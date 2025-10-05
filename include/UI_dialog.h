#include <string>

using std::string;

class UI_Dialog {
public:
  string display_dialog(const string &prompt);
  bool rename(const string &input);
};
