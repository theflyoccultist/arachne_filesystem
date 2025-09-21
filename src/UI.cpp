#include "../include/UI.h"
#include <cstddef>
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
  if (highl_index < 0)
    highl_index = files.size() - 1;
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
    mvprintw(i + 2, 0, "%s", display_name.c_str());

    if (is_highlighted)
      attroff(A_REVERSE | COLOR_PAIR(color));
  }
}

void UI::display_file(const string &file) {
  if (fs::is_regular_file(file)) {
    std::ifstream f(file);
    if (f.is_open()) {
      string line;

      int i = 0;
      while (std::getline(f, line)) {
        mvprintw(i + 2, 0, "%s", line.c_str());
        ++i;
      }
    }
    f.close();
  }
}
