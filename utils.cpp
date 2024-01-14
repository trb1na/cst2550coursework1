#include "utils.h"

int userInput(std::string message) {
    int tempInput;
    while (true) {
        std::cout << message;
        std::cin >> tempInput;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number. \n";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    std::cout << "\n";
    return tempInput;
}

std::string userInput(const std::string& message, const std::regex pattern) {
    std::string tempInput;
    while (true) {
        std::cout << message;
        if (!std::getline(std::cin, tempInput) || !std::regex_match(tempInput, pattern)) {
            std::cin.clear();
            std::cout << "Invalid input. Please enter a valid string.\n";
        }
        else {
            break;
        }
    }
    std::cout << "\n";
    return tempInput;
}