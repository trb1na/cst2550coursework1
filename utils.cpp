#include "utils.h"
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

int userInput(std::string message, std::istream& in, std::ostream& out) {
    int tempInput;
    while (true) {
        out << message;
        in >> tempInput;
        if (in.fail()) {
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            out << "Invalid input. Please enter a number. \n";
        }
        else {
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    out << "\n";
    return tempInput;
}

std::string userInput(std::string message, std::regex pattern, std::istream& in, std::ostream& out) {
    std::string tempInput;
    while (true) {
        out << message;
        if (!std::getline(in, tempInput) || !std::regex_match(tempInput, pattern)) {
            in.clear();
            out << "Invalid input. Please enter a valid string.\n";
        }
        else {
            break;
        }
    }
    out << "\n";
    return tempInput;
}

void menuAddMember() {
    Librarian1.addMember();
}

void menuIssueBook() {
    int iMemberid = userInput("Member ID: ", std::cin, std::cout);
    if (Members.count(iMemberid) <= 0) {
        std::cout << "\nMember with this id does not exist. \n\n";
        return;
    }

    int iBookid = userInput("Book ID : ", std::cin, std::cout);
    if (Books.count(iBookid) <= 0) {
        std::cout << "\nBook with this id does not exist. \n\n";
        return;
    }

    if (Books[iBookid].DueDate().time != NULL) {
        std::cout << "\nBook has already been issued. \n\n ";
        return;
    }

    std::tm* pTmDate;
    time_t rawCurrentTime = currentTime;
    pTmDate = localtime(&rawCurrentTime);

    std::tm date = *pTmDate;

    date.tm_mday += 3;
    time_t dueDate = mktime(&date);

    Books[iBookid].setDueDate({ dueDate });
    Librarian1.issueBook(iMemberid, iBookid);
}

void menuReturnBook() {
    int iMemberid = userInput("Member ID : ", std::cin, std::cout);
    if (Members.count(iMemberid) <= 0) {
        std::cout << "\nMember with this id does not exist. \n\n";
        return;
    }

    int iBookid = userInput("Book ID : ", std::cin, std::cout);
    if (Books.count(iBookid) <= 0) {
        std::cout << "\nBook with this id does not exist. \n\n";
        return;
    }
    std::vector tempBooks = Members[iMemberid].booksBorrowed();

    auto it = std::find_if(tempBooks.begin(), tempBooks.end(),
        [iBookid](Book book) { return book.bookID() == iBookid; });

    if (it == tempBooks.end()) {
        std::cout << "\nMember does not have this book. \n\n ";
        return;
    }

    Librarian1.returnBook(iMemberid, iBookid);
    std::cout << "Book : " << Books[iBookid].bookName() << ", has been returned. \n\n";
}

void menuDisplayBooks() {
    int iMemberid = userInput("Member ID : ",std::cin, std::cout);
    if (Members.count(iMemberid) <= 0) {
        std::cout << "\nMember with this id does not exist. \n\n";
        return;
    }

    if (Members[iMemberid].booksBorrowed().empty()) {
        std::cout << "\nMember has no books. \n\n ";
        return;
    }

    Librarian1.displayBorrowedBooks(iMemberid);
}

void menuCalculateFines() {
    int iMemberid = userInput("Member ID : ", std::cin, std::cout);
    if (Members.count(iMemberid) <= 0) {
        std::cout << "\nMember does not exist. \n\n";
        return;
    }

    if (Members[iMemberid].booksBorrowed().empty()) {
        std::cout << "\nMember has no books. \n\n ";
        return;
    }

    Librarian1.calcFine(iMemberid);
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

int loadCSV() {
    std::string strFilename;
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (entry.path().extension() == ".csv") {
            strFilename = entry.path().string();
            break;
        }
    }

    std::ifstream file(strFilename);
    if (!file.is_open()) {
        std::cout << "\nFile cannot be opened.\n\n ";
        return 1;
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
                std::cerr << "\nInvalid argument in CSV line: " << line << "\n\n ";
            }
        }
    }
    return 0;
}