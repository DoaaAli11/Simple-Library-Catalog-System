
// Created by Esraa Mahmoud on 29/11/2023.
//

// declarations of the structs' and SLS class's functions

//#include "bits-stdc++.h"
#include "SLS.h"
#include <cstring>
#include <iostream>
#include <map>
#include <limits>
#include <sstream>
vector<int> authorIds;
map<int,long> indexing;

using namespace std;

void insertAuthorIndex(int recsize , char*id)
{
    fstream pIndex = fstream("pIndex.txt" , ios::app);
    pIndex.write((char*)id , strlen(id));
    pIndex << " ";
    pIndex << recsize;
    pIndex << "\n";
}
int binarySearch(const vector<int>& iDs, int id) {
    int left = 0;
    int right = iDs.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (iDs[mid] == id) {
            return mid;
        }

        if (iDs[mid] < id) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return -1;
}
Author::Author() {}


Author::Author(string id, string n, string add)
{
//    used strcpy to copy the char arrays
    strcpy(this->ID , id.c_str());
    strcpy(this->name , n.c_str());
    strcpy(this->address , add.c_str());

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
void store_Index_In_Map()
{
    fstream pIndex = fstream("pIndex.txt" , ios::in);
    string line;
    while (std::getline(pIndex, line)) {
        istringstream is(line);
        int id;
        long byteOffset;

        if (is >> id >> byteOffset) {
            indexing[id] = byteOffset;
        } else {
            std::cout << "Error parsing line: " << line << std::endl;
        }
    }
    pIndex.close();
    cout<<"Done\n";
}
void retrieve_into_index()
{
    fstream pIndex = fstream("pIndex.txt" , ios::out);
    for (const auto& pair : indexing) {
        pIndex << pair.first << " " << pair.second << std::endl;
    }
    cout<<"Done\n";

}
void SLS::deleteAuthor(Author A)
{
    //store index into Map
    store_Index_In_Map();
    auto check = indexing.find(stoi(A.ID));
    if (check != indexing.end())
    {
        char List[10];
        ///get size of record
        int size=strlen(A.ID) + strlen(A.name) + strlen(A.address);
        ////get Avail List
        authorFile.open("file.txt" , ios::in);
        authorFile.getline(List,sizeof (List));
        authorFile.close();

        ////get byte offset of deleted record
        long ByteOffset=indexing[stoi(A.ID)];
        authorFile.open("file.txt", std::ios::in | std::ios::out);
        authorFile.seekp(ios::beg);
        authorFile<<ByteOffset;
        authorFile.seekp(ByteOffset,ios::beg);
        ///insert size and pre deleted
        authorFile<<"*"<<List<<"|"<<size;
        authorFile.close();
        auto it = indexing.find(stoi(A.ID));
        indexing.erase(it);
        retrieve_into_index();
        cout<<"Done\n";

    }
    else
        cout<<"This author doesn't exist\n";
}
void SLS::Search_By_Primary(int Id)
{
    store_Index_In_Map();
    auto check = indexing.find(Id);
    if (check != indexing.end()) {
        authorFile.open("file.txt", ios::in);
        long ByteOffset=indexing[Id];
        authorFile.seekg(ByteOffset,ios::beg);
        //don't want print without it
        authorFile.get();
        string line;
        getline(authorFile, line);
        cout<<"the Author Founded.. \n";
//        cout<<line<<endl;
        istringstream ss(line);
        string token;
        vector<std::string> tokens;
        while (std::getline(ss, token, '|')) {
            tokens.push_back(token);
        }
        cout<<"Author's ID : "<<tokens[0]<<endl;
        cout<<"Author's name : "<<tokens[1]<<endl;
        cout<<"Author's Address : "<<tokens[2]<<endl;
    }
    else
    {
        cout<<"Sorry this author not exist\n";
    }
}
//void SLS::addAuthor(Author auhor)
//{
//    cout << auhor.ID << " |" << auhor.name;
//    string id = string(auhor.ID);
//    int check = binarySearch(authorIds , stoi(id));
//    if( check != -1)
//    {
//        return;
//    }
//    authorFile.open("file.txt" , ios::app);
//    authorFile.write((char*)author.ID , strlen(author.ID));
//    authorFile << '|';
//    authorFile.write((char *) author.name , strlen(author.name));
//    authorFile << '|';
//    authorFile.write((char *) author.address , strlen(author.address));
//    authorFile << "\n";
//    insertAuthorIndex(recsize , author.ID);
//    recsize+=strlen(author.ID) + strlen(author.name) + strlen(author.address) + 3;
//    authorFile.close();
//}
//void SLS::addBook()
//{
//    bookFile.open("Books.txt", ios::out | ios:: binary | ios::app | ios::in);
//    // Check if the file is open
//    if (!bookFile.is_open()) {
//        cout << "Error opening file\n";
//        return;
//    }
//
////    if (bookFile.peek() == EOF)
////    {
////        char* size = "0";
////        char* AVAIL = "-1";
////        bookFile.write(size,sizeof (size));
////        bookFile << "|";
////        bookFile.write(AVAIL,sizeof (AVAIL));
////        bookFile << "\n";
////
////    }
//
//    char isbn[15], t[30], aid[15];
//    cin.ignore();
//    cout << "Enter book's ISBN:";
//    cin >> isbn;
//    cout << "Enter book's title:";
//    cin >> t;
//    cout << "Enter book's author's ID:";
//    cin >> aid;
//
//    this->book = Book(isbn, t, aid);
//
//    // Write data as binary structure
//    bookFile.seekp(0, ios::end);
//    bookFile.write((char*)(&book), sizeof(book));
//
//
//    int newSize = updateBookFileHeader(true);
//    updateISBNIndex(book.ISBN, newSize, true);
//    cout << "\nBook added successfully.\n\n";
//
//    // Flush and close the file
//    bookFile.flush();
//    bookFile.close();
//}
//
//void SLS::updateAuthorName()
//{
//}
//
//void SLS::updateBookTitle()
//{
//}
//
//void SLS::deleteBook()
//{
//}
//
//
//void SLS::printBook()
//{
//    bookFile.open("Books.txt", ios::in);
//    vector<Book> books;
//
//    bookFile.seekg (0,ios::end);
//    long long size = bookFile.tellg();
//    bookFile.seekg(0);
//
//    int n = size / 60;
////    cout<<n<<endl;
//
//    for(int i=0;i<n;i++) {
//        bookFile.read((char *) &book, sizeof(book));
//        books.push_back(book);
//    }
//
//    for(Book b:books){
//        cout<<"ISBN: "<<b.ISBN<<endl;
//        cout<<"Book title: "<<b.title<<endl;
//        cout<<"book author ID: "<<b.authorID<<endl;
//        cout<<"------------------"<<endl;
//    }
//}
//
//void SLS::query()
//{
//}
//
//void SLS::updateISBNIndex(char isbn[15], int rrn, bool flag) {
//    map<char*, int> primaryI;
//
//    primaryIFile.open("ISBNIndex.txt", ios::app | ios::in);
//    primaryIFile.seekg (0,ios::end);
//    long long size = primaryIFile.tellg();
//    primaryIFile.seekg(0);
//
//    int n = size / 18;
//    if(flag)                    //addition
//    {
//        if(primaryIFile.eof())
//        {
//            primaryIFile << isbn << '|';
//            primaryIFile << rrn << '\n';
//            return;
//        }
//        primaryI.insert({isbn, rrn});
//
//        for(int i = 0; i < n; i++) {
//            primaryIFile.read(isbn,'|');
//            primaryIFile >> rrn;
//            primaryI.insert({isbn, rrn});
//            primaryIFile.ignore(numeric_limits<streamsize>::max(), '\n');
//        }
//        for(auto i: primaryI)
//        {
//            primaryIFile << i.first << '|';
//            primaryIFile << i.second << '\n';
//        }
//    }
//    primaryIFile.close();
//}
//
//int SLS::updateBookFileHeader(bool flag) {
//    if(flag )                                // addition
//    {
//        ifstream bookfile("Books.txt");
//        int size = 0;
//        string firstIntegerStr;
//
//        // Read the first string until the "|" delimiter
//        if (getline(bookfile, firstIntegerStr, '|')) {
//            // Convert the string to an integer
//            int firstInteger = stoi(firstIntegerStr);
//
//            // Print or process the first integer
//            std::cout << "First Integer: " << firstInteger << std::endl;
//            size = firstInteger;
//        }
//        size++;
//        firstIntegerStr = to_string(size);
//        bookFile.seekp(0);
////        bookFile.write((char*)&firstIntegerStr,);
//        return size;
//    }
//
//}
