#include "User.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string.h>
#include <glog/logging.h>

using namespace std;

// URLs to send requests.
const char * const LOGIN_URL = "https://clarity13.eecs.umich.edu:30000/login";
const char * const LEARN_URL = "https://clarity13.eecs.umich.edu:30000/learn";
const char * const INFER_URL = "https://clarity13.eecs.umich.edu:30000/infer";

// Initialize static variables.
int User::num_users = 0;

// Call back function for curl.
size_t curlWriteCallbackFunc(void *contents, size_t size, size_t nmemb,
  string *s) {
  size_t new_length = size * nmemb;
  size_t old_length = s->size();
  s->resize(old_length + new_length);
  std::copy((char*) contents,(char*) contents + new_length,
    s->begin() + old_length);
  return size * nmemb;
}

void User::login() {
  curl_easy_setopt(curl, CURLOPT_URL, LOGIN_URL);
  string cookie_file_name = "cookies" + to_string(unique_id);
  cookie_file_name += ".txt";
  curl_easy_setopt(curl, CURLOPT_COOKIEJAR, cookie_file_name.c_str());
  setForm({{"username", username}, {"password", password}});
  string s = performRequest();
}

void User::learnImage() {
  curl_easy_setopt(curl, CURLOPT_URL, LEARN_URL);
  auto lastptr = setForm({{"op", "add_image"}, {"label", "Italy"},
    {"submit", "send"}});
  attachFileToForm("0.jpg", lastptr);
  string s = performRequest();
}

void User::deleteImage() {
  deleteKnowledge(KnowledgeType::IMAGE);
}

void User::deleteText() {
  deleteKnowledge(KnowledgeType::TEXT);
}

void User::learnText() {
  curl_easy_setopt(curl, CURLOPT_URL, LEARN_URL);
  setForm({{"op", "add_text"}, {"knowledge", "The capital of Italy is Rome."},
    {"submit", "send"}});
  string s = performRequest();
}

void User::learnUrl() {
  curl_easy_setopt(curl, CURLOPT_URL, LEARN_URL);
  setForm({{"op", "add_url"}, {"knowledge",
    "https://en.wikipedia.org/wiki/Orange"}, {"submit", "send"}});
  string s = performRequest();
}

void User::inferImage() {
  curl_easy_setopt(curl, CURLOPT_URL, INFER_URL);
  auto lastptr = setForm({{"op", "infer"}});
  attachFileToForm("0.jpg", lastptr);
  string s = performRequest();
  cout << s;
}

void User::inferText() {
  curl_easy_setopt(curl, CURLOPT_URL, INFER_URL);
  setForm({{"op", "infer"}, {"speech_input", "Where is the capital of Italy?"}});
  string s = performRequest();
}

void User::inferImageText() {
  curl_easy_setopt(curl, CURLOPT_URL, INFER_URL);
  auto lastptr = setForm({{"op", "infer"}, {"speech_input", "Where is the capital of this?"}});
  attachFileToForm("0.jpg", lastptr);
  string s = performRequest();
  cout << s;
}

void User::deleteKnowledge(KnowledgeType type) {
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
  LOG(INFO) << "Deleting " << which_id << " " << id;
  setForm({{"op", "delete_image"}, {which_id, id}, {"submit", "send"}});
  string s = performRequest();
}

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

void User::attachFileToForm(const string &file_path,
  struct curl_httppost *lastptr) {
  curl_formadd(&formpost,
   &lastptr,
   CURLFORM_COPYNAME, "file",
   CURLFORM_FILE, file_path.c_str(),
   CURLFORM_END);    
}

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
