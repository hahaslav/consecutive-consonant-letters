#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

const int NUMBER_OF_SAME_LETTERS_NEEDED = 2;

std::string read_file(std::string filename = "input.txt") {
    std::ifstream fin(filename);
    std::stringstream buffer;
    buffer << fin.rdbuf();
    fin.close();

    return buffer.str();
}

char to_lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        c = c - ('A' - 'a');
    }
    return c;
}

bool is_letter(char c) {
// assumes the letter is lowercase
    if (c < 'a' || c > 'z') {
        return false;
    }

    return true;
}

bool is_consonant(char c) {
    if (!is_letter(c)) {
        return false;
    }

    if (c == 'e' || c == 'y' || c == 'u' || c == 'i' || c == 'o' || c == 'a') {
        return false;
    }

    return true;
}

class Letter_Counter {
    char last_char;
    std::string word;
    std::vector<std::string> found_words;
    bool good_word = false;
    int number_of_same_letters = 0;

    void separator_actions() {
        if (number_of_same_letters == NUMBER_OF_SAME_LETTERS_NEEDED) {
            good_word = true;
        }
        if (good_word) {
            bool repeated_word = false;
            int i;
            for (i = 0; i < found_words.size(); i++) {
                if (word == found_words[i]) {
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
        last_char = ' ';
    }

    void letter_repetition_check(int set_number_of_same_letters) {
        if (number_of_same_letters == NUMBER_OF_SAME_LETTERS_NEEDED) {
            good_word = true;
            return;
        }
        number_of_same_letters = set_number_of_same_letters;
    }

    void letter_actions(char letter) {
        if (good_word) {
            return;
        }

        // if a vowel
        if (!is_consonant(letter)) {
            letter_repetition_check(0);
        }

        // if the same consonant
        else if (letter == last_char) {
            number_of_same_letters += 1;
        }

        // if another consonant
        else {
            letter_repetition_check(1);
        }

        // in any case
        last_char = letter;
    }
public:
    Letter_Counter() {}

    void read_letter(char letter_lower, char letter) {
        // if a separator
        if (!is_letter(letter_lower)) {
            separator_actions();
            return;
        }

        // if a letter
        word += letter;
        letter_actions(letter_lower);
    }

    std::vector<std::string> get_found_words() {
        return found_words;
    }
};

int main(int argc, char *argv[]) {
    std::string text;
    if (argc > 1) {
        text = read_file(argv[1]);
    } else {
        text = read_file();
    }

    std::string text_lower;
    int i;
    for (i = 0; i < text.length(); i++) {
        text_lower += to_lower(text[i]);
    }
    text_lower += '0'; // to mark the end of the last word

    Letter_Counter letter_counter;
    for (i = 0; i < text_lower.length(); i++) {
        letter_counter.read_letter(text_lower[i], text[i]);
    }

    std::vector<std::string> found_words = letter_counter.get_found_words();
    for (i = 0; i < found_words.size(); i++) {
        std::cout << found_words[i] << "\n";
    }

    return 0;
}
