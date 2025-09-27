#include "../include/UI.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <string>

namespace fs = std::filesystem;

void UI::setup_UI(const int toggle_cursor) {
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(toggle_cursor);
}

void UI::initialize_colors() {
  if (!has_colors()) {
    endwin();
    std::cerr << "Color can't be used\n";
    return;
  }

  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
}

void UI::scroll_movement(const vector<string> &files, int &highl_index) {
  if (highl_index < 0) {
    highl_index = files.size() - 1;
  }
  if (highl_index >= (int)files.size())
    highl_index = 0;
}

void UI::draw_list(const vector<string> &files, const int &highl_index) {
  for (size_t i = 0; i < files.size(); i++) {
    fs::path entry_path(files[i]);
    bool is_dir = fs::is_directory(entry_path);

    bool is_highlighted = (i == highl_index);
    int color = (is_highlighted ? (is_dir ? 2 : 1) : 0);

    if (is_highlighted)
      attron(A_REVERSE | COLOR_PAIR(color));

    string prefix = is_dir ? "[DIR] " : "[FILE] ";

    string display_name = prefix + files[i];
    mvprintw(i + 4, 0, "%s", display_name.c_str());

    if (is_highlighted)
      attroff(A_REVERSE | COLOR_PAIR(color));
  }
}

void UI::open_file(const string &file) {
  file_contents.clear();
  scroll_offset = 0;

  if (fs::is_regular_file(file)) {
    std::ifstream f(file);
    if (f.is_open()) {
      string line;
      while (std::getline(f, line)) {
        file_contents.push_back(line);
      }
    }
  } else {
    file_contents.push_back("[Not a regular file]");
  }
}

void UI::scroll_file(int delta) {
  int max_offset = std::max(0, (int)file_contents.size() - (LINES - 5));
  scroll_offset = std::clamp(scroll_offset + delta, 0, max_offset);
}

void UI::display_file() {
  int max_lines = LINES - 5;
  for (int i = 0;
       i < max_lines && (i + scroll_offset) < (int)file_contents.size(); i++) {
    mvprintw(i + 4, 0, "%s", file_contents[i + scroll_offset].c_str());
  }
}

string UI::display_dialog(const string &prompt) {
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

  string input(buf);

  if (input.empty()) {
    mvprintw(LINES - 6, 0, "File renaming has been canceled.");
  } else {
    mvprintw(LINES - 6, 0, "File has been renamed to: %s", input.c_str());
  }

  mvprintw(LINES - 5, 0, "Press 'l' to go back to the directory list.");
  return input;
}

void UI::display_size(const string &path, const double &size) {
  string file_size;
  (size < 1024.0) ? file_size = std::to_string(size) + " KB"
                  : file_size = std::to_string(size / 1024.0) + " MB";
  mvprintw(LINES - 6, 0, "SIZE OF %s : %s", path.c_str(), file_size.c_str());
}
