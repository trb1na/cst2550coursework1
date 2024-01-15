#include "Book.h"
#include "Librarian.h"
#include "Member.h"
#include "Person.h"
#include "globals.h"
#include "utils.h"

std::map<int, Member> Members;
std::map<int, Book> Books;
time_t currentTime = time(nullptr);
Librarian Librarian1 = Librarian(1, std::string("Librarian"), std::string("777 Librarian Road"), std::string("email@gmail.com"), 400000);

int main()
{
    if (loadCSV()) {
        std::cout << "Closing software.";
        return 0;
    }
    
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
                return 0;
            }
    }
}

