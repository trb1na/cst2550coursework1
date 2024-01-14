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
    return vectorBook_booksLoaned;
}

void Member::setBooksBorrowed(Book book) {
    if (book.DueDate().time == NULL) {
        int idToRemove = book.bookID();
        vectorBook_booksLoaned.erase(std::remove_if(vectorBook_booksLoaned.begin(), vectorBook_booksLoaned.end(),
            [idToRemove](Book b) { return b.bookID() == idToRemove; }),
            vectorBook_booksLoaned.end());
    }
    else {
        vectorBook_booksLoaned.push_back(book);
    }
}