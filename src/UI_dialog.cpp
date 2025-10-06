#include "../include/UI_dialog.h"
#include <ncurses.h>

string UI_Dialog::display_dialog(const string &prompt) {
  char buf[256];
  buf[0] = '\0';

  WINDOW *win = newwin(4, 40, LINES / 2 - 1, COLS / 2 - 20);
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

bool UI_Dialog::rename(const string &original, const string &new_name) {
  if (original.empty()) {
    mvprintw(LINES - 6, 0, "File renaming has been canceled.");
    return false;
  } else {
    mvprintw(LINES - 6, 0, "%s has been renamed to: %s", original.c_str(),
             new_name.c_str());
    return true;
  }
}

void UI_Dialog::confirm_removal(const string &input) {
  mvprintw(LINES - 7, 0, "Are you sure you want to remove %s? [Y/n]",
           input.c_str());
}

bool UI_Dialog::copy(const string &original, const string &copy) {
  if (copy.empty()) {
    mvprintw(LINES - 6, 0, "Copying has been canceled.");
    return false;
  } else {
    mvprintw(LINES - 6, 0, "%s has been copied to %s", original.c_str(),
             copy.c_str());
    return true;
  }
}

bool UI_Dialog::move(const string &original, const string &new_name) {
  if (original.empty()) {
    mvprintw(LINES - 6, 0, "Move has been canceled.");
    return false;
  } else {
    mvprintw(LINES - 6, 0, "%s has been moved to: %s", original.c_str(),
             new_name.c_str());
    return true;
  }
}
