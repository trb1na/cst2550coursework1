#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <regex>

int userInput(std::string message);
std::string userInput(const std::string& message, const std::regex pattern);

#endif 
