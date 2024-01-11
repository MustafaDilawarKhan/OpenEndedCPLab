#include <iostream>
#include <string>
using namespace std;

struct Book {
    string name;
    string author;
    int pubYear;
    string genre;
};

void inputBook(Book& book);
void categorizeBooks(Book allBooks[], int size, Book fiction[], Book nonFiction[], int& fictionCount, int& nonFictionCount);
Book findEarliestBook(const Book books[], int size);
void displayBooks(const Book books[], int size, const string& category, const Book& earliestBook);

int main() {
    const int numBooks = 6;
    Book allBooks[numBooks];
    Book fictionBooks[numBooks], nonFictionBooks[numBooks];
    int fictionCount = 0, nonFictionCount = 0;



    for (int i = 0; i < numBooks; ++i) {
        cout << "Enter details for Book " << i + 1 << ":\n";
        inputBook(allBooks[i]);
    }


    categorizeBooks(allBooks, numBooks, fictionBooks, nonFictionBooks, fictionCount, nonFictionCount);

    
    Book earliestFiction = findEarliestBook(fictionBooks, fictionCount);
    Book earliestNonFiction = findEarliestBook(nonFictionBooks, nonFictionCount);


    displayBooks(fictionBooks, fictionCount, "Fiction", earliestFiction);
    displayBooks(nonFictionBooks, nonFictionCount, "Non-Fiction", earliestNonFiction);

    return 0;
}


void inputBook(Book& book) {
    cout << "Book Name: ";
    getline(cin >> ws, book.name);  
    cout << "Author: ";
    getline(cin >> ws, book.author);

    
    do {
        cout << "Publication Year (four digits): ";
        cin >> book.pubYear;

        if (cin.fail() || to_string(book.pubYear).length() != 4) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
            cout << "Invalid input. Please enter a valid four-digit year.\n";
        }
    } while (cin.fail() || to_string(book.pubYear).length() != 4);

   
    int choice;
    bool validChoice = false;

    do {
        cout << "Select Genre:\n";
        cout << "1: Fiction\n";
        cout << "2: Non-fiction\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> choice;

        if (choice == 1) {
            book.genre = "Fiction";
            validChoice = true;
        }
        else if (choice == 2) {
            book.genre = "Non-Fiction";
            validChoice = true;
        }
        else {
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
    } while (!validChoice);

}


void categorizeBooks(Book allBooks[], int size, Book fiction[], Book nonFiction[], int& fictionCount, int& nonFictionCount) {
    fictionCount = 0;
    nonFictionCount = 0;

    for (int i = 0; i < size; ++i) {
        if (allBooks[i].genre == "Fiction") {
            fiction[fictionCount++] = allBooks[i];
        }
        else if (allBooks[i].genre == "Non-Fiction") {
            nonFiction[nonFictionCount++] = allBooks[i];
        }
    }
}


Book findEarliestBook(const Book books[], int size) {
    Book earliestBook = books[0];

    for (int i = 1; i < size; ++i) {
        if (books[i].pubYear < earliestBook.pubYear) {
            earliestBook = books[i];
        }
    }

    return earliestBook;
}


void displayBooks(const Book books[], int size, const string& category, const Book& earliestBook) {
    cout << "\nBooks in " << category << " category:\n" << endl;

    for (int i = 0; i < size; ++i) {
        cout << "Title: " << books[i].name << "\n Author: " << books[i].author << "\n Publication Year: "
            << books[i].pubYear << "\n Genre: " << books[i].genre << "\n";
    }

    cout << "\nEarliest Published Book in " << category << " category:\n";
    cout << "\nTitle: " << earliestBook.name << "\n Author: " << earliestBook.author
        << "\n Publication Year: " << earliestBook.pubYear << "\n Genre: " << earliestBook.genre << "\n";
}