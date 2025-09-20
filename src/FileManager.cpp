#include "../include/FileManager.h"
#include <filesystem>
#include <string>

using std::string;
namespace fs = std::filesystem;

string FileManager::get_filename(string path) {
  fs::path file_path = path;
  string filename = file_path.filename().string();
  return filename;
}
