#include "../includes/Librarian.h"
#include "../includes/globals.h"
#include "../includes/Member.h"
#include "../includes/Book.h"
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
    int iMemberid = userInput("Member ID : ", std::cin, std::cout);
    if (Members.count(iMemberid) == 0) {
        std::regex regexName("^[A-Za-z]+(?:[ '-][A-Za-z]+)*$");
        std::regex regexEmail(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
        std::regex regexAddress("(?=.*[a-zA-Z])(?=.*[0-9]).+");

        std::string strName = userInput("Name : ", regexName, std::cin, std::cout);
        std::string strAddress = userInput("Address : ", regexAddress, std::cin, std::cout);
        std::string strEmail = userInput("Email : ", regexEmail, std::cin, std::cout);

        Members.emplace(iMemberid, Member(iMemberid, strName, strAddress, strEmail));

        std::cout << "\nMade an account with : " << std::endl;
        std::cout << "\nMember ID : " << iMemberid << "\nName : " <<
            strName << "\nAddress : " << strAddress << "\nEmail : " << strEmail << "\n\n";
    }
    else {
        std::cout << "Member with this id already exists.";
    }
}

void Librarian::issueBook(int memberid, int bookid) {
    Members[memberid].setBooksBorrowed(Books[bookid]);
}

void Librarian::returnBook(int memberid, int bookid) {
    Books[bookid].setDueDate({0});
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

    int iTotalFine = 0;
    for (auto& book : tempBooksBorrowed) {
        time_t dueDate = book.DueDate().time;

        if (dueDate < currentTime) {
            int iDaysOverdue = difftime(currentTime, dueDate) / (60 * 60 * 24);
            int iFineAmount = iDaysOverdue * 10;
            iTotalFine += iFineAmount;
            std::cout << "Book ID " << book.bookID() << " is overdue. Fine: �" << iFineAmount << "\n\n";
        }
    }
    if (iTotalFine > 0) {
        std::cout << "Total Fine : " << iTotalFine  << "\n\n";
    } else {
        std::cout << "No Fines. \n\n";
    }
    

}

void Librarian::setStaffID(int staffid) {
    i_staffID = staffid;
}

void Librarian::setSalary(int salary) {
    i_salary = salary;
}