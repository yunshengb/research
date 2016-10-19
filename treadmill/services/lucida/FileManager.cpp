#include "FileManager.h"
#include <stdexcept>
#include <iostream>
#include <boost/filesystem.hpp>
#include <algorithm>
#include <glog/logging.h>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstddef>

using namespace std;
using namespace boost::filesystem;

// Constructor.
// Throws `runtime_error` if it cannot load the files.
FileManager::FileManager() {
  // Load images.
  // Images are stored in "image/".
  // Use the stemmed file name as label.
  vector<pair<string, string>> image_files = loadFilesInDirectory("image");
  for (const auto &p : image_files) {
    images.push_back(Image(p.first, p.second));
  }
  sort(images.begin(), images.end());
  LOG(INFO) << images.size() << " images added to file manager";
  // Load text knowledge.
  // Text is stored in "text/".
  loadFileLineByLineToVector("text/text_knowledge.txt", text_knowledge);
  LOG(INFO) << text_knowledge.size() << " pieces of text knowledge added "
  "to file manager";
  // Load url knowledge.
  // Text is stored in "text/".
  loadFileLineByLineToVector("text/url_knowledge.txt", url_knowledge);
  LOG(INFO) << url_knowledge.size() << " pieces of url knowledge added "
  "to file manager";
  // Load text queries.
  // Text is stored in "text/".
  loadFileLineByLineToVector("text/queries.txt", text_queries);
  LOG(INFO) << text_queries.size() << " pieces of queries added "
  "to file manager";
  // Load speech queries.
  // Speech queries are stored in "speech/".
  vector<pair<string, string>> speech_files = loadFilesInDirectory("speech");
  for (const auto &p : speech_files) {
    speech_queries.push_back(p.first); // only use the file path
  }
  LOG(INFO) << speech_queries.size() << " speech queries added to file manager";
}

// Returns a random object from the vector.
template<typename T>
T FileManager::getRandomObject(const vector<T> &vec) const {
  srand(time(NULL));
  return vec[rand() % vec.size()];
}

// Returns a random image.
const FileManager::Image FileManager::getImage() const {
  return getRandomObject(images);
}

// Returns a random piece of text knowledge.
const string FileManager::getTextKnowledge() const {
  return getRandomObject(text_knowledge);
}

// Returns a random piece of Url knowledge.
const string FileManager::getUrlKnowledge() const {
  return getRandomObject(url_knowledge);
}

// Returns a random piece of text query.
const string FileManager::getTextQuery() const {
  return getRandomObject(text_queries);
}

// Returns a random piece of speech (file path) query.
const string FileManager::getSpeechQuery() const {
  return getRandomObject(speech_queries);
}

// Loads all the files in the directory and returns a vector:
// the first entry of the pair stores the file path;
// the second entry of the pair stores the file stemmed file name.
// Throws `runtime_error` if it fails.
vector<pair<string, string>>
FileManager::loadFilesInDirectory(const string &dir_name) {
  vector<pair<string, string>> files;
  path p(dir_name);
  try {
    if (exists(p)) {
      if (is_directory(p)){
        directory_iterator end_iter;
        for (directory_iterator dir_itr(p); dir_itr != end_iter; ++dir_itr) {
          string file_path = dir_itr->path().string();
          string stemmed_file_name = dir_itr->path().stem().string();
          files.push_back(make_pair(file_path, stemmed_file_name));
        }
      } else {
        throw runtime_error(dir_name + " should be a directory!");
      }
    } else {
      throw runtime_error(dir_name + " does not exist!");
    }
  } catch (const filesystem_error &e) {
    throw runtime_error(e.what());
  }
  return files;
}

// Loads the file into the vector line by line.
// Throws `runtime_error` if the file cannot be opened.
void FileManager::loadFileLineByLineToVector(const string &file_name,
  vector<string> &vec) {
  ifstream input_file(file_name.c_str()); 
  if (!input_file.is_open()) {
    throw runtime_error("Cannot open " + file_name);
  }
  for(string line; getline(input_file, line);) {
   vec.push_back(line);
 }
}
