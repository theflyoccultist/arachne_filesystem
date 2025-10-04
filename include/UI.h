#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class UI {
public:
  void setup_UI(const int toggle_cursor);
  void initialize_colors();

  void display_dir(const vector<string> &files, int &highl_index);
  void scroll_list(int delta, const vector<string> &files, int highl_index);
  void draw_list(const vector<string> &files, const int &highl_index);

  void open_file(const string &file);
  void scroll_file(int delta);
  void display_file();

  string display_dialog(const string &prompt);

  void display_path(const string &path);
  void display_size(const double &size);
  void display_perms(const string &perms);
  void display_mtime(const string &time);

  void show_status(const string &msg);

private:
  vector<string> file_contents;
  int file_offset = 0;
  int list_offset = 0;
};
