/*
 * Author: Joseph Neubert
 * Description: Assignment where I must add comments to document each and every class and function.
 */

// Imports
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Book Class
class Book
{
    int id;
    std::string title;
    std::string author;
    bool available;

public:
    // Book Class Constructor
    Book(int id, const std::string &title, const std::string &author)
        : id(id), title(title), author(author), available(true) {}

    // Returns Book ID
    int getId() const { return id; }

    // Returns Book Title
    const std::string &getTitle() const { return title; }

    // Returns Book Author Name
    const std::string &getAuthor() const { return author; }

    // Returns Book Availability Boolean
    bool isAvailable() const { return available; }

    // Marks a Book as Borrowed
    void markBorrowed() { available = false; }

    // Marks a Book as Returned
    void markReturned() { available = true; }
};

// Library Member Class
class Member
{
    int id;
    std::string name;

public:
    // Member Class Constructor
    Member(int id, const std::string &name) : id(id), name(name) {}

    // Returns Member ID Number
    int getId() const { return id; }

    // Returns Member Name
    const std::string &getName() const { return name; }
};

// Book Loan Class
class Loan
{
    int memberId;
    int bookId;
    int dueDay; // very simplified "date" as an integer day

public:
    // Loan Class Constructor
    Loan(int memberId, int bookId, int dueDay)
        : memberId(memberId), bookId(bookId), dueDay(dueDay) {}

    // Returns Member ID of the Borrowing Member
    int getMemberId() const { return memberId; }

    // Returns Book ID of the Borrowed Book
    int getBookId() const { return bookId; }

    // Returns the Integer Due Date of the Borrowed Book
    int getDueDay() const { return dueDay; }

    // Returns the Boolean of Whether the Book Loan is Currently Overdue or Not
    bool isOverdue(int today) const
    {
        return today > dueDay;
    }
};

// Library Class
class Library
{
    std::vector<Book> books;
    std::vector<Member> members;
    std::vector<Loan> loans;

public:
    // Accepts Book Object as Parameter in order to Append the Book to the Books Vector
    void addBook(const Book &book)
    {
        books.push_back(book);
    }

    // Accepts Member Object as Parameter in order to Append the Member to the Members Vector
    void addMember(const Member &member)
    {
        members.push_back(member);
    }

    // Accepts Book Title String as Parameter, Returns the First Available Book Object from the Vector with a Matching Title (or Null Pointer if None Available are Found)
    Book *findAvailableBookByTitle(const std::string &title)
    {
        for (auto &book : books)
        {
            if (book.getTitle() == title && book.isAvailable())
            {
                return &book;
            }
        }
        return nullptr;
    }

    // Accepts Member ID as Parameter, Returns the First Member Object from the Vector with the Same ID (or Null Pointer if None are Found)
    Member *findMemberById(int id)
    {
        for (auto &m : members)
        {
            if (m.getId() == id)
                return &m;
        }
        return nullptr;
    }

    // Accepts Member ID, Book ID, and Due Date as Parameters in order to Construct then Append a Book Loan to the Loans Vector
    void addLoan(int memberId, int bookId, int dueDay)
    {
        loans.emplace_back(memberId, bookId, dueDay);
    }

    // Function that Prints to Console Details for Each Loan in the Loans Vector Including Member ID, Book ID, and Due Date
    void printLoans() const
    {
        std::cout << "\nCurrent loans:\n";
        for (const auto &loan : loans)
        {
            std::cout << " Member ID " << loan.getMemberId()
                      << " has Book ID " << loan.getBookId()
                      << " due on day " << loan.getDueDay() << "\n";
        }
    }
};

// Librarian Class
class Librarian
{
public:
    // Accepts Member Objects as a Parameter, Returns Boolean of Whether Member is Currently Permitted to Borrow from the Library
    bool canBorrow(const Member &member)
    {
        // In a real system, check fines, limits, etc.
        // For now, everyone is allowed.
        (void)member; // Suppress unused parameter warning.
        return true;
    }

    // Accepts Library Object, Member ID, Book Title, and Today's Date as Parameters, Returns Boolean Depending on Whether the Loan is Successful or Not
    bool borrowBook(Library &library, int memberId, const std::string &title,
                    int today)
    {
        // Returns False if Member not Found by ID
        Member *member = library.findMemberById(memberId);
        if (!member)
        {
            std::cout << "Member not found.\n";
            return false;
        }
        // Returns False if Member Found is Disallowed from further Borrowing
        if (!canBorrow(*member))
        {
            std::cout << "Member is not allowed to borrow.\n";
            return false;
        }
        // Returns False if No Available Copy of Book is Found by Title
        Book *book = library.findAvailableBookByTitle(title);
        if (!book)
        {
            std::cout << "No available copy of \"" << title << "\".\n";
            return false;
        }
        // Append Loan to Library Loan Vector, and Return True
        // Simple due date: 14 days from today
        int dueDay = today + 14;
        book->markBorrowed();
        library.addLoan(member->getId(), book->getId(), dueDay);
        std::cout << member->getName() << " successfully borrowed \""
                  << book->getTitle() << "\". Due day: " << dueDay << "\n";
        return true;
    }
};

// Main
int main()
{
    Library library;
    Librarian librarian;
    // Setup sample data
    library.addBook(Book(1, "Clean Code", "Robert C. Martin"));
    library.addBook(Book(2, "Clean Code", "Robert C. Martin"));
    library.addBook(Book(3, "Design Patterns", "Gamma et al."));
    library.addMember(Member(100, "Alice"));
    library.addMember(Member(101, "Bob"));
    int today = 1;
    // Scenario: Alice borrows "Clean Code"
    librarian.borrowBook(library, 100, "Clean Code", today);
    // Bob borrows "Clean Code" as well (second copy)
    librarian.borrowBook(library, 101, "Clean Code", today);
    // Third attempt should fail (no more available copies)
    librarian.borrowBook(library, 101, "Clean Code", today);
    // Print all created loans
    library.printLoans();

    return 0;
}