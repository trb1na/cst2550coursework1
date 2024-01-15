#ifndef BOOK_H
#define BOOK_H

#include <string>

#include "Member.h"
#include "Date.h"


class Book {
private:

  int i_bookID;

  std::string str_bookName;
  std::string str_authorFirstName;
  std::string str_authorLastName;
  std::string str_bookType;

  Date str_dueDate;
  Member member_borrower;

public:

  Book(int bookid, std::string bookname, std::string authorfirstname,
       std::string authorlastname);
  Book();

  int bookID();
  std::string bookName();
  std::string AuthorFirsName();
  std::string AuthorLastName();

  Date DueDate();
  void setDueDate(Date duedate);
  void returnBook();
  void borrowBook(Member borrower, Date duedate);
};

#endif 
