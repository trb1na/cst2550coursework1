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

void Librarian::addMember(int memberID, std::string name, std::string address,
    std::string email) {
    Members.emplace(memberID, Member(memberID, name, address, email));
}

void Librarian::issueBook(int memberid, int bookid) {
    std::map<int, Book> tempBooksBorrowed = Members[memberid].booksBorrowed();
    tempBooksBorrowed.emplace(Books[bookid].bookID(), Books[bookid]);
    Members[memberid].setBooksBorrowed(tempBooksBorrowed);
}

void Librarian::returnBook(int memberid, int bookid) {
    std::map<int, Book> tempBooksBorrowed = Members[memberid].booksBorrowed();
    tempBooksBorrowed.erase(bookid);
    Members[memberid].setBooksBorrowed(tempBooksBorrowed);
    Books[bookid].returnBook();
}

void Librarian::displayBorrowedBooks(int memberid) {
    std::map<int, Book> tempBooksBorrowed = Members[memberid].booksBorrowed();
    std::cout << "Books Borrowed : \n";
    for (auto& pair : tempBooksBorrowed) {
        std::cout << " - " << pair.second.bookName() << "\n";
        std::cout << "\n\n";
    }
}

void Librarian::calcFine(int memberid) {
    std::map<int, Book> tempBooksBorrowed = Members[memberid].booksBorrowed();
    time_t currentTime = time(nullptr);

    for (auto& pair : tempBooksBorrowed) {
        time_t dueDate = pair.second.DueDate();

        if (dueDate < currentTime) {
            int iDaysOverdue = difftime(currentTime, dueDate) / (60 * 60 * 24);
            int iFineAmount = iDaysOverdue * 10;

            std::cout << "Book ID " << pair.first << " is overdue. Fine: £" << iFineAmount << std::endl;
        }
    }
}

void Librarian::setStaffID(int staffid) {
    i_staffID = staffid;
}

void Librarian::setSalary(int salary) {
    i_salary = salary;
}