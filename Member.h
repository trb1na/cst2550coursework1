#ifndef MEMBER_H
#define MEMBER_H

#include <vector>
#include <map>

#include "Person.h"

class Book;

class Member : public Person {
private:

  int i_memberID;
  std::map<int, Book> mapBook_booksLoaned;

public:
  Member(int memberID, std::string name, std::string address,
         std::string email);
  Member();

  int memberID();

  std::map<int, Book> booksBorrowed();
  void setBooksBorrowed(std::map<int, Book> books);
};

#endif
