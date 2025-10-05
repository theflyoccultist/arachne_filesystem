#include "../include/UI_dialog.h"
#include <ncurses.h>

string UI_Dialog::display_dialog(const string &prompt) {
  char buf[256];
  buf[0] = '\0';

  WINDOW *win = newwin(3, 40, LINES / 2 - 1, COLS / 2 - 20);
  box(win, 0, 0);
  mvwprintw(win, 1, 1, "%s", prompt.c_str());
  wrefresh(win);

  echo();
  wgetnstr(win, buf, sizeof(buf) - 1);
  noecho();

  delwin(win);

  mvprintw(LINES - 5, 0, "Press 'l' to go back to the directory list.");
  string input(buf);
  return input;
}

bool UI_Dialog::create_file(const string &input) {
  if (input.empty()) {
    mvprintw(LINES - 6, 0, "File creation has been canceled.");
    return false;
  } else {
    mvprintw(LINES - 6, 0, "File created with name: %s", input.c_str());
    return true;
  }
}

bool UI_Dialog::create_folder(const string &input) {
  if (input.empty()) {
    mvprintw(LINES - 6, 0, "Folder creation has been canceled.");
    return false;
  } else {
    mvprintw(LINES - 6, 0, "Folder created with name: %s", input.c_str());
    return true;
  }
}

bool UI_Dialog::rename(const string &input) {
  if (input.empty()) {
    mvprintw(LINES - 6, 0, "File renaming has been canceled.");
    return false;
  } else {
    mvprintw(LINES - 6, 0, "File has been renamed to: %s", input.c_str());
    return true;
  }
}
