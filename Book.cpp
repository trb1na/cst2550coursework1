#include "Book.h"
#include "globals.h"

Book::Book(int bookid, std::string bookname, std::string authorfirstname,
    std::string authorlastname) {
    i_bookID = bookid;
    str_bookName = bookname;
    str_authorFirstName = authorfirstname;
    str_authorLastName = authorlastname;
    str_dueDate.time = NULL;
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

Date Book::DueDate() {
    return str_dueDate;
}

void Book::setDueDate(Date duedate) {
    str_dueDate = duedate;
}

void Book::returnBook() {
    str_dueDate.time = NULL;
}

void Book::borrowBook(Member borrower, Date duedate) {
    str_dueDate = duedate;
    member_borrower = borrower;
}