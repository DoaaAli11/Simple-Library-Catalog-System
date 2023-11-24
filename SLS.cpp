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
    openFile(bookFile, "Books.txt");
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
    closeFile(bookFile);
}

void SLS::openFile(fstream& file, string fileName)
{
    file.open(fileName, ios::in | ios::out | ios::app | ios::binary);
}

void SLS::closeFile(fstream& file)
{
    file.close();
}

//void SLS::readFromFile(fstream& file)
//{
//}
//
//void SLS::writeToFile(fstream& file,const char ojc[])
//{
//    file.write(ojc,sizeof(ojc));
//}

void SLS::addAuthor()
{
}

void SLS::addBook()
{
    char isbn[15], t[30], aid[15];
    cin.ignore();
    cout<<"Enter book's ISBN:";
    cin.getline(isbn, 15);
    cout<<"Enter book's title:";
    cin.getline(t, 30);
    cout<<"Enter book's author's ID:";
    cin.getline(aid, 15);

    this->book = Book(isbn, t, aid);

    bookFile.write((char*)& book, sizeof(book));
    cout<<"\nBook added successfully.\n\n";
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
