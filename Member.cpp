#include "Member.h"
#include "Book.h"

Member::Member(int memberid, std::string name, std::string address,
    std::string email) {
    i_memberID = memberid;
    str_name = name;
    str_address = address;
    str_email = email;
}

Member::Member() {};

int Member::memberID() {
    return i_memberID;
}

std::map<int, Book> Member::booksBorrowed() {
    return mapBook_booksLoaned;
}

void Member::setBooksBorrowed(std::map<int, Book> books) {
    mapBook_booksLoaned = books;
}