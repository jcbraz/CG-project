#include <iostream>
#include <string>

std::string receiveInput(std::string &input) {
    std::cout << "Enter a string: ";
    std::cin >> input;
    return input;
}

int main() {
    std::string input;
    receiveInput(input);
    std::cout << "You entered: " << input << std::endl;
    return 0;
}
