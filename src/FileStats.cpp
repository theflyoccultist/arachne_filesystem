#include "../include/FileStats.h"
#include <chrono>
#include <format>
#include <sstream>

double FileStats::get_size(const fs::path &path) {
  if (fs::is_regular_file(path)) {
    return fs::file_size(path) / 1024.0;
  } else if (fs::is_directory(path)) {
    double total = 0;
    for (auto const &entry : fs::recursive_directory_iterator(path)) {
      if (entry.is_regular_file()) {
        total += fs::file_size(entry);
      }
    }
    return total / 1024.0;
  }
  return 0.0;
}

namespace {
string parse_perms(fs::perms p) {
  using std::filesystem::perms;

  std::ostringstream out;

  auto show = [&](char op, perms perm) {
    out << (perms::none == (perm & p) ? '-' : op);
  };

  show('r', perms::owner_read);
  show('w', perms::owner_write);
  show('x', perms::owner_exec);
  show('r', perms::group_read);
  show('w', perms::group_write);
  show('x', perms::group_exec);
  show('r', perms::others_read);
  show('w', perms::others_write);
  show('x', perms::others_exec);

  return out.str();
}
} // namespace

string FileStats::get_perms(const fs::path &p) {
  return parse_perms(fs::status(p).permissions());
}

string FileStats::get_mtime(const fs::path &path) {
  auto ftime = fs::last_write_time(path);
  auto sctp = std::chrono::clock_cast<std::chrono::system_clock>(ftime);
  return std::format("{:%F %H:%M}", sctp);
}
