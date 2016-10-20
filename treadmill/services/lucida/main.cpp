#include "User.h"
#include <iostream>
#include <stdexcept>
#include <glog/logging.h>

using namespace std;

int main() {
  try {
    User user("yba", "cookies0");
    user.login();
    while (true) {
      user.inferText();
    }
  } catch (const runtime_error &e) {
    LOG(ERROR) << e.what();
  } catch (...) {
    LOG(ERROR) << "Exception caught!";
  }
  return 0;
}
