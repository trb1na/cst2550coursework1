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
}

void Librarian::displayBorrowedBooks(int memberid) {
    std::map<int, Book> tempBooksBorrowed = Members[memberid].booksBorrowed();
    for (auto& pair : tempBooksBorrowed) {
        std::cout << pair.second.bookName();
    }
}

void Librarian::calcFine(int memberid) {

    time(&currentTime);
    time_t futureTime = currentTime + 3 * 24 * 60 * 60;
    tm futureLocalTime;
    localtime_s(&futureLocalTime, &futureTime);

    int day = futureLocalTime.tm_mday;
    int month = futureLocalTime.tm_mon + 1;
    int year = futureLocalTime.tm_year + 1900;

    std::cout << "Future Date: " << day << "/" << month << "/" << year << std::endl;
}

void Librarian::setStaffID(int staffid) {
    i_staffID = staffid;
}

void Librarian::setSalary(int salary) {
    i_salary = salary;
}