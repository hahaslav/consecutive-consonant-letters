#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

int main() {
    std::string text = read_file("input.txt");
    std::cout << text << "\n";

    std::string text_lower;
    int i;
    for (i = 0; i < text.length(); i++) {
        text_lower += toLower(text[i]);
    }
    std::cout << text_lower << "\n";
    return 0;
}
