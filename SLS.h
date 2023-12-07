//
// Created by Doaa Ali on ١٠/١١/٢٠٢٣.
//

// Main system's structure, may change according to requirements

#ifndef SLS_H
#define SLS_H
using namespace std;
void loadPindex();
int findAuthSecondary(char name[30]);
void loadLinkedSize();
void loadSecondaryMap();
void store_Index();
void retrieve_into_index();
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
public:
    Author author;
    Book book;
    void insertAuthPrimaryIndex(char recsize[15] , char id[15]);

    // author and book files that contain the records
    fstream authorFile;
    fstream bookFile;
    fstream primaryIFile;
    fstream secondaryFile;
    fstream linkedFile;
    //
    // add your own index files as you need
    //
    void addToLinked(char id[15] , char name[30]);
    // main file's functions
    void updateISBNIndex(char* isbn, int rrn, bool flag);
    int updateBookFileHeader(bool flag);
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
    void addAuthSecondaryIndex(char name[30] , char byteoffset[15]);
    void addAuthor();
    void addBook();
    void updateAuthorName();
    void updateBookTitle();
    void deleteAuthor(int Id);
    void deleteBook();
    void searchAuthor(int id);
    void printBook();
    void query();
};

#endif // SLS_H
