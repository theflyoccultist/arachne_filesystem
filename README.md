# arachne_filesystem
A TUI file explorer using std::filesystem and ncurses

## Controls

- Enter key: open folder
- Backspace: go to parent directory
- o: toggle file viewer
- l: toggle directory viewer
- r: rename selected file / folder
- Key Up and Key Down: browse directory / browse current file

## Setup

```bash
git clone https://github.com/theflyoccultist/arachne_filesystem.git
mkdir build && cd build
cmake ..
make
./arachne_filesystem
```

