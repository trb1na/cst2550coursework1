#include "Book.h"


Book::Book(int bookid, std::string bookname, std::string authorfirstname,
    std::string authorlastname, std::string booktype) {
    i_bookID = bookid;
    str_bookName = bookname;
    str_authorFirstName = authorfirstname;
    str_authorLastName = authorlastname;
    str_bookType = booktype;
}

Book::Book() {};

int Book::bookID() {
    return i_bookID;
}

std::string Book::bookName() {
    return str_bookName;
}

std::string Book::AuthorFirsName() {
    return str_authorFirstName;
}

std::string Book::AuthorLastName() {
    return str_authorLastName;
}

time_t Book::DueDate() {
    return str_dueDate;
}

void Book::setDueDate(time_t duedate) {
    str_dueDate = duedate;
}

void Book::returnBook() {
    str_dueDate = NULL;
}

void Book::borrowBook(Member borrower, time_t duedate) {
    str_dueDate = duedate;
    member_borrower = borrower;
}