#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cctype>
#include <string>

using namespace std;

bool isConsonant(char c) {
    string consonants = "bcdfghjklmnpqrstvwxyz";
    return consonants.find(tolower(c)) != string::npos;
}

vector<string> splitWord(const string& word) {
    vector<string> substrings;
    string currentWord = "";

    for (char c : word) {
        if (isalpha(c)) {
            currentWord += c;
        } else {
            if (!currentWord.empty()) {
                substrings.push_back(currentWord);
                currentWord = "";
            }
            substrings.push_back(string(1, c));
        }
    }

    if (!currentWord.empty()) {
        substrings.push_back(currentWord);
    }

    return substrings;
}

string findLongestConsonantSubstring(const string& word) {
    string longestSubstring = "";
    string currentSubstring = "";

    for (char c : word) {
        if (isConsonant(c)) {
            currentSubstring += c;
        } else {
            if (currentSubstring.length() > longestSubstring.length()) {
                longestSubstring = currentSubstring;
            }
            currentSubstring = "";
        }
    }

    if (currentSubstring.length() > longestSubstring.length()) {
        longestSubstring = currentSubstring;
    }

    return longestSubstring;
}

int main() {
    string filename = "text.txt";
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cout << "Error opening the file." << endl;
        return 1;
    }

    string word;
    string longestConsonantSubstring;
    set<string> wordsWithLongestSubstring;

    while (inputFile >> word) {
        vector<string> substrings = splitWord(word);

        string currentLongestSubstring = "";
        string concatenatedWord = "";

        for (const string& substring : substrings) {
            if (isalpha(substring[0])) {
                string substringConsonants = findLongestConsonantSubstring(substring);

                if (substringConsonants.length() > currentLongestSubstring.length()) {
                    currentLongestSubstring = substringConsonants;
                    concatenatedWord = substring;
                }
            } else {
                if (substring.length() > currentLongestSubstring.length()) {
                    currentLongestSubstring = substring;
                }
            }
            if (concatenatedWord.length() >= 30) {
                cout << "Word '" << word << "' is longer than 30 characters. Skipping." << endl;
                continue;
            }
            if (currentLongestSubstring.length() > longestConsonantSubstring.length()) {
                longestConsonantSubstring = currentLongestSubstring;
                wordsWithLongestSubstring.clear();
                wordsWithLongestSubstring.insert(concatenatedWord);
            } else if (currentLongestSubstring.length() == longestConsonantSubstring.length()) {
                wordsWithLongestSubstring.insert(concatenatedWord);
            }
        }


    }

    cout << "Words with the longest consonant substring (" << longestConsonantSubstring.length() << "):" << endl;
    for (const string& word : wordsWithLongestSubstring) {
        cout << word << endl;
    }

    inputFile.close();

    return 0;
}
