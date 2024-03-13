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

int main() {
    std::cout << read_file("input.txt") << "\n";

    return 0;
}
