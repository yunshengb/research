#include "User.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <glog/logging.h>
#include <cstdio>

using namespace std;

// URLs to send requests.
const char * const LOGIN_URL = "https://clarity13.eecs.umich.edu:30000/login";
const char * const LEARN_URL = "https://clarity13.eecs.umich.edu:30000/learn";
const char * const INFER_URL = "https://clarity13.eecs.umich.edu:30000/infer";
const char * const INFER_SPEECH_URL =
"https://clarity13.eecs.umich.edu:30001/client/dynamic/recognize";
// const char * const LOGIN_URL = "http://localhost:3000/login";
// const char * const LEARN_URL = "http://localhost:3000/learn";
// const char * const INFER_URL = "http://localhost:3000/infer";
// const char * const INFER_SPEECH_URL =
// "http://localhost:8081/client/dynamic/recognize";

// HTML tags that define the error.
static const char * const error_start =
"<strong class=text-danger><p class=\"error\">";
static const char * const error_end = "</p></strong>";

// HTML tags that define the infer result.
static const char * const infer_result_start =
"<textarea readonly id=\"clinc\" style=\"margin-right: 10px\">";
static const char * const infer_result_end = "</textarea>";

// JASON strings that define the speech infer result.
static const char * const speech_infer_result_start =
"\"hypotheses\": [{\"utterance\": ";
static const char * const speech_infer_result_end = "}], \"id\": \"";

// Initialize static variables.
int User::num_users = 0;

// Call back function for curl.
size_t curlWriteCallbackFunc(void *contents, size_t size, size_t nmemb,
  string *s) {
  size_t new_length = size * nmemb;
  size_t old_length = s->size();
  s->resize(old_length + new_length);
  copy((char*) contents,(char*) contents + new_length,
    s->begin() + old_length);
  return size * nmemb;
}

// Constructor.
User::User(const string &username_, const string &password_) :
username(username_), password(password_), unique_id(num_users++) {
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if (!curl) {
    throw runtime_error("Curl initialization failed");
  }
}

// Destructor.
User::~User() {
  curl_easy_cleanup(curl);
  curl_formfree(formpost);
}

// Sends a login request.
// Must be called before other requests.
// Throws `runtime_error` if it fails.
void User::login() {
  LOG(INFO) << "Login started";
  curl_easy_setopt(curl, CURLOPT_URL, LOGIN_URL);
  string cookie_file_name = "cookies" + to_string(unique_id);
  cookie_file_name += ".txt";
  curl_easy_setopt(curl, CURLOPT_COOKIEJAR, cookie_file_name.c_str());
  setForm({{"username", username}, {"password", password}});
  string s = performRequest();
  checkError(s);
  LOG(INFO) << "Login finished";
}

// Sends a learn image request.
// Throws `runtime_error` if it fails.
void User::learnImage() {
  LOG(INFO) << "Learn image started";
  curl_easy_setopt(curl, CURLOPT_URL, LEARN_URL);
  FileManager::Image image = fm.getImage();
  auto lastptr = setForm({{"op", "add_image"}, {"label", image.label},
    {"submit", "send"}});
  attachFileToForm(image.file_path, lastptr);
  string s = performRequest();
  checkError(s);
  LOG(INFO) << "Learn image finished";
}

// Sends a delete image request.
// Throws `runtime_error` if there is no image or it fails.
void User::deleteImage() {
  LOG(INFO) << "Delete image started";
  string s = deleteKnowledge(KnowledgeType::IMAGE);
  checkError(s);
  LOG(INFO) << "Delete image finished";
}

// Sends a learn text request.
// Throws `runtime_error` if it fails.
void User::learnText() {
  LOG(INFO) << "Learn text started";
  curl_easy_setopt(curl, CURLOPT_URL, LEARN_URL);
  setForm({{"op", "add_text"}, {"knowledge", fm.getTextKnowledge()},
    {"submit", "send"}});
  string s = performRequest();
  checkError(s);
  LOG(INFO) << "Learn text finished";
}

// Sends a learn url request.
// Throws `runtime_error` if it fails.
void User::learnUrl() {
  LOG(INFO) << "Learn Url started";
  curl_easy_setopt(curl, CURLOPT_URL, LEARN_URL);
  setForm({{"op", "add_url"}, {"knowledge", fm.getUrlKnowledge()},
    {"submit", "send"}});
  string s = performRequest();
  checkError(s);
  LOG(INFO) << "Learn Url finished";
}

// Sends a delete text (including Url) request.
// Throws `runtime_error` if there is no text or it fails.
void User::deleteTextUrl() {
  LOG(INFO) << "Delete text started";
  string s = deleteKnowledge(KnowledgeType::TEXT);
  checkError(s);
  LOG(INFO) << "Delete text finished";
}

// Sends an infer image request.
// Throws `runtime_error` if it fails.
void User::inferImage() {
  LOG(INFO) << "Infer image started";
  curl_easy_setopt(curl, CURLOPT_URL, INFER_URL);
  auto lastptr = setForm({{"op", "infer"}, {"speech_input", ""}});
  FileManager::Image image = fm.getImage();
  attachFileToForm(image.file_path, lastptr);
  string s = performRequest();
  checkError(s);
  LOG(INFO) << "Infer image finished. Sent " << image.label << ", received " <<
  getInferResult(s);
}

// Sends an infer text request.
// Throws `runtime_error` if it fails.
void User::inferText() {
  LOG(INFO) << "Infer text started";
  curl_easy_setopt(curl, CURLOPT_URL, INFER_URL);
  setForm({{"op", "infer"}, {"speech_input", fm.getTextQuery()}});
  string s = performRequest();
  checkError(s);
  LOG(INFO) << "Infer text finished " << getInferResult(s);
}

// Sends an infer image text request.
// Throws `runtime_error` if it fails.
void User::inferImageText() {
  LOG(INFO) << "Infer image text started";
  curl_easy_setopt(curl, CURLOPT_URL, INFER_URL);
  auto lastptr = setForm({{"op", "infer"},
    {"speech_input", fm.getTextQuery()}});
  FileManager::Image image = fm.getImage();
  LOG(INFO) << "Sent " << image.label;
  attachFileToForm(image.file_path, lastptr);
  string s = performRequest();
  checkError(s);
  LOG(INFO) << "Infer image text finished. Sent " << image.label <<
  ", received " << getInferResult(s);
}

// Sends an infer speech request.
// Throws `runtime_error` if it fails.
void User::inferSpeech() {
  LOG(INFO) << "Infer speech started";
  FILE *fd = fopen(fm.getSpeechQuery().c_str(), "rb");
  if (!fd) {
    throw runtime_error("Open speech file failed!");
  }
  curl_easy_setopt(curl, CURLOPT_URL, INFER_SPEECH_URL);
  curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
  curl_easy_setopt(curl, CURLOPT_READDATA, fd);
  // Force LibCurl not to verify the authencity of peer’s certificate.
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
  string s = performRequest();
  string result = getStrBetween
  (speech_infer_result_start, speech_infer_result_end, s);
  if (result.empty()) {
    throw runtime_error("Infer speech failed! Result: " + s);
  }
  LOG(INFO) << "Infer speech finished " << result;
}

// Sends a request to delete an image or a piece of text
// and returns the HTML content as a string.
// `type` must be either `IMAGE` or `TEXT`.
// Throws `runtime_error` if `type` is wrong, there is no image, or it fails.
string User::deleteKnowledge(KnowledgeType type) {
  string which_id;
  switch (type) {
    case KnowledgeType::IMAGE: {
      which_id = "image_id";
      break;
    }
    case KnowledgeType::TEXT: {
      which_id = "text_id";
      break;
    }
    default: {
      throw runtime_error("Delete type must be either IMAGE or TEXT!");
      break;
    }
  }
  curl_easy_setopt(curl, CURLOPT_URL, LEARN_URL);
  // Find the first piece of text to delete.
  istringstream sstream(performRequest(HTTPRequestType::GET));
  string id;
  for (string line; getline(sstream, line);) {
    if (line.find(which_id) != string::npos) {
      auto start_it = line.find("value=") + strlen("value=");
      auto end_it = line.find("></input>");
      id = line.substr(start_it, end_it - start_it);
      break; // found the text to delete
    }
  }
  if (id.empty()) {
    throw runtime_error("No " + which_id + " to delete!");
  }
  setForm({{"op", "delete_image"}, {which_id, id}, {"submit", "send"}});
  string s = performRequest();
  return s;
}

// Sets the form.
// Returns the pointer to the last item of the form.
struct curl_httppost *User::setForm(const vector<pair<string, string>> &form) {
  // Clear the previous form.
  curl_formfree(formpost);
  // Fill in the form.
  struct curl_httppost *lastptr=NULL;
  for (auto i : form) {
    curl_formadd(&formpost,
     &lastptr,
     CURLFORM_COPYNAME, i.first.c_str(),
     CURLFORM_COPYCONTENTS, i.second.c_str(),
     CURLFORM_END);    
  }
  return lastptr;
}

// Attaches a file to the form.
// Must be called after `setForm()` using its returned pointer as `lastptr`.
void User::attachFileToForm(const string &file_path,
  struct curl_httppost *lastptr) {
  curl_formadd(&formpost,
   &lastptr,
   CURLFORM_COPYNAME, "file",
   CURLFORM_FILE, file_path.c_str(),
   CURLFORM_END);    
}

// Performs the HTTP request and returns the HTML content as a string.
// Throws `runtime_error` if `type` is wrong, or it fails.
string User::performRequest(HTTPRequestType type)
const {
  // Set up the curl option.
  switch (type) {
    case HTTPRequestType::GET: {
      curl_easy_setopt(curl, CURLOPT_HTTPGET, 1); // force using GET
      break;
    }
    case HTTPRequestType::POST: {
      curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
      break;
    }
    default: {
      throw runtime_error("HTTP request type must be either GET or POST!");
      break;
    }
  }
  // Direct the HTML content to a string.
  string s;
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteCallbackFunc);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
  CURLcode res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    throw runtime_error(curl_easy_strerror(res));
  }
  return s;
}

// Throws `runtime_error` if any error occurs in the web page.
// Otherwise, returns true.
bool User::checkError(const string &web_page) const {
  string result = getStrBetween(error_start, error_end, web_page);
  if (!result.empty()) {
    throw runtime_error(result);
  }
  return true;
}

// Returns the infer result in the web page.
// Throws `runtime_error` if the result cannot be found.
string User::getInferResult(const string &web_page) const {
  string result = getStrBetween(infer_result_start, infer_result_end,
    web_page);
  if (result.empty()) {
    cout << web_page;
    throw runtime_error("Infer result cannot be found!");
  }
  return result;
}

// Returns the string content between `start` and `end`
// (HTML tags/JASON strings) in the string.
// Returns an empty string if `start` or `end` cannot be found
// within the same line.
string User::getStrBetween(const char *start, const char *end,
  const string &web_page) const {
  istringstream sstream(web_page);
  for (string line; getline(sstream, line);) {
    auto start_it = line.find(start);
    if (start_it != string::npos) {
      auto end_it = line.find(end);
      start_it += strlen(start);
      if (end_it == string::npos) {
        continue;
      }
      return line.substr(start_it, end_it - start_it);
    }
  }
  return "";
}
