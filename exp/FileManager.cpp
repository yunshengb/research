#include "FileManager.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <cstring>
#include <cstddef>
#include <dirent.h>

using namespace std;

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
  cout << images.size() << " images added to file manager" << endl;
  // Load text knowledge.
  // Text is stored in "text/".
  loadFileLineByLineToVector("text/text_knowledge.txt", text_knowledge);
  cout << text_knowledge.size() << " pieces of text knowledge added "
  "to file manager" << endl;
  // Load url knowledge.
  // Text is stored in "text/".
  loadFileLineByLineToVector("text/url_knowledge.txt", url_knowledge);
  cout << url_knowledge.size() << " pieces of url knowledge added "
  "to file manager" << endl;
  // Load text queries.
  // Text is stored in "text/".
  loadFileLineByLineToVector("text/queries.txt", text_queries);
  cout << text_queries.size() << " pieces of queries added "
  "to file manager" << endl;
  // Load speech queries.
  // Speech queries are stored in "speech/".
  vector<pair<string, string>> speech_files = loadFilesInDirectory("speech");
  for (const auto &p : speech_files) {
    speech_queries.push_back(p.first); // only use the file path
  }
  cout << speech_queries.size() << " speech queries added to file manager" <<
  endl;
}

// Returns a random object from the vector.
// Throws `runtime_error` if the vector is empty.
template<typename T>
T FileManager::getRandomObject(const vector<T> &vec) const {
  if (vec.empty()) {
    throw runtime_error("Cannot get random object from empty vector!");
  }
  srand(time(NULL));
  return vec[rand() % vec.size()];
}

// Returns a random image.
FileManager::Image FileManager::getImage() const {
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
  static int i = 0;
  if (i >= int(text_queries.size())) {
    throw runtime_error("No more text queries!");
  }
  string rtn = text_queries[i];
  ++i;
  return rtn;
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
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir(dir_name.c_str())) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      string file_path = ent->d_name;
      assert(!file_path.empty());
      string stemmed_file_name;
      char* p;
      char* totken = strtok_r(&file_path[0], ".", &p);
      while(totken != NULL) {
        stemmed_file_name = totken;
        break;
      }
      files.push_back(make_pair(file_path, stemmed_file_name));
    }
    closedir(dir);
  } else {
    throw runtime_error(dir_name + " could not be opned!");
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
