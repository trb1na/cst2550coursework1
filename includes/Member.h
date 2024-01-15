#ifndef MEMBER_H
#define MEMBER_H

#include <vector>
#include <map>

#include "Person.h"

class Book;

class Member : public Person {
private:

  int i_memberID;
  std::vector<Book> vectorBook_booksLoaned;

public:
  Member(int memberID, std::string name, std::string address,
         std::string email);

  Member();

  std::string memberID();
  std::vector<Book> booksBorrowed();
  void setBooksBorrowed(Book book);
};

#endif
