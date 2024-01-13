#include "Librarian.h"
#include "globals.h"
#include "Member.h"
#include "Book.h"
#include <iostream>

Librarian::Librarian(int staffid, std::string name, std::string address,
    std::string email, int salary) {
    i_salary = salary;
    i_staffID = staffid;
    str_address = address;
    str_email = email;
    str_name = name;
}

Librarian::Librarian() {};

int Librarian::staffID() {
    return i_staffID;
}

int Librarian::salary() {
    return i_salary;
}

void Librarian::addMember() {
    
}

void Librarian::issueBook(int memberid, int bookid) {
    Members[memberid].setBooksBorrowed(Books[bookid]);
}

void Librarian::returnBook(int memberid, int bookid) {
    Members[memberid].setBooksBorrowed(Books[bookid]);
}

void Librarian::displayBorrowedBooks(int memberid) {
    std::vector<Book> tempBooksBorrowed = Members[memberid].booksBorrowed();
    std::cout << "Books Borrowed : \n";
    for (auto& book : tempBooksBorrowed) {
        std::cout << " - " << book.bookName() << "\n";
        std::cout << "\n\n";
    }
}

void Librarian::calcFine(int memberid) {
    std::vector<Book> tempBooksBorrowed = Members[memberid].booksBorrowed();
    time_t currentTime = time(nullptr);

    for (auto& book : tempBooksBorrowed) {
        time_t dueDate = book.DueDate().time;

        if (dueDate < currentTime) {
            int iDaysOverdue = difftime(currentTime, dueDate) / (60 * 60 * 24);
            int iFineAmount = iDaysOverdue * 10;

            std::cout << "Book ID " << book.bookID() << " is overdue. Fine: £" << iFineAmount << std::endl;
        }
    }
}

void Librarian::setStaffID(int staffid) {
    i_staffID = staffid;
}

void Librarian::setSalary(int salary) {
    i_salary = salary;
}