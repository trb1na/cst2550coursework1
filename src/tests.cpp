#define CATCH_CONFIG_MAIN

#include "../includes/Book.h"
#include "../includes/Date.h"
#include "../includes/globals.h"
#include "../includes/Librarian.h"
#include "../includes/Member.h"
#include "../includes/Person.h"
#include "../includes/utils.h"
#include "../includes/catch.hpp"


//Librarian
TEST_CASE("Librarian constructor, setters and getters.") {
	Librarian librarian(1, "Librarian", "123 Librarian street", "Librarian@library.com", 50000);
	INFO("Testing constructor with initial values")
	REQUIRE(librarian.staffID() == 1);
	REQUIRE(librarian.name() == "Librarian");
	REQUIRE(librarian.email() == "Librarian@library.com");
	REQUIRE(librarian.address() == "123 Librarian street");
	REQUIRE(librarian.salary() == 50000);

	librarian.setStaffID(2);
	librarian.setName("NewName");
	librarian.setEmail("NewEmail@email.com");
	librarian.setAddress("New Address");
	librarian.setSalary(100000);

	INFO("Testing setters for staffid, name, email, address, and salary.")
	REQUIRE(librarian.staffID() == 2);
	REQUIRE(librarian.name() == "NewName");
	REQUIRE(librarian.email() == "NewEmail@email.com");
	REQUIRE(librarian.address() == "New Address");
	REQUIRE(librarian.salary() == 100000);
}

TEST_CASE("issueBook and returnBook function") {
	Members.clear();
	Books.clear();
	Members.emplace(1, Member(1, "Name", "Address", "Email"));
	Books.emplace(1, Book(1, "Book Title", "Author Name", "Author Surname"));

	Librarian librarian;

	SECTION("issueBook") {
		Books[1].setDueDate({ 3 });
		librarian.issueBook(1, 1);

		REQUIRE(Members[1].booksBorrowed().size() == 1);
	}

	SECTION("returnBook") {
		librarian.returnBook(1, 1);

		REQUIRE(Members[1].booksBorrowed().size() == 0);
		REQUIRE(Books[1].DueDate().time == 0);
	}
}

TEST_CASE("calcFine function") {
	time_t currentTime = time(nullptr);

	Members.clear();
	Books.clear();

	Members.emplace(1, Member(1, "Name", "Address", "Email"));
	Books.emplace(1, Book(1, "Book Title", "Author Name", "Author Surname"));

	Librarian librarian;

	SECTION("No Fine") {
		time_t futureTime = currentTime + (24 * 60 * 60); 
		Books[1].setDueDate({ futureTime });
		Members[1].setBooksBorrowed(Books[1]);

		std::ostringstream capturedOutput;
		std::streambuf* originalCoutBuffer = std::cout.rdbuf();
		std::cout.rdbuf(capturedOutput.rdbuf());

		librarian.calcFine(1);

		std::cout.rdbuf(originalCoutBuffer);

		REQUIRE(capturedOutput.str() == "No Fines. \n\n");
	}

	SECTION("Fine") {
		time_t pastTime = currentTime - (7 * 24 * 60 * 60); 
		Books[1].setDueDate({ pastTime });
		Members[1].setBooksBorrowed(Books[1]);

		std::ostringstream capturedOutput;
		std::streambuf* originalCoutBuffer = std::cout.rdbuf();
		std::cout.rdbuf(capturedOutput.rdbuf());

		librarian.calcFine(1);

		std::cout.rdbuf(originalCoutBuffer);

		std::string expectedOutput = "Book ID 1 is overdue. Fine: �70\n\nTotal Fine : 70\n\n";
		REQUIRE(capturedOutput.str() == expectedOutput);
	}
}

//Member
TEST_CASE("Member constructor, setters and getters") {
	Member member(1, "Member", "123 Member street", "Member@member.com");
	INFO("Testing constructor with initial values")
	REQUIRE(member.memberID() == "1");
	REQUIRE(member.name() == "Member");
	REQUIRE(member.address() == "123 Member street");
	REQUIRE(member.email() == "Member@member.com");
	
	Book book;
	book.setDueDate({0});

	member.setAddress("New Address");
	member.setBooksBorrowed(book);
	member.setEmail("NewEmail@email.com");
	member.setName("NewName");

	INFO("Testing setters for name, address, and email.");
	REQUIRE(member.name() == "NewName");
	REQUIRE(member.address() == "New Address");
	REQUIRE(member.email() == "NewEmail@email.com");

	INFO("Testing setbooksBorrowed after setting a book with no due date.");
	REQUIRE(member.booksBorrowed().size() == 0);
	
	book.setDueDate({ 1 });
	member.setBooksBorrowed(book);

	INFO("Testing booksBorrowed after setting a book with a due date.");
	REQUIRE(member.booksBorrowed().size() == 1);
}
//Book


TEST_CASE("Book constructor, setters and getters") {
	Book book(1, "Book Title", "Author Name", "Author Surname");
	INFO("Testing constructor with initial values.")
	REQUIRE(book.bookID() == 1);
	REQUIRE(book.bookName() == "Book Title");
	REQUIRE(book.AuthorFirsName() == "Author Name");
	REQUIRE(book.AuthorLastName() == "Author Surname");

	book.setDueDate({ 1 });
	INFO("Testing setDueDate and DueDate with value 1");
	REQUIRE(book.DueDate().time == 1);

	book.returnBook();
	INFO("Testing returnBook with dueDate value 1")
	REQUIRE(book.DueDate().time == 0);

	Member member;
	book.borrowBook(member, { 3 });
	INFO("Testing borrowBook with dueDate value 3")
	REQUIRE(book.DueDate().time == 3);
}

