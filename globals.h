#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include <map>
#include <ctime>

class Member;
class Book;

extern std::map<int, Book>  Books; 
extern std::map<int, Member> Members;
extern time_t currentTime;

#endif 
