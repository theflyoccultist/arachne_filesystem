#include "../include/FileManager.h"
#include "../include/UI.h"
#include <ncurses.h>

int main() {
  setup_UI(0);

  FileManager f;
  std::string p =
      f.get_filename("/home/rin/work/cpp/arachne_filesystem/CMakeLists.txt");

  bool running = true;
  while (running) {
    clear();
    mvprintw(0, 0, "%s", p.c_str());
    mvprintw(1, 0, "Press q to quit.");
    refresh();

    int ch = getch();
    if (ch == 'q') {
      running = false;
    }
  }

  endwin();
  return 0;
}
