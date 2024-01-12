#include <iostream>
#include <vector>
#include <limits>
#include <map>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <regex>
#include <ctime>

#include "Book.h"
#include "Librarian.h"
#include "Member.h"
#include "Person.h"
#include "globals.h"

namespace fs = std::filesystem;

std::map<int, Member> Members;
std::map<int, Book> Books;
time_t currentTime = time(nullptr);

Librarian Librarian1 = Librarian(1, std::string("Librarian"), std::string("777 Librarian Road"), std::string("email@gmail.com"), 400000);

int userInput(std::string message) {
    int tempInput;
    while (true) {
        std::cout << message;
        std::cin >> tempInput;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number. \n";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            break;
        }
    }
    return tempInput;
}

std::string userInput(const std::string& message, const std::regex pattern) {
    std::string tempInput;
    while (true) {
        std::cout << message;
        if (!std::getline(std::cin, tempInput) || !std::regex_match(tempInput, pattern)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid string.\n";
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    return tempInput;
}

void menuAddMember() {
    std::regex temp("^[A-Za-z]+(?:[ '-][A-Za-z]+)*$");
    int iMemberid = userInput("Member ID : ");
    std::string strName = userInput("Name : ",temp);
    std::string strAddress = userInput("Address : ",temp);
    std::string strEmail = userInput("Email : ",temp);
    Members.emplace(iMemberid, Member(iMemberid, strName, strAddress, strEmail));
    std::cout << "Made an account with : " << std::endl;
    std::cout << "Member ID : " << iMemberid << "Name : " << 
        strName << "Address : " << strAddress << "Email : " << strEmail << std::endl;
}

void menuIssueBook() {
    int iMemberid = userInput("Member ID : ");
    int iBookid = userInput("Book ID : ");
    Librarian1.issueBook(iMemberid, iBookid);
}

void menuReturnBook() {
    int iMemberid = userInput("Member ID : ");
    int iBookid = userInput("Book ID : ");
    Librarian1.returnBook(iMemberid, iBookid);
}

void menuDisplayBooks() {
    int iMemberid = userInput("Member ID : ");
    Librarian1.displayBorrowedBooks(iMemberid);
}

void menuCalculateFines() {
    int iMemberid = userInput("Member ID : ");
    Librarian1.calcFine(iMemberid);
}

void loadCSV() {

    std::string filename;
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (entry.path().extension() == ".csv") {
            filename = entry.path().string();
            break;
        }
    }
    
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("File cannot be opened.");
    }
    else {
        std::string line;

        while (std::getline(file, line)) {
            std::stringstream ss(line);

            int iBookid;
            std::string strBookName;
            std::string strPageCount;
            std::string strAuthorFirstName;
            std::string strAuthorLastName;
            std::string strBookType;
            char delimiter = ',';

            ss >> iBookid;
            ss.ignore();
            std::getline(ss, strBookName, delimiter);
            std::getline(ss, strPageCount, delimiter);
            std::getline(ss, strAuthorFirstName, delimiter);
            std::getline(ss, strAuthorLastName, delimiter);
            std::getline(ss, strBookType, delimiter);

            Books.emplace(iBookid, Book(iBookid, strBookName, strAuthorFirstName, strAuthorLastName, strBookType));
        }
    }
}

int main()
{
    loadCSV();
    int menuchoice;
    while (true)
    {
        std::cout << "Select an Option : \n";
        menuchoice = userInput(" ( 1 ) - Add a member. \n ( 2 ) - Issue a book to a member. \n ( 3 ) - Return a book. \n ( 4 ) - Display all books borrowed by a member. \n ( 5 ) - Calculate overdue fine for a member. \n ( 0 ) - Exit software.");

            switch (menuchoice) {
            case 1:
                menuAddMember();
                break;
            case 2:
                menuIssueBook();
                break;
            case 3:
                menuReturnBook();
                break;
            case 4:
                menuDisplayBooks();
                break;
            case 5:
                menuCalculateFines();
                break;
            case 0:
                break;
            }
    }

    return 0;
}

