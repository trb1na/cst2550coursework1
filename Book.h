#ifndef BOOK_H
#define BOOK_H

#include <string>

#include "Member.h"


class Book {
private:

  int i_bookID;
  std::string str_bookName;
  std::string str_authorFirstName;
  std::string str_authorLastName;
  std::string str_bookType;
  time_t str_dueDate;
  Member member_borrower;

public:
  Book(int bookid, std::string bookname, std::string authorfirstname,
       std::string authorlastname, std::string booktype);
  Book();

  int bookID();
  std::string bookName();
  std::string AuthorFirsName();
  std::string AuthorLastName();
  time_t DueDate();

  void setDueDate(time_t duedate);
  void returnBook();
  void borrowBook(Member borrower, time_t duedate);
};

#endif 
