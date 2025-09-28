#pragma once

#include <filesystem>
#include <string>

using std::string;

namespace fs = std::filesystem;

class FileStats {
public:
  double get_size(const fs::path &path);
  string get_perms(const fs::path &p);
  string get_mtime(const fs::path &path);
};
