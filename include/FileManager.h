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

  string create_file(const string &input);
  string create_directory(const string &input);
  string rename(const string &old_name, const string &new_name);
  string remove(const string &input);

  vector<string> current_files() const;
  fs::path current_path() const;

private:
  fs::path current_folder;
  vector<string> files;
};
