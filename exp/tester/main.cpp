#include "User.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

using namespace std;

// Function declarations.
void testASR(User &user);
void testQA(User &user);
void testCL(User &user);
string getString(const string &enter_what);

// Function implementations.
int main() {
    // Start interacting with the console.
    // Keep looping until the quit command is invoked.
    User user("yba", "cookies0");
    user.login();
    while (true) {
        try {
            // Prompt the user and read command letters.
            cout << "\nEnter command: ";
            string action_letters;
            getline(cin, action_letters);
            if (action_letters == "qq") {
                cout << "Done\n";
                return 0; // program exits
            }
            if (action_letters == "ta") {
                testASR(user);
            } else if (action_letters == "tq") {
                testQA(user);
            } else if (action_letters == "tcl") {
                testCL(user);
            } else {
                throw runtime_error("Unrecognized command " + action_letters + \
                                    "\nPlease type 'enter' to continue");
            }
        } catch (const runtime_error &e) {
            cout << e.what() << "\n";
            cin.clear();
            while (cin.get() != '\n'); // skips the rest of the input line
        } catch (...) {
            cout << "Unknown exception caught!\n";
            return 0;
        }
    }
}

// Tests the ASR.
void testASR(User &user) {
    string file_path = getString("audio file path");
    user.inferSpeech(file_path);
}

// Tests the QA.
void testQA(User &user) {
    string text_query = getString("text query");
    user.output_file << "audio_file_path,query" << endl;
    user.inferText(text_query);
}

// Tests the query classifier.
void testCL(User &user) {
    string text_query = getString("text query");
    string file_path = getString("image file path");
    user.inferTestClassifier(text_query, file_path);
}

// Gets and returns a string from cin with the prompt "\nEnter <enter_what>: ".
string getString(const string &enter_what) {
    cout << "\nEnter " << enter_what << ": ";
    string rtn;
    getline(cin, rtn);
    return rtn;
}
