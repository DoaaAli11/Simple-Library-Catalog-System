#include "bits-stdc++.h"
// if you're working on VS code comment #include "SLS.h" and uncomment #include "SLS.cpp"
// if you're working on Clion comment #include "SLS.cpp" and uncomment #include "SLS.h"
//#include "SLS.cpp"
 #include "SLS.h"

using namespace std;

int main()
{            string n ;

    SLS system;
    int choice = 1;
    string isbn;
    cout << "Welcome to our simple library system :)\n\n";
    while (choice != 0)
    {
        cout << "1 - Add New Author\n"
                "2 - Add New Book\n"
                "3 - Update Author Name(Author ID)\n"
                "4 - Update Book Title(ISBN)\n"
                "5 - Delete Author(Author ID)\n"
                "6 - Delete Book (ISBN)\n"
                "7 - Print Author(Author ID)\n"
                "8 - Print Book(ISBN)\n"
                "9 - Write Query\n"
                "0 - Exit\n\n";
        cout << "Enter your choice:";
        cin >> choice;
        switch (choice)
        {
        case 1:
            system.addAuthor();
            break;
        case 2:
            system.addBook();
            break;
        case 3:
            system.updateAuthorName();
            break;
        case 4:
            system.updateBookTitle();
            break;
        case 5:
            system.deleteAuthor();
            break;
        case 6:
            cout << "Enter book ISBN: ";
            char temp[15];
            cin.ignore();
            cin >> temp;
            isbn = temp;
            isbn = string(14 - isbn.length(), '0') + isbn;
            system.deleteBook(isbn);
            break;
        case 7:
            system.printAuthor();
            break;
        case 8:
            system.printBook();
            break;
        case 9:
            system.query();
            break;
        case 0:
            break;
        default:
            cout << "\nWrong input!\nTry again.\n\n";
            break;
        }
    }

    cout << "\nThanks for using our system :)\n";

    return 0;
}
