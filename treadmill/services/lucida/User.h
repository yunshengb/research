#ifndef User_h
#define User_h

#include <string>
#include <curl/curl.h>
#include <stdexcept>
#include <vector>

// A class for representing a User.
class User {
public:
  // Constructor.
  User(const std::string &username_, const std::string &password_) :
  username(username_), password(password_), unique_id(num_users++) {
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl) {
      throw std::runtime_error("Curl initialization failed");
    }
  }

  // Destructor.
  ~User() {
    curl_easy_cleanup(curl);
    curl_formfree(formpost);
  }

  // Sends a login request.
  // Throws `runtime_error` if it fails.
  void sendLoginRequest();

  // Sends a learn image request.
  // Throws `runtime_error` if it fails.
  void sendLearnImageRequest();

  // Sends a learn text request.
  // Throws `runtime_error` if it fails.
  void sendLearnTextRequest();

  // Sends an infer image request.
  // Throws `runtime_error` if it fails.
  void sendInferImageRequest();

private:
  // The username.
  const std::string username;

  // The password.
  const std::string password;

  // The unique ID of the user.
  int unique_id;

  // The number of users that have been created.
  static int num_users;

  // Curl.
  CURL *curl = nullptr;
  struct curl_httppost *formpost = nullptr;

  // Sets the form.
  // Returns the pointer to the last item of the form.
  struct curl_httppost *setForm(
    const std::vector<std::pair<std::string, std::string>> &form);

  // Attaches a file to the form.
  // Must be called after `setForm()` using its returned pointer as `lastptr`.
  void attachFileToForm(const std::string &file_path,
    struct curl_httppost *lastptr);

  // Performs the HTTP request and returns the HTML content as a string.
  // Throws `runtime_error` if it fails.
  std::string performRequest() const;
};

#endif /* User_h */
