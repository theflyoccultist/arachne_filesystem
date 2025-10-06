#include <string>

using std::string;

class UI_Dialog {
public:
  string display_dialog(const string &prompt);

  bool create_file(const string &input);
  bool create_folder(const string &input);
  bool rename(const string &original, const string &new_name);
  void confirm_removal(const string &input);
  bool copy(const string &original, const string &copy);
  bool move(const string &original, const string &new_name);
};
