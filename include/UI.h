#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class UI {
public:
  void setup_UI(const int toggle_cursor);
  void initialize_colors();

  void scroll_movement(const vector<string> &files, int &highl_index);
  void draw_list(const vector<string> &files, const int &highl_index);

  void open_file(const string &file);
  void scroll_file(int delta);
  void display_file();

  string display_dialog(const string &prompt);

  void display_size(const string &path, const double &size);
  void display_perms(const string &path, const string &perms);
  void display_mtime(const string &path, const string &time);

private:
  vector<string> file_contents;
  int scroll_offset = 0;
};
