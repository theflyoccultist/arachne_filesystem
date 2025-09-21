#include "../include/FileManager.h"
#include "../include/UI.h"
#include <filesystem>
#include <ncurses.h>

namespace fs = std::filesystem;

int main() {
  bool running = true;
  bool show_file = false;
  bool show_list = false;
  int highl_index = 0;

  FileManager f;
  std::string p = f.get_filename("/home/rin/work/test.txt");
  fs::path current_folder = fs::current_path();
  auto files = f.list_dir(current_folder.string());

  UI ui;
  ui.setup_UI(0);
  ui.initialize_colors();

  while (running) {
    clear();

    mvprintw(1, 0, "Press q to quit.");

    if (show_file && !show_list) {
      show_list = !show_list;
      ui.display_file(files[highl_index]);
    } else if (show_list) {
      ui.scroll_movement(files, highl_index);
      ui.draw_list(files, highl_index);
    }

    refresh();

    int ch = getch();
    if (ch == 'q')
      running = false;
    else if (ch == 'o')
      show_file = !show_file;
    else if (ch == 'l')
      show_list = !show_list;
    else if (ch == KEY_UP)
      highl_index--;
    else if (ch == KEY_DOWN)
      highl_index++;
    else if (ch == '\n') {
      current_folder = f.enter_directory(current_folder, files[highl_index]);
      files = f.list_dir(current_folder.string());
      highl_index = 0;
    } else if (ch == KEY_BACKSPACE) {
      current_folder = f.go_up(current_folder);
      files = f.list_dir(current_folder.string());
      highl_index = 0;
    }
  }

  endwin();
  return 0;
}
