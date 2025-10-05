#include "../include/UI.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ncurses.h>

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

void UI::display_help() {
  mvprintw(4, 0, "Enter key: open selected folder");
  mvprintw(5, 0, "Backspace: go to parent directory");
  mvprintw(6, 0, "Key Up / Down: browse file / directory");
  mvprintw(7, 0, "h: display help");
  mvprintw(8, 0, "o: toggle file viewer");
  mvprintw(9, 0, "l: list directory");
  mvprintw(10, 0, "r: rename selected file / directory");
  mvprintw(11, 0, "s: display file / directory stats");
  mvprintw(12, 0, "c: create file");
  mvprintw(13, 0, "f: create directory");
  mvprintw(14, 0, "d: remove selected file / directory");
  mvprintw(15, 0, "p: copy file / directory");
  mvprintw(16, 0, "q: quit app");
}

void UI::display_dir(const vector<string> &files, int &highl_index) {
  if (highl_index < 0) {
    highl_index = 0;
  } else if (highl_index >= (int)files.size())
    highl_index = (int)files.size() - 1;
}

void UI::scroll_list(int delta, const vector<string> &files, int highl_index) {
  int max_lines = LINES - 5;
  if (highl_index < list_offset) {
    list_offset = highl_index;
  } else if (highl_index >= list_offset + max_lines) {
    list_offset = highl_index - max_lines;
  }

  int max_offset = std::max(0, (int)files.size() - max_lines);
  list_offset = std::clamp(list_offset + delta, 0, max_offset);
}

void UI::draw_list(const vector<string> &files, const int &highl_index) {
  for (int i = 0; i < (LINES - 5) && (i + list_offset) < (int)files.size();
       i++) {
    int idx = i + list_offset;

    fs::path entry_path(files[idx]);
    bool is_dir = fs::is_directory(entry_path);

    bool is_highlighted = (idx == highl_index);
    int color = (is_highlighted ? (is_dir ? 2 : 1) : 0);

    if (is_highlighted)
      attron(A_REVERSE | COLOR_PAIR(color));

    string prefix = is_dir ? "[DIR] " : "[FILE] ";
    string display_name = prefix + files[idx];

    mvprintw(i + 4, 0, "%s", display_name.c_str());

    if (is_highlighted)
      attroff(A_REVERSE | COLOR_PAIR(color));
  }
}

void UI::open_file(const string &file) {
  file_contents.clear();
  file_offset = 0;

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
  file_offset = std::clamp(file_offset + delta, 0, max_offset);
}

void UI::display_file() {
  int max_lines = LINES - 5;
  for (int i = 0;
       i < max_lines && (i + file_offset) < (int)file_contents.size(); i++) {
    mvprintw(i + 4, 0, "%s", file_contents[i + file_offset].c_str());
  }
}

void UI::display_path(const string &path) {
  mvprintw(LINES - 8, 0, "File Path: %s", path.c_str());
}

void UI::display_size(const double &size) {
  string file_size;
  (size < 1024.0) ? file_size = std::to_string(size) + " KB"
                  : file_size = std::to_string(size / 1024.0) + " MB";
  mvprintw(LINES - 7, 0, "Size: %s", file_size.c_str());
}

void UI::display_perms(const string &perms) {
  mvprintw(LINES - 6, 0, "Permissions: %s", perms.c_str());
}

void UI::display_mtime(const string &time) {
  mvprintw(LINES - 5, 0, "Last modified time: %s", time.c_str());
}

void UI::show_status(const string &msg) { mvprintw(3, 0, "%s", msg.c_str()); }
