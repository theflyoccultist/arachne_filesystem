#include <string>

using std::string;

class UI_Dialog {
public:
  string display_dialog(const string &prompt);

  bool create_file(const string &input);
  bool create_folder(const string &input);
  bool rename(const string &input);
  void confirm_removal(const string &input);
};
