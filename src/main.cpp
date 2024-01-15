#include "../includes/Book.h"
#include "../includes/Librarian.h"
#include "../includes/Member.h"
#include "../includes/Person.h"
#include "../includes/globals.h"
#include "../includes/utils.h"

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
        menuchoice = userInput(" ( 1 ) - Add a member. \n ( 2 ) - Issue a book to a member. \n ( 3 ) - Return a book. \n ( 4 ) - Display all books borrowed by a member. \n ( 5 ) - Calculate overdue fine for a member. \n ( 0 ) - Exit software. \n ~ : ", std::cin, std::cout);

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

