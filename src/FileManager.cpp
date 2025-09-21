#include "../include/FileManager.h"
#include <filesystem>

namespace fs = std::filesystem;

string FileManager::get_filename(string path) {
  fs::path file_path = path;
  string filename = file_path.filename().string();
  return filename;
}

vector<string> FileManager::list_dir(string path) {
  vector<string> list_of_entries;
  for (const auto &entry : fs::directory_iterator(path))
    list_of_entries.push_back(entry.path());
  return list_of_entries;
}
