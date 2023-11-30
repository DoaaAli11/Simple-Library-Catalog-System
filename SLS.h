#include <vector>
#include <map>

using namespace std;
extern vector<int> authorIds;
extern map<int,long> indexing;
//int recsize=0;
void insertAuthorIndex(int recsize , char*id);
int binarySearch(const vector<int>& iDs, int id);
struct Author
{
    char ID[15];
    char name[30];
    char address[30];
    Author();
    Author(string id, string n, string add);
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
    fstream primaryIFile;

    //
    // add your own index files as you need
    //

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
    void addAuthor(Author A);
    void addBook();
    void updateAuthorName();
    void updateBookTitle();
    void deleteAuthor(int Id);
    void deleteBook();
    void Search_By_Primary(int ID);
    void printBook();
    void query();
};

#endif //LASTTEST_SLS_H
