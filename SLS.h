//
// Created by Doaa Ali on ١٠/١١/٢٠٢٣.
//

// Main system's structure, may change according to requirements

#ifndef SLS_H
#define SLS_H

using namespace std;
int recsize = 0;
void insertAuthorIndex(int recsize , char*id);
int binarySearch(const vector<int>& iDs, int id);
vector<int> authorIds;
vector<int> AuthorByteOffset;
struct Author
{
    char ID[15];
    char name[30];
    char address[30];
    Author();
    Author(char id[15], char n[30], char add[30]);
};

struct Book
{
    char ISBN[15];
    char title[30];
    char authorID[15];
    Book();
    Book(char isbn[15], char t[30], char aID[15]);
};

// Simple Library System
class SLS
{
private:
    Author author;
    Book book;

    // author and book files that contain the records
    fstream authorFile;
    fstream bookFile;
    fstream pISBNFile;
    int curRecord;

    //
    // add your own index files as you need
    //

    // main file's functions
    void updateISBNIndex(char* isbn, int recSize, bool flag);
//    void readFromFile(fstream& file);
//    static void writeToFile(fstream& file,const char ojc[]);

    //
    // add your own index functions and any other functions as you need
    //

public:
    // constructors and destructors
    SLS();
    SLS(Author a);
    SLS(Book b);
    SLS(Author a, Book b);
    ~SLS();

    // main system's function that the user will use
    void addAuthor();
    void addBook();
    void updateAuthorName();
    void updateBookTitle();
    void deleteAuthor();
    void deleteBook();
    void printAuthor();
    void printBook();
    void query();
};

#endif // SLS_H
