#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <map>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <regex>
#include <ctime>
#include <chrono>

int userInput(std::string message);
std::string userInput(const std::string& message, const std::regex pattern);
void menuAddMember();
void menuIssueBook();
void menuReturnBook();
void menuDisplayBooks();
void menuCalculateFines();
std::vector<std::string> splitCSV(std::string& line);
int loadCSV();

#endif 
