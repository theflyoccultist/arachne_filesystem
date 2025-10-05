#include "../include/FileManager.h"
#include "../include/FileStats.h"
#include "../include/UI.h"
#include "../include/UI_dialog.h"
#include <ncurses.h>

int main() {
  FileManager f;
  FileStats s;

  UI ui;
  ui.setup_UI(0);
  ui.initialize_colors();
  UI_Dialog dialog;

  bool running = true;
  int highl_index = 0;

  enum class Mode {
    Help,
    Browsing,
    ViewingFile,
    ViewingStats,
    CreateFile,
    CreateDirectory,
    Renaming,
    Removing
  };
  Mode mode = Mode::Browsing;

  while (running) {
    clear();

    mvprintw(1, 0, "Press q to quit, h to display help.");
    mvprintw(2, 0, "Current Folder: %s", f.current_path().c_str());

    auto files = f.current_files();

    switch (mode) {
    case Mode::Help:
      ui.display_help();
      break;

    case Mode::Browsing:
      ui.display_dir(files, highl_index);
      ui.draw_list(files, highl_index);
      break;

    case Mode::ViewingFile:
      ui.display_file();
      break;

    case Mode::ViewingStats:
      ui.display_path(f.current_path().c_str());
      ui.display_size(s.get_size(files[highl_index]));
      ui.display_perms(s.get_perms(files[highl_index]));
      ui.display_mtime(s.get_mtime(files[highl_index]));
      break;

    case Mode::CreateFile: {
      string file_name = dialog.display_dialog("New File name: ");
      if (dialog.create_file(file_name)) {
        auto msg = f.create_file(file_name);
        ui.show_status(msg);
      }
      break;
    }

    case Mode::CreateDirectory: {
      string dir_name = dialog.display_dialog("New Directory name: ");
      if (dialog.create_folder(dir_name)) {
        auto msg = f.create_directory(dir_name);
        ui.show_status(msg);
      }
      break;
    }

    case Mode::Renaming: {
      string old_name = files[highl_index];
      string new_name = dialog.display_dialog("Rename to: ");
      if (dialog.rename(new_name)) {
        auto msg = f.rename(old_name, new_name);
        ui.show_status(msg);
      }
      break;
    }

    case Mode::Removing: {
      dialog.confirm_removal(files[highl_index]);

      int ch = getch();
      if (ch == 'Y') {
        auto msg = f.remove(files[highl_index]);
        mvprintw(LINES - 6, 0, "%s", msg.c_str());
      } else {
        mvprintw(LINES - 6, 0, "Deletion canceled.");
      }
      mvprintw(LINES - 5, 0, "Press 'l' to go back to the directory list.");
    }
    }

    refresh();

    int ch = getch();
    switch (ch) {

    case 'q':
      running = false;
      break;

    case '\n': {
      f.enter_directory(files[highl_index]);
      highl_index = 0;
      break;
    }

    case 'h':
      mode = Mode::Help;
      break;

    case KEY_BACKSPACE:
      if (mode != Mode::Browsing)
        continue;
      f.go_up();
      highl_index = 0;
      break;

    case 'o':
      ui.open_file(files[highl_index]);
      mode = Mode::ViewingFile;
      break;

    case 's':
      mode = Mode::ViewingStats;
      break;

    case 'l':
      mode = Mode::Browsing;
      break;

    case 'c':
      mode = Mode::CreateFile;
      break;

    case 'f':
      mode = Mode::CreateDirectory;
      break;

    case 'r':
      mode = Mode::Renaming;
      break;

    case 'd':
      mode = Mode::Removing;
      break;

    case KEY_UP:
      if (mode == Mode::Browsing) {
        highl_index--;
        ui.scroll_list(-1, files, highl_index);
      } else if (mode == Mode::ViewingFile) {
        ui.scroll_file(-1);
      }
      break;

    case KEY_DOWN:
      if (mode == Mode::Browsing) {
        highl_index++;
        ui.scroll_list(+1, files, highl_index);
      } else if (mode == Mode::ViewingFile) {
        ui.scroll_file(+1);
      }
    }
  }

  endwin();
  return 0;
}
