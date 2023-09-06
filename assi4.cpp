#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

enum Genre {
    Fiction,
    NonFiction,
    Periodical,
    Inspirational,
    Children
};

class Book {
private:
    string ISBN;
    string title;
    string author;
    int copyrightDate;
    bool checkedOut;
    Genre genre;

public:
    Book(const string& isbn, const string& title, const string& author, int copyrightDate, Genre genre)
        : ISBN(isbn), title(title), author(author), copyrightDate(copyrightDate), checkedOut(false), genre(genre) {}

    string getISBN() const { return ISBN; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getCopyrightDate() const { return copyrightDate; }
    bool isCheckedOut() const { return checkedOut; }
    Genre getGenre() const { return genre; }

    void checkOut() { checkedOut = true; }
    void checkIn() { checkedOut = false; }

    bool operator==(const Book& other) const {
        return ISBN == other.ISBN;
    }

    bool operator!=(const Book& other) const {
        return !(*this == other);
    }

    friend ostream& operator<<(ostream& os, const Book& book) {
        os << "Title: " << book.title << "\nAuthor: " << book.author << "\nISBN: " << book.ISBN << "\nGenre: ";
        switch (book.getGenre()) {
        case Fiction: os << "Fiction"; break;
        case NonFiction: os << "Non-Fiction"; break;
        case Periodical: os << "Periodical"; break;
        case Inspirational: os << "Inspirational"; break;
        case Children: os << "Children"; break;
        default: os <<"Invalid genre";
        };
        return os;
    }
};

class Patron {
private:
    string userNname;
    string cardNumber;
    int ownedFees;

public:
    Patron(string u, string c, int f) : userNname(u), cardNumber(c), ownedFees(f) {}

    string getUserName() const { return userNname; }
    string getCardNumber() const { return cardNumber; }
    int getOwnedFees() const { return ownedFees; }

    bool owesFees() const {
        return ownedFees > 0;
    }

    void setFees(int f) {
        if (f >= 0) {
            ownedFees = f;
        }
    }

    bool operator==(const Patron& other) const {
        return cardNumber == other.cardNumber;
    }
};

class Transaction {
private:
    Book book;
    Patron patron;
    string activity;
    string date;

public:
    Transaction(Book& b, Patron& p, string a, string d) : book(b), patron(p), activity(a), date(d) {}
};

class Library {
private:
    vector<Book> books;
    vector<Patron> patrons;
    vector<Transaction> transactions;
    vector<Patron> debtors;

public:
    void addBook(Book& book) {
        books.push_back(book);
    }

    void addPatron(Patron& p) {
        patrons.push_back(p);
    }

    vector<Patron> debtorsFinder() {
        debtors.clear(); // Clear the debtors vector
        for (auto i : patrons) {
            if (i.owesFees()) {
                debtors.push_back(i);
            }
        }
        return debtors;
    }

    void checkOut(Patron& patron, Book& book, string activity, string date) {
        debtorsFinder();
        auto bookIter = find(books.begin(), books.end(), book);
        auto patronIter = find(patrons.begin(), patrons.end(), patron);

        if (patronIter == patrons.end() || bookIter == books.end()) {
            cout << "Error: the user or the book is not registered." << endl;
        } else if (find(debtors.begin(), debtors.end(), patron) != debtors.end()) {
            cout << "The user owes fees." << endl;
        } else {
            Transaction tran1(book, patron, activity, date);
            transactions.push_back(tran1);
            cout << "Activity recorded" << endl;
        }
    }
};

int main() {
    Book book1("978-0-12-345678-9", "The Rules Of Life", "Richard Templar", 2023, Inspirational);
    Book book2("978-9-87-654321-0", "Flawed", "Cecilia Ahern", 2022, NonFiction);
    Patron person1("Horan", "0281918", 0);
    Library library;

    library.addBook(book1);
    library.addBook(book2);
    library.addPatron(person1);
    library.checkOut(person1, book1, "checkOut", "0/0/2023");

    cout << "Book 1:\n" << book1 << endl << endl;
    cout << "Book 2:\n" << book2 << endl << endl;

    if (book1 == book2) {
        cout << "Book 1 and Book 2 have the same ISBN." << endl;
    } else {
        cout << "Book 1 and Book 2 have different ISBNs." << endl;
    }

    return 0;
}

