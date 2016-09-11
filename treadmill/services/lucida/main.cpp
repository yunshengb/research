#include "User.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int main() {
  try {
    User user("yba", "cookies0");
    user.sendLoginRequest();
    user.sendLearnImageRequest();
    user.sendInferImageRequest();
    user.sendLearnTextRequest();
  } catch (const runtime_error &e) {
    cout << e.what() << "\n";
  }
    return 0;
}
