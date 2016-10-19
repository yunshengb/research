#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include <utility>

// A class for representing a file manager.
class FileManager {
public:
  // Constructor.
  // Throws `runtime_error` if it cannot load the files.
  FileManager();

  // An image.
  class Image {
  public:
    Image(const std::string &file_path_, const std::string &label_) :
    file_path(file_path_), label(label_) {}
    std::string file_path;
    std::string label;
    bool operator<(const Image &rhs) const {
      return file_path < rhs.file_path;
    }
  };

  // Returns a random image.
  const Image getImage() const;

  // Returns a random piece of text knowledge.
  const std::string getTextKnowledge() const;

  // Returns a random piece of Url knowledge.
  const std::string getUrlKnowledge() const;

  // Returns a random piece of text query.
  const std::string getTextQuery() const;

  // Returns a random piece of speech (file path) query.
  const std::string getSpeechQuery() const;

private:
  std::vector<Image> images;
  std::vector<std::string> text_knowledge;
  std::vector<std::string> url_knowledge;
  std::vector<std::string> text_queries;
  std::vector<std::string> speech_queries;
  std::vector<std::pair<std::string, std::string>>
  loadFilesInDirectory(const std::string &dir_name);
  void loadFileLineByLineToVector(const std::string &file_name,
    std::vector<std::string> &vec);
  template<typename T>
  T getRandomObject(const std::vector<T> &vec) const;
};

#endif /* FILEMANAGER_H */
