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

SLS::SLS() {}

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

SLS::~SLS() {}

void SLS::openFile(fstream file, string fileName)
{
    file.open(fileName, ios::in | ios::out | ios::app | ios::binary);
}

void SLS::closeFile(fstream file)
{
    file.close();
}

void SLS::readFromFile(fstream file)
{
}

void SLS::writeToFile(fstream file)
{
}

void SLS::addAuthor()
{
}

void SLS::addBook()
{
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
}

void SLS::query()
{
}
