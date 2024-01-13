#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include <map>
#include <ctime>
#include "Time.h"

class Member;
class Book;

extern std::map<int, Book>  Books; 
extern std::map<int, Member> Members;
extern time_t currentTime;

extern struct Time;

#endif 
