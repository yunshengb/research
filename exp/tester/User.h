#ifndef USER_h
#define USER_h

#include <string>
#include <curl/curl.h>
#include <stdexcept>
#include <vector>
#include <fstream>

// A class for representing a User.
class User {
public:
    // Constructor.
    User(const std::string &username_, const std::string &password_);
    
    // Destructor.
    ~User();
    
    // Sends a login request.
    // Must be called before other requests.
    // Throws `runtime_error` if it fails.
    void login();
    
    // Sends a learn image request.
    // Throws `runtime_error` if it fails.
    void learnImage(const std::string &label, const std::string &file_path);
    
    // Sends a delete image request.
    // Throws `runtime_error` if there is no image or it fails.
    void deleteImage();
    
    // Sends a learn text request.
    // Throws `runtime_error` if it fails.
    void learnText(const std::string &text_knowledge);
    
    // Sends a learn url request.
    // Throws `runtime_error` if it fails.
    void learnUrl(const std::string &url_knowledge);
    
    // Sends a delete text (including Url) request.
    // Throws `runtime_error` if there is no text or it fails.
    void deleteTextUrl();
    
    // Sends an infer image request.
    // Throws `runtime_error` if it fails.
    void inferImage(const std::string &label, const std::string &file_path);
    
    // Sends an infer text request.
    // Throws `runtime_error` if it fails.
    void inferText(const std::string &text_query);
    
    // Sends an infer image text request.
    // Throws `runtime_error` if it fails.
    void inferImageText(const std::string &label, const std::string &file_path,
                        const std::string &text_query);
    
    // Sends an infer speech request.
    // Throws `runtime_error` if it fails.
    void inferSpeech(const std::string &file_path);
    
    // Sends an test classifier request.
    // Throws `runtime_error` if it fails.
    void inferTestClassifier(const std::string &text_query,
                             const std::string &file_path);
    
    // The type of knowledge.
    enum class KnowledgeType {
        IMAGE, TEXT, URL
    };
    
    // Type of HTTP request.
    enum class HTTPRequestType {
        GET, POST
    };
    
private:
    // Output file.
    std::ofstream output_file;
    
    // The username.
    const std::string username;
    
    // The password.
    const std::string password;
    
    // The unique ID of the user.
    const int unique_id;
    
    // The number of users that have been created.
    static int num_users;
    
    // Curl handle.
    CURL *curl = nullptr;
    
    // Curl form.
    struct curl_httppost *formpost = nullptr;
    
    std::string deleteKnowledge(KnowledgeType type);
    struct curl_httppost *setForm
    (const std::vector<std::pair<std::string, std::string>> &form);
    void attachFileToForm(const std::string &file_path,
                          struct curl_httppost *lastptr);
    std::string performRequest(HTTPRequestType type = HTTPRequestType::POST)
    const;
    bool checkError(const std::string &web_page) const;
    std::string getInferResult(const std::string &web_page) const;
    std::string getStrBetween(const char *start, const char *end,
                              const std::string &str) const;
    std::string getFileName(const std::string &base_file_name) const;
};

#endif /* USER_h */
