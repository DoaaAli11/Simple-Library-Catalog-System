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
    bookFile.open("Books.txt", ios::out | ios:: binary | ios::app | ios::in);
    // Check if the file is open
    if (!bookFile.is_open()) {
        cout << "Error opening file\n";
        return;
    }

//    if (bookFile.peek() == EOF)
//    {
//        char* size = "0";
//        char* AVAIL = "-1";
//        bookFile.write(size,sizeof (size));
//        bookFile << "|";
//        bookFile.write(AVAIL,sizeof (AVAIL));
//        bookFile << "\n";
//
//    }

    char isbn[15], t[30], aid[15];
    cin.ignore();
    cout << "Enter book's ISBN:";
    cin >> isbn;
    cout << "Enter book's title:";
    cin >> t;
    cout << "Enter book's author's ID:";
    cin >> aid;

    this->book = Book(isbn, t, aid);

    // Write data as binary structure
    bookFile.seekp(0, ios::end);
    bookFile.write((char*)(&book), sizeof(book));


    int newSize = updateBookFileHeader(true);
    updateISBNIndex(book.ISBN, newSize, true);
    cout << "\nBook added successfully.\n\n";

    // Flush and close the file
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

void SLS::updateISBNIndex(char isbn[15], int rrn, bool flag) {
    map<char*, int> primaryI;

    primaryIFile.open("ISBNIndex.txt", ios::app | ios::in);
    primaryIFile.seekg (0,ios::end);
    long long size = primaryIFile.tellg();
    primaryIFile.seekg(0);

    int n = size / 18;
    if(flag)                    //addition
    {
        if(primaryIFile.eof())
        {
            primaryIFile << isbn << '|';
            primaryIFile << rrn << '\n';
            return;
        }
        primaryI.insert({isbn, rrn});

        for(int i = 0; i < n; i++) {
            primaryIFile.read(isbn,'|');
            primaryIFile >> rrn;
            primaryI.insert({isbn, rrn});
            primaryIFile.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        for(auto i: primaryI)
        {
            primaryIFile << i.first << '|';
            primaryIFile << i.second << '\n';
        }
    }
    primaryIFile.close();
}

int SLS::updateBookFileHeader(bool flag) {
    if(flag )                                // addition
    {
        ifstream bookfile("Books.txt");
        int size = 0;
        string firstIntegerStr;

        // Read the first string until the "|" delimiter
        if (getline(bookfile, firstIntegerStr, '|')) {
            // Convert the string to an integer
            int firstInteger = stoi(firstIntegerStr);

            // Print or process the first integer
            std::cout << "First Integer: " << firstInteger << std::endl;
            size = firstInteger;
        }
        size++;
        firstIntegerStr = to_string(size);
        bookFile.seekp(0);
        bookFile.write((char*)&firstIntegerStr,);
        return size;
    }

}

