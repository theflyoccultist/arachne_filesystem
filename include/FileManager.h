#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

class FileManager {
public:
  string get_filename(string path);
  vector<string> list_dir(string path);
};
