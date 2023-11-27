//
// Created by Doaa Ali on ١٠/١١/٢٠٢٣.
//

// declarations of the structs' and SLS class's functions

#include <bits/stdc++.h>
#include "SLS.h"

using namespace std;

void SLS::insertAuthorIndex(int recsize, char *id)
{
    fstream pIndex = fstream("AuthorIDIndex.txt", ios::app);
    pIndex.write((char *)id, strlen(id));
    pIndex << " ";
    pIndex << recsize;
    pIndex << "\n";
}

void SLS::updateISBNIndex(char *isbn, int recSize, bool flag)
{
    pISBNFile.open("ISBNIndex.txt", ios::app);
    pISBNFile.write((char *)isbn, strlen(isbn));
    pISBNFile << " ";
    pISBNFile << 1;
    pISBNFile << "\n";
    pISBNFile.close();
}

int SLS::binarySearch(const vector<int> &iDs, int id)
{
    int left = 0;
    int right = iDs.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (iDs[mid] == id)
        {
            return mid;
        }

        if (iDs[mid] < id)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return -1;
}

void SLS::loadBookIndex()
{
    if (!pISBNFile.is_open())
    {
        pISBNFile.open("ISBNIndex.txt", ios::in);
    }
    if (pISBNFile.peek() == EOF)
    {
        pISBNFile.close();
        return;
    }
    char isbn[15]; // Assuming each name is at most 15 characters long

    while (!pISBNFile.eof())
    {
        pISBNFile >> isbn;

        bookISBN.push_back(stoi(isbn));

        // Move the file pointer to the next line
        pISBNFile.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    pISBNFile.close();
}

Author::Author() {}

Author::Author(char id[15], char n[30], char add[30])
{
    //    used strcpy to copy the char arrays
    strcpy(this->ID, id);
    strcpy(this->name, n);
    strcpy(this->address, add);
}

Book::Book() {}

Book::Book(char isbn[15], char t[30], char aID[15])
{
    strcpy(this->ISBN, isbn);
    strcpy(this->title, t);
    strcpy(this->authorID, aID);
}

SLS::SLS()
{
}

SLS::SLS(Author a)
{
    this->author = a;
}

SLS::SLS(Book b)
{
    this->book = b;
}

SLS::SLS(Author a, Book b)
{
    this->author = a;
    this->book = b;
}

SLS::~SLS()
{
}

void SLS::addAuthor()
{

    int check = binarySearch(authorIds, stoi(author.ID));
    if (check != -1)
    {
        return;
    }

    authorFile.open("file.txt", ios::app);
    authorFile.write((char *)author.ID, strlen(author.ID));
    authorFile << '|';
    authorFile.write((char *)author.name, strlen(author.name));
    authorFile << '|';
    authorFile.write((char *)author.address, strlen(author.address));
    authorFile << "\n";
    insertAuthorIndex(recsize, author.ID);
    recsize += strlen(author.ID) + strlen(author.name) + strlen(author.address) + 3;
    authorFile.close();
}

void SLS::addBook()
{
    cout << "Enter book ISBN: ";
    char isbn[15];
    cin.ignore();
    cin >> isbn;

    loadBookIndex();

    int check = binarySearch(bookISBN, stoi(isbn));
    if (check != -1)
    {
        cout << "A book with ISBN " << isbn << " exist.\n";
        return;
    }

    cout << "Enter book title: ";
    char t[15];
    cin.ignore();
    cin >> t;

    cout << "Enter book author ID: ";
    char aid[15];
    cin.ignore();
    cin >> aid;

    this->book = Book(isbn, t, aid);

    curRecord = strlen(book.ISBN) + strlen(book.title) + strlen(book.authorID) + 3;

    bookFile.open("Book.txt", ios::app);

    bookFile << curRecord;
    bookFile << '|';
    bookFile.write((char *)book.ISBN, strlen(book.ISBN));
    bookFile << '|';
    bookFile.write((char *)book.title, strlen(book.title));
    bookFile << '|';
    bookFile.write((char *)book.authorID, strlen(book.authorID));
    bookFile << "\n";

    updateISBNIndex(book.ISBN, curRecord, true);

    bookFile.flush();
    bookFile.close();
}

void SLS::updateAuthorName()
{
}

void SLS::updateBookTitle()
{
}

void SLS::deleteAuthor()
{
}

void SLS::deleteBook()
{
}

void SLS::printAuthor()
{
}

void SLS::printBook()
{
    bookFile.open("Book.txt", ios::in);

    string line;

    while (getline(bookFile, line))
    {
        stringstream ss(line);
        int length;
        char isbn[15];
        char title[30];
        char aid[15];

        ss >> length;
        ss.ignore();
        ss.getline(isbn, 15, '|');
        ss.getline(title, 30, '|');
        ss.getline(aid, 15);

        cout << "ISBN: " << isbn << ", title: " << title << ", aID: " << aid << endl;
    }
    bookFile.close();
}

void SLS::query()
{
}
