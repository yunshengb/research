#include "User.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int main() {
  try {
    User user("yba", "cookies0");
    user.login();
    user.learnImage();
    //user.learnImage();
    // user.inferImage();
    user.learnText();
    // user.learnUrl();
    // user.deleteImage();
    user.inferImageText();
  } catch (const runtime_error &e) {
    cout << e.what() << "\n";
  }
    return 0;
}
