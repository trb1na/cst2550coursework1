#include "Librarian.h"

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

}

void Librarian::returnBook(int memberid, int bookid) {

}

void Librarian::displayBorrowedBooks(int memberid) {

}

void Librarian::calcFine(int memberid) {

}

void Librarian::setStaffID(int staffid) {
    i_staffID = staffid;
}

void Librarian::setSalary(int salary) {
    i_salary = salary;
}