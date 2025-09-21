#include "../include/FileManager.h"

string FileManager::get_filename(string path) {
  fs::path file_path = path;
  string filename = file_path.filename().string();
  return filename;
}

vector<string> FileManager::list_dir(const string &path) {
  vector<string> list_of_entries;
  for (const auto &entry : fs::directory_iterator(path))
    list_of_entries.push_back(entry.path().string());
  return list_of_entries;
}

fs::path FileManager::enter_directory(const fs::path &current,
                                      const string &selected) {
  fs::path next = current / selected;
  if (fs::is_directory(next))
    return next;
  return current;
}

fs::path FileManager::go_up(const fs::path &current) {
  if (current.has_parent_path())
    return current.parent_path();
  return current;
}
