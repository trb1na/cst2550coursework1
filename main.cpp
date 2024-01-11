#include <iostream>
#include <vector>
#include <limits>
#include <map>
#include <regex>

#include "Book.h"
#include "Librarian.h"
#include "Member.h"
#include "Person.h"
#include "globals.h"

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
            break;
        }
    }
    return tempInput;
}

void menuAddMember() {
    std::regex temp("");
    int iMemberid = userInput("");
    std::string strName = userInput("",temp);
    std::string strAddress = userInput("",temp);
    std::string strEmail = userInput("",temp);
    Members.emplace(iMemberid, Member(iMemberid, strName, strAddress, strEmail));
}

void menuIssueBook() {

}

void menuReturnBook() {

}

void menuDisplayBooks() {

}

void menuCalculateFines() {

}

int main()
{
    int menuchoice;
    while (true)
    {
        std::cout << "Select an Option : \n";
        menuchoice = userInput("( 1 ) - Add a member. \n ( 2 ) - Issue a book to a member. \n ( 3 ) - Return a book. \n ( 4 ) - Display all books borrowed by a member. \n ( 5 ) - Calculate overdue fine for a member. \n ( 0 ) - Exit software.");

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

