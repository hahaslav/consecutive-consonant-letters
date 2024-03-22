#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

const int NUMBER_OF_SAME_LETTERS_NEEDED = 2;

std::string read_file(std::string filename) {
    std::ifstream fin(filename);
    std::stringstream buffer;
    buffer << fin.rdbuf();
    fin.close();

    return buffer.str();
}

char toLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        c = c - ('A' - 'a');
    }
    return c;
}

bool isLetter(char c) {
// assumes the letter is lowercase
    if (c < 'a' || c > 'z') {
        return false;
    }

    return true;
}

bool isConsonant(char c) {
    if (!isLetter(c)) {
        return false;
    }

    if (c == 'e' || c == 'y' || c == 'u' || c == 'i' || c == 'o' || c == 'a') {
        return false;
    }

    return true;
}

int main() {
    std::string text = read_file("input.txt");

    std::string text_lower;
    int i;
    for (i = 0; i < text.length(); i++) {
        text_lower += toLower(text[i]);
    }
    text_lower += '0'; // to add the end of the last word

    char last_char;
    std::string word;
    std::vector<std::string> found_words;
    bool good_word = false;
    int number_of_same_letters = 0;
    for (i = 0; i < text_lower.length(); i++) {
        // if a separator
        if (!isLetter(text_lower[i])) {
            if (number_of_same_letters == NUMBER_OF_SAME_LETTERS_NEEDED) {
                good_word = true;
            }
            if (good_word) {
                bool repeated_word = false;
                for (int j = 0; j < found_words.size(); j++) {
                    if (word == found_words[j]) {
                        repeated_word = true;
                        break;
                    }
                }
                if (!repeated_word) {
                    found_words.push_back(word);
                }
            }
            number_of_same_letters = 0;
            word = "";
            good_word = false;
        }
        // if a letter
        else {
            word += text[i];
            if (good_word) {
                continue;
            }
            // if a vowel
            if (!isConsonant(text_lower[i])) {
                if (number_of_same_letters == NUMBER_OF_SAME_LETTERS_NEEDED) {
                    good_word = true;
                    continue;
                } else {
                    number_of_same_letters = 0;
                }
            }
            // if the same consonant
            else if (text_lower[i] == last_char) {
                number_of_same_letters += 1;
            }
            // if another consonant
            else if (number_of_same_letters == NUMBER_OF_SAME_LETTERS_NEEDED) {
                good_word = true;
                continue;
            } else {
                number_of_same_letters = 1;
            }
        }
        // in any case, except good_word = true
        last_char = text_lower[i];
    }

    for (i = 0; i < found_words.size(); i++) {
        std::cout << found_words[i] << "\n";
    }

    return 0;
}
