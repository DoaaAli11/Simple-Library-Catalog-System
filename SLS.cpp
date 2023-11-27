//
// Created by Doaa Ali on ١٠/١١/٢٠٢٣.
//

// declarations of the structs' and SLS class's functions

#include <bits/stdc++.h>
#include "SLS.h"

using namespace std;

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

SLS::SLS() {

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

SLS::~SLS() {
}

void SLS::addAuthor()
{
}

void SLS::addBook()
{
    bookFile.open("Books.txt", ios::out | ios:: binary | ios::app | ios::in);

//    int check = binarySearch(authorIds , stoi(author.ID));
//    if( check != -1)
//    {
//        return;
//    }
    bookFile.open("Book.txt" , ios::app);
    bookFile.write((char*)book.ISBN , strlen(book.ISBN));
    bookFile << '|';
    bookFile.write((char *) book.title , strlen(book.title));
    bookFile << '|';
    bookFile.write((char *) book.authorID , strlen(book.authorID));
    bookFile << "\n";
    updateISBNIndex(author.ID, curRecord, true);
    curRecord+=strlen(author.ID) + strlen(author.name) + strlen(author.address) + 3;
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
    bookFile.open("Books.txt", ios::in);
    vector<Book> books;

    bookFile.seekg (0,ios::end);
    long long size = bookFile.tellg();
    bookFile.seekg(0);

    int n = size / 60;
//    cout<<n<<endl;

    for(int i=0;i<n;i++) {
        bookFile.read((char *) &book, sizeof(book));
        books.push_back(book);
    }

    for(Book b:books){
        cout<<"ISBN: "<<b.ISBN<<endl;
        cout<<"Book title: "<<b.title<<endl;
        cout<<"book author ID: "<<b.authorID<<endl;
        cout<<"------------------"<<endl;
    }
}

void SLS::query()
{
}

void SLS::updateISBNIndex(char* isbn, int recSize, bool flag) {
    pISBNFile = fstream("pIndex.txt" , ios::app);
    pISBNFile.write((char*)isbn, strlen(isbn));
    pISBNFile << " ";
    pISBNFile << recSize;
    pISBNFile << "\n";
}


