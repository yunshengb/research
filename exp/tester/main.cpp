#include "User.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

using namespace std;

// Function declarations.
void testASR(User &user);
void testQA(User &user);
void testSA();

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
            } else if (action_letters == "SA") {
                testSA();
            } else {
                throw runtime_error("Unrecognized command " + action_letters);
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

// Test the ASR.
void testASR(User &user) {
    cout << "\nEnter audio file path: ";
    string file_path;
    getline(cin, file_path);
    user.inferSpeech(file_path);
}

// Test the QA.
void testQA(User &user) {
    cout << "\nEnter text query: ";
    string text_query;
    getline(cin, text_query);
    user.inferText(text_query);
}

// Test the SA.
void testSA() {
    
}
