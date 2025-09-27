#include "../include/FileManager.h"
#include <filesystem>
#include <iostream>

FileManager::FileManager() {
  current_folder = fs::current_path();
  files = list_dir(current_folder.string());
}

vector<string> FileManager::list_dir(const string &path) const {
  vector<string> list_of_entries;
  for (const auto &entry : fs::directory_iterator(path))
    list_of_entries.push_back(entry.path().string());
  return list_of_entries;
}

void FileManager::enter_directory(const string &selected) {
  fs::path new_path = fs::path(selected);
  if (fs::is_directory(new_path)) {
    current_folder = new_path;
    files = list_dir(current_folder.string());
  }
}

void FileManager::go_up() {
  if (current_folder.has_parent_path()) {
    current_folder = current_folder.parent_path();
    files = list_dir(current_folder.string());
  }
}

void FileManager::rename(const string &old_name, const string &new_name) {
  try {
    fs::rename(current_folder / old_name, current_folder / new_name);
    files = list_dir(current_folder.string());
  } catch (fs::filesystem_error const &ex) {
    std::cout << ex.code().message() << "\n";
  }
}

vector<string> FileManager::current_files() const { return files; }

fs::path FileManager::current_path() const { return current_folder; }
