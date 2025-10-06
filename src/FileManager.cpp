#include "../include/FileManager.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <system_error>

FileManager::FileManager() {
  current_folder = fs::current_path();
  files = list_dir(current_folder.string());
}

vector<string> FileManager::list_dir(const string &path) const {
  vector<string> list_of_entries;
  std::error_code ec;
  fs::directory_iterator it(path, ec);

  if (ec) {
    list_of_entries.push_back("[Error] " + ec.message());
  }

  for (const auto &entry : it)
    list_of_entries.push_back(entry.path().string());

  std::sort(list_of_entries.begin(), list_of_entries.end());
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

string FileManager::create_file(const string &input) {
  auto path = current_folder / input;
  if (fs::exists(path)) {
    return "Warning: file already exists (not overwritten).";
  }
  std::ofstream file(path);
  if (!file.is_open()) {
    return "Error: could not create file (permission denied?)";
  }
  files = list_dir(current_folder.string());
  return "File created successfully";
}

string FileManager::create_directory(const string &input) {
  auto path = current_folder / input;
  if (fs::exists(path)) {
    return "Warning: directory already exists (not overwritten).";
  }

  std::error_code ec;
  fs::create_directories(path, ec);
  if (ec)
    return "Error: " + ec.message();

  files = list_dir(current_folder.string());
  return "Directory has been created successfully.";
}

string FileManager::rename(const string &old_name, const string &new_name) {
  try {
    fs::rename(current_folder / old_name, current_folder / new_name);
    files = list_dir(current_folder.string());
    return old_name + " renamed to " + new_name;
  } catch (fs::filesystem_error const &ex) {
    return ex.code().message();
  }
}

string FileManager::remove(const string &input) {
  auto path = current_folder / input;
  if (!fs::exists(path)) {
    return "Error: the file / directory does not exist (aborted).";
  }

  std::error_code ec;
  const std::uintmax_t n = fs::remove_all(path, ec);
  if (ec)
    return "Error: " + ec.message();

  files = list_dir(current_folder.string());
  return "Removed " + std::to_string(n) + " files or directories.";
}

string FileManager::copy(const string &original, const string &copy) {
  auto path_orig = current_folder / original;
  auto path_copy = current_folder / copy;

  std::error_code ec;
  if (fs::equivalent(path_orig, path_copy, ec)) {
    return "Error: source and destination are the same path.";
  }

  auto copy_opts = fs::copy_options::update_existing;

  if (fs::is_directory(path_orig)) {
    if (path_copy.string().find(path_orig.string()) == 0)
      return "Error: cannot copy a directory into itself";

    copy_opts |= fs::copy_options::recursive;
    fs::copy(path_orig, path_copy, copy_opts, ec);

    if (ec)
      return "Error: " + ec.message();

  } else {
    fs::copy(path_orig, path_copy, ec);

    if (ec)
      return "Error: " + ec.message();
  }
  files = list_dir(current_folder.string());
  return "Copied: " + original + " to " + copy;
}

string FileManager::move(const string &old_name, const string &new_name) {
  auto path_orig = current_folder / old_name;
  auto path_new = current_folder / new_name;
  std::error_code ec;

  if (fs::equivalent(path_orig, path_new, ec))
    return "Error: source and destination are the same.";

  if (fs::is_directory(path_orig))
    path_new /= path_orig.filename();

  fs::rename(path_orig, path_new, ec);

  if (ec == std::errc::cross_device_link) {
    const auto copy_opts =
        fs::copy_options::recursive | fs::copy_options::overwrite_existing;
    fs::copy(path_orig, path_new, copy_opts, ec);
    fs::remove_all(path_orig, ec);
  }

  if (ec)
    return "Error: " + ec.message();

  files = list_dir(current_folder.string());
  return old_name + " moved to " + path_new.string();
}

vector<string> FileManager::current_files() const { return files; }

fs::path FileManager::current_path() const { return current_folder; }
