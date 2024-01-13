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

std::string Member::memberID() {
    return std::to_string(i_memberID);
}

std::vector<Book> Member::booksBorrowed() {
    return mapBook_booksLoaned;
}

void Member::setBooksBorrowed(Book book) {
    mapBook_booksLoaned = book;
}