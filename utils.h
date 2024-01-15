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

int userInput(std::string message, std::istream& in, std::ostream& out);
std::string userInput(std::string message, std::regex pattern, std::istream& in, std::ostream& out);
void menuAddMember();
void menuIssueBook();
void menuReturnBook();
void menuDisplayBooks();
void menuCalculateFines();
std::vector<std::string> splitCSV(std::string& line);
int loadCSV();

#endif 
