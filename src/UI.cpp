#include "../include/UI.h"
#include <cstddef>
#include <iostream>
#include <ncurses.h>

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
}

void UI::scroll_movement(const vector<string> &files, int &highl_index) {
  if (highl_index < 0)
    highl_index = files.size() - 1;
  if (highl_index >= (int)files.size())
    highl_index = 0;
}

void UI::draw_list(const vector<string> &files, int &highl_index) {
  for (size_t i = 0; i < files.size(); i++) {
    if (i == highl_index) {
      attron(A_REVERSE | COLOR_PAIR(1));
      mvprintw(i + 2, 0, "%s", files[i].c_str());
      attroff(A_REVERSE | COLOR_PAIR(1));
    } else {
      mvprintw(i + 2, 0, "%s", files[i].c_str());
    }
  }
}
