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

// Declare Author struct
struct Author
{
    char ID[15];
    char name[30];
    char address[30];
    Author();
    Author(char id[15], char n[30], char add[30]);
};

// Declare Book struct
struct Book
{
    char ISBN[15];
    char title[30];
    char authorID[15];
    Book();
    Book(char isbn[15], char t[30], char aID[15]);
};

// Declare Simple Library System class SLS
class SLS
{
public:
    Author author;
    Book book;
    void insertAuthPrimaryIndex(char recsize[15] , char id[15]);

    // author data file
    fstream authorFile;
    // book data file
    fstream bookFile;

    // book primary index file
    fstream pISBNFile;
    fstream primaryIFile;
    // book secondary index file
    fstream sAuthorIDFile;
    // book secondary index file inverted list
    fstream sAuthorIDListFile;

    int curRecordSize = 0;
    short curByteOffset = 0;

    // Vectors for primary and secondary attributes
//    vector<int> authorIds;
    vector<int> AuthorByteOffset;
    vector<string> bookISBN;
    vector<string> secAuthorIds;
    vector<pair<string, int>> secIsbnList;

    // Map for primary index
    map<string, int> bookIsbnMap;
    // Map for secondary index
    map<string, int> secAuthorMap;
    fstream secondaryFile;
    fstream linkedFile;
    //
    // add your own index files as you need
    //
    void addToLinked(char id[15] , char name[30]);
    // main file's functions

    // Load methods
    void loadBookIndex();
    void loadAuthorSecIndex();
    void loadIsbnSecList();

    // Update methods
    void updateBookAVAIL(int beforeTarget, int target, bool flag);
    void updateISBNIndex(char *isbn, int recSize, bool flag);
    void updateSecondaryAuthorIDFile(char *authorID, char *isbn, bool flag);

    // Needed methods
    int binarySearch(const vector<string> &iDs, string id);
    int binarySearch(const vector<int> &iDs, int id);
    int setCurByteOffset();
    Book searchBook(string isbn);
    void addBook(Book b);
    void deleteBook(string isbn);
    void deleteAllAuthorBooks(string authorId);

//    void insertAuthorIndex(int recsize, char *id);

public:
    //
    // add your own index functions and any other functions as you need

    // constructors and destructors

    SLS();
    SLS(Author a);
    SLS(Book b);
    SLS(Author a, Book b);
    ~SLS();

    // main system's methods that the user will use
    void addAuthSecondaryIndex(char name[30] , char byteoffset[15]);
    void addAuthor();
    void addBook();
    void updateAuthorName(char* id, char* name);
    void updateBookTitle();
    void deleteAuthor(int Id);
    void deleteBook();
    void searchAuthor(int id);
    void printBook();
    void query();
};

#endif // SLS_H
