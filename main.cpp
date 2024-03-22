#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

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
    for (i = 0; i < text_lower.length(); i++) {
        std::cout << text_lower[i] << ' ' << isLetter(text_lower[i]) << ' ' << isConsonant(text_lower[i]) << "\n";
    }

    return 0;
}
