#ifndef User_h
#define User_h

#include <string>
#include <curl/curl.h>
#include <stdexcept>
#include <vector>

// A class for representing a User.
class User {
public:
  // The type of knowledge.
  enum class KnowledgeType {
    IMAGE, TEXT, URL
  };

  // Type of HTTP request.
  enum class HTTPRequestType {
    GET, POST
  };

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
  void login();

  // Sends a learn image request.
  // Throws `runtime_error` if it fails.
  void learnImage();

  // Sends a delete image request.
  // Throws `runtime_error` if there is no image or it fails.
  void deleteImage();

  // Sends a learn text request.
  // Throws `runtime_error` if it fails.
  void learnText();

  // Sends a delete text request.
  // Throws `runtime_error` if there is no text or it fails.
  void deleteText();

  // Sends a learn url request.
  // Throws `runtime_error` if it fails.
  void learnUrl();

  // Sends an infer image request.
  // Throws `runtime_error` if it fails.
  void inferImage();

  // Sends an infer text request.
  // Throws `runtime_error` if it fails.
  void inferText();

  // Sends an infer image text request.
  // Throws `runtime_error` if it fails.
  void inferImageText();

private:
  // The username.
  const std::string username;

  // The password.
  const std::string password;

  // The unique ID of the user.
  int unique_id;

  // The number of users that have been created.
  static int num_users;

  // Curl handle.
  CURL *curl = nullptr;

  // Curl form.
  struct curl_httppost *formpost = nullptr;

  // Sends a request to delete an image or a piece of text.
  // `type` must be either `IMAGE` or `TEXT`.
  // Throws `runtime_error` if `type` is wrong, there is no image, or it fails.
  void deleteKnowledge(KnowledgeType type);

  // Sets the form.
  // Returns the pointer to the last item of the form.
  struct curl_httppost *setForm(
    const std::vector<std::pair<std::string, std::string>> &form);

  // Attaches a file to the form.
  // Must be called after `setForm()` using its returned pointer as `lastptr`.
  void attachFileToForm(const std::string &file_path,
    struct curl_httppost *lastptr);

  // Performs the HTTP request and returns the HTML content as a string.
  // Throws `runtime_error` if `type` is wrong, or it fails.
  std::string performRequest(HTTPRequestType type = HTTPRequestType::POST)
  const;
};

#endif /* User_h */
