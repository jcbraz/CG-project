#include <cstring>
#include <iostream>
#include <string>
#include <vector>

struct Input {
    std::string graphicType;
    int radious;
    int slices;
    int stacks;
    std::string outputFile;
};

Input parseInput(char commmands[]) {
    char *parsedInput = std::strtok(commmands, " ");
    std::vector<std::string> parsedInputs;
    while (parsedInput != nullptr) {
        parsedInputs.push_back(parsedInput);
        parsedInput = std::strtok(nullptr, " ");
    }

    struct Input instructions_recieved;
    instructions_recieved.graphicType = parsedInputs[1];
    instructions_recieved.radious = std::stoi(parsedInputs[2]);
    instructions_recieved.slices = std::stoi(parsedInputs[3]);
    instructions_recieved.stacks = std::stoi(parsedInputs[4]);
    instructions_recieved.outputFile = parsedInputs[5];

    return instructions_recieved;
}

int main() {
    char commands[] = "generator sphere 1 10 10 sphere.3d";
    Input input = parseInput(commands);
    std::cout << "Graphic type: " << input.graphicType << '\n';
    std::cout << "Radius: " << input.radious << '\n';
    std::cout << "Slices: " << input.slices << '\n';
    std::cout << "Stacks: " << input.stacks << '\n';
    std::cout << "Output file: " << input.outputFile << '\n';
    return 0;
}
