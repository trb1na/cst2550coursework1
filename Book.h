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
  std::string str_dueDate;
  Member member_borrower;

public:
  Book(int bookid, std::string bookname, std::string authorfirstname,
       std::string authorlastname, std::string booktype);
  Book();

  int bookID();
  std::string bookName();
  std::string AuthorFirsName();
  std::string AuthorLastName();
  std::string DueDate();

  void setDueDate(std::string duedate);
  void returnBook();
  void borrowBook(Member borrower, std::string duedate);
};

#endif 
