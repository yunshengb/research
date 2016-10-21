#include "User.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int main() {
  try {
    User user("yba", "cookies0");
    user.login();
    while (true) {
      user.inferText();
    }
  } catch (const runtime_error &e) {
    cout << e.what() << endl;
  } catch (...) {
    cout << "Exception caught!" << endl;
  }
  return 0;
}
