#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
// Forward declarations
class Book;
class Patron;

class Book {
private:
    string ISBN;
    string Title;
    string Author;
    int CopyrightDate;
    bool CheckedOut;
    string Genre;

public:
    Book(string isbn, string title, string author, int copyrightDate, string genre);
    string getISBN() const;
    string getTitle() const;
    string getAuthor() const;
    int getCopyrightDate() const;
    bool isCheckedOut() const;
    void checkOut();
    void checkIn();
    string getGenre() const;
    bool operator==(const Book& other) const;
    bool operator!=(const Book& other) const;
    friend ostream& operator<<(ostream& os, const Book& book);
};

class Patron {
private:
    string UserName;
    string CardNumber;
    int OwedFees;

public:
    Patron(string userName, string cardNumber);
    string getUserName() const;
    string getCardNumber() const;
    int getOwedFees() const;
    bool owesFees() const;
    void setOwedFees(int fees);
};

class Transaction {
private:
    Book BookRef;
    Patron PatronRef;
    string Activity;
    string Date;

public:
    Transaction(const Book& book, const Patron& patron, string activity, string date);
};

class Library {
private:
    vector<Book> Books;
    vector<Patron> Patrons;
    vector<Transaction> Transactions;

public:
    void addBook(const Book& book);
    void addPatron(const Patron& patron);
    void checkOutBook(const Book& book, const Patron& patron, string date);
    vector<string> getOwingPatrons() const;
};

// Implement class member functions here

int main() {
    // Example usage
    Library library;

    Book book1("123456", "Sample Book 1", "Author A", 2020, "Fiction");
    Book book2("654321", "Sample Book 2", "Author B", 2015, "Nonfiction");

    Patron patron1("User1", "P123");
    Patron patron2("User2", "P456");

    library.addBook(book1);
    library.addBook(book2);
    library.addPatron(patron1);
    library.addPatron(patron2);

    library.checkOutBook(book1, patron1, "2023-08-24");
    library.checkOutBook(book2, patron2, "2023-08-25");

    vector<string> owingPatrons = library.getOwingPatrons();

    cout << "Owing Patrons:\n";
    for (vector<string>::iterator it = owingPatrons.begin(); it != owingPatrons.end(); ++it) {
        cout << *it << endl;
    }

    return 0;
}


