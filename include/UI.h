#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class UI {
public:
  void setup_UI(const int toggle_cursor);
  void initialize_colors();
  void scroll_movement(const vector<string> &files, int &highl_idx);
  void draw_list(const vector<string> &files, int highl_idx);
};
