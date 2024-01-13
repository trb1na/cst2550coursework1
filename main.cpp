#include <iostream>
#include <vector>
#include <limits>
#include <map>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <regex>
#include <ctime>
#include <chrono>

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
            std::cout << "Invalid input. Please enter a valid string.\n";
        }
        else {
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
    std::cout << "\nMade an account with : " << std::endl;
    std::cout << "\nMember ID : " << iMemberid << "\nName : " << 
        strName << "\nAddress : " << strAddress << "\nEmail : " << strEmail << "\n\n";
}

void menuIssueBook() {
    std::regex regexDate(R"(^\d{2}/\d{2}/\d{4}$)");
    int iMemberid = userInput("Member ID: ");
    int iBookid = userInput("Book ID: ");

    std::string strDate = userInput("Due date (DD/MM/YYYY): ", regexDate);
    std::tm date = {};
    std::istringstream ss(strDate);
    char delimiter;
    ss >> date.tm_mday >> delimiter >> date.tm_mon >> delimiter >> date.tm_year;

    if (ss.fail() || delimiter != '/') {
        std::cout << "Invalid date format.\n\n";
    }
    else {
        date.tm_mon -= 1;
        date.tm_year -= 1900; 
        date.tm_hour = 0; date.tm_min = 0; date.tm_sec = 0;

        time_t dueDate = mktime(&date);
        time_t currentTime = time(nullptr);
        time_t minDueDate = currentTime + 24 * 60 * 60;

        if (dueDate != -1 && dueDate >= minDueDate) {
            if (Books[iBookid].DueDate().time == NULL) { 
                Librarian1.issueBook(iMemberid, iBookid);
                Books[iBookid].setDueDate(dueDate);
            }
            else {
                std::cout << "Book has already been issued. \n\n ";
            }
        }
        else {
            std::cout << "Invalid or past date entered. \n\n ";
        }
    }
}

void menuReturnBook() {
    int iMemberid = userInput("Member ID : ");
    int iBookid = userInput("Book ID : ");
    if (Books[iBookid].DueDate().time == NULL) {
        std::cout << "Member does not have this book. \n\n ";
    }
    else {
        Librarian1.returnBook(iMemberid, iBookid);
    }
    
}

void menuDisplayBooks() {
    int iMemberid = userInput("Member ID : ");
    if (Members[iMemberid].booksBorrowed().size() > 0) {
        Librarian1.displayBorrowedBooks(iMemberid);
    }
    else {
        std::cout << "Member has no books \n ";
    }
}

void menuCalculateFines() {
    int iMemberid = userInput("Member ID : ");
    if (Members[iMemberid].booksBorrowed().size() > 0) {
        Librarian1.calcFine(iMemberid);
    }
    else {
        std::cout << "Member has no books \n\n ";
    }
    
}

std::vector<std::string> splitCSV(std::string& line) {
    std::vector<std::string> vecFields;
    std::string strField;
    bool bQuotes = false;

    for (char i : line) {
        if (i == '"') {
            bQuotes = !bQuotes; 
        }
        else if (i == ',' && !bQuotes) {
            vecFields.push_back(strField);
            strField.clear();
        }
        else {
            strField.push_back(i);
        }
    }
    vecFields.push_back(strField); 
    return vecFields;
}


void loadCSV() {
    std::string strFilename;
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (entry.path().extension() == ".csv") {
            strFilename = entry.path().string();
            break;
        }
    }

    std::ifstream file(strFilename);
    if (!file.is_open()) {
        std::cout << "File cannot be opened.\n\n ";
        return;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        auto fields = splitCSV(line);
        if (fields.size() >= 6) {
            try {
                int iBookid = std::stoi(fields[0]);
                std::string strBookName = fields[1];
                std::string strPageCount = fields[2];
                std::string strAuthorFirstName = fields[3];
                std::string strAuthorLastName = fields[4];
                std::string strBookType = fields[5];

                Books.emplace(iBookid, Book(iBookid, strBookName, strAuthorFirstName, strAuthorLastName));
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Invalid argument in CSV line: " << line << "\n\n ";
            }
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
        menuchoice = userInput(" ( 1 ) - Add a member. \n ( 2 ) - Issue a book to a member. \n ( 3 ) - Return a book. \n ( 4 ) - Display all books borrowed by a member. \n ( 5 ) - Calculate overdue fine for a member. \n ( 0 ) - Exit software. \n ~ : ");

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

