#pragma once
#include <filesystem>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace fs = std::filesystem;

class FileManager {
public:
  FileManager();

  vector<string> list_dir(const string &path) const;

  void enter_directory(const string &selected);
  void go_up();
  void rename(const string &old_name, const string &new_name);
  double get_size(const fs::path &path);

  vector<string> current_files() const;
  fs::path current_path() const;

private:
  fs::path current_folder;
  vector<string> files;
};
