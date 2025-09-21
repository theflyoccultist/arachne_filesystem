#include "../include/FileManager.h"
#include "../include/UI.h"
#include <ncurses.h>

int main() {
  bool running = true;
  bool show_file = false;
  bool show_list = false;
  int highl_index = 0;

  FileManager f;
  std::string p = f.get_filename("/home/rin/work/test.txt");
  std::vector<std::string> l = f.list_dir("/home/rin/work");

  UI ui;
  ui.setup_UI(0);
  ui.initialize_colors();

  while (running) {
    clear();

    mvprintw(1, 0, "Press q to quit.");

    if (show_file) {
      mvprintw(0, 0, "%s", p.c_str());
    }

    if (show_list) {
      ui.scroll_movement(l, highl_index);
      ui.draw_list(l, highl_index);
    }

    refresh();

    int ch = getch();
    if (ch == 'g')
      show_file = !show_file;
    if (ch == 'l')
      show_list = !show_list;
    if (ch == 'q')
      running = false;
    if (ch == KEY_UP)
      highl_index--;
    if (ch == KEY_DOWN)
      highl_index++;
  }

  endwin();
  return 0;
}
