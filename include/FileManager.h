#pragma once
#include <filesystem>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace fs = std::filesystem;

class FileManager {
public:
  string get_filename(string path);
  vector<string> list_dir(const string &path);

  fs::path enter_directory(const fs::path &current, const string &selected);
  fs::path go_up(const fs::path &current);
};
