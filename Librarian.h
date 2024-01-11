#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include <string>
#include "Person.h"


class Librarian : public Person {
private:

  int i_staffID;
  int i_salary;

public:

  Librarian(int staffid, std::string name, std::string address,
            std::string email, int salary);

  Librarian();

  int staffID();
  int salary();

  void addMember();
  void issueBook(int memberid, int bookid);
  void returnBook(int memberid, int bookid);
  void displayBorrowedBooks(int memberid);
  void calcFine(int memberid);
  void setStaffID(int staffid);
  void setSalary(int salary);
};

#endif