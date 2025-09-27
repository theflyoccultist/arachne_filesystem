#include "../include/FileManager.h"
#include "../include/UI.h"
#include <ncurses.h>

int main() {
  FileManager f;
  UI ui;
  ui.setup_UI(0);
  ui.initialize_colors();

  bool running = true;
  int highl_index = 0;

  enum class Mode { Browsing, ViewingFile, Renaming, ViewingSize };
  Mode mode = Mode::Browsing;

  while (running) {
    clear();

    mvprintw(1, 0, "Press q to quit.");
    mvprintw(2, 0, "Current Folder: %s", f.current_path().c_str());

    auto files = f.current_files();

    switch (mode) {
    case Mode::Browsing:
      ui.scroll_movement(files, highl_index);
      ui.draw_list(files, highl_index);
      break;

    case Mode::ViewingFile:
      ui.display_file();
      break;

    case Mode::Renaming: {
      string old_name = files[highl_index];
      string new_name = ui.display_dialog("Rename to: ");
      f.rename(old_name, new_name);
      break;
    }

    case Mode::ViewingSize:
      ui.display_size(files[highl_index], f.get_size(files[highl_index]));
      break;
    }

    refresh();

    int ch = getch();
    switch (ch) {
    case 'q':
      running = false;
      break;

    case '\n':
      f.enter_directory(files[highl_index]);
      highl_index = 0;
      break;

    case KEY_BACKSPACE:
      if (mode == Mode::ViewingFile)
        continue;
      f.go_up();
      highl_index = 0;
      break;

    case 'o':
      ui.open_file(files[highl_index]);
      mode = Mode::ViewingFile;
      break;

    case 'l':
      mode = Mode::Browsing;
      break;

    case 'r':
      mode = Mode::Renaming;
      break;

    case 's':
      mode = Mode::ViewingSize;
      break;

    case KEY_UP:
      if (mode == Mode::Browsing)
        highl_index--;
      else if (mode == Mode::ViewingFile)
        ui.scroll_file(-1);
      break;

    case KEY_DOWN:
      if (mode == Mode::Browsing)
        highl_index++;
      else if (mode == Mode::ViewingFile)
        ui.scroll_file(+1);
    }
  }

  endwin();
  return 0;
}
