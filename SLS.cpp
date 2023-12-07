//
// Created by Doaa Ali on ١٠/١١/٢٠٢٣.
//


#include "bits-stdc++.h"
#include <algorithm>
#include <vector>
#include "SLS.h"
using namespace std;
int recsize = 3;
int presize = 0;
int linkedresize = 0;
vector <int> authorIds;
map<int,long> indexing;
map<string , long> secondary;
void loadLinkedSize(){
    fstream file("list_author.txt",ios::app);
    file.close();
    file.open("list_author.txt" , ios::in);
    string rec;
    while (getline(file,rec))
    {
        linkedresize++;
    }
    if(linkedresize != 0)
        linkedresize=-1;
}
void loadPindex(){
    fstream file("author_pIndex.txt" , ios::in);
    string record;
    while (getline(file ,record))
    {
        istringstream is(record);
        string id;
        getline(is , id , ' ');
        authorIds.push_back(stoi(id));
    }
    sort(authorIds.begin() , authorIds.end());
    file.close();
    for (int i = 0; i < authorIds.size(); ++i) {
        cout << authorIds[i] << endl;
    }
}
void SLS::addToLinked(char id[15] , char name[30])
{
    linkedFile.open("list_author.txt" , ios::in | ios::out);
    linkedFile.seekp(0,ios::end);
    linkedFile.write((char *)id , sizeof(id));
    linkedFile << ' ';
    linkedFile.write((char*) -1 , 2);
    linkedFile << '\n';
    linkedFile.close();
    char buffer[15];
    std::snprintf(buffer, sizeof(buffer), "%d", linkedresize);
    linkedresize++;
    if(secondary.find(name) != secondary.end())
    {
        long rcc = secondary[name];
        linkedFile.open("lis_author.txt" , ios::in | ios::out);
        linkedFile.seekp(rcc*19 + 16);


    }
    else {
        addAuthSecondaryIndex(name, buffer);
    }
}

void loadSecondaryMap(){
    fstream secondaryFile("author_secondaryIndex.txt", ios::app);
    secondaryFile.close();
    secondaryFile.open("author_secondaryIndex.txt" , ios::in);

    if (secondaryFile.is_open()) {
        cout << "done";
    }

    string line;
    while (std::getline(secondaryFile, line)) {
        istringstream is(line);
        string name;
        long byteOffset;

        if (is >> name >> byteOffset) {
            secondary[name] = byteOffset;
        } else {
            std::cout << "Error parsing line: " << line << std::endl;
        }
    }
    secondaryFile.close();
    cout<<"Done\n";
}
int findAuthSecondary(char name[30])
{
    if(secondary.find(name) != secondary.end()){
        return secondary[name];
    }
    else
    {
        return -1;
    }
}
int binarySearch( vector<int>& iDs, int id) {
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
void store_Index()
{
    fstream pIndex = fstream("author_pIndex.txt" , ios::in);
    long lastrecS;
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
    sort(authorIds.begin(), authorIds.end());
    pIndex.close();
    cout<<"Done\n";
}
void retrieve_into_index()
{
    fstream pIndex = fstream("author_pIndex.txt" , ios::out);
    for (const auto& pair : indexing) {
        pIndex << pair.first << " " << pair.second << std::endl;
    }
    cout<<"Done\n";

}

void SLS::insertAuthPrimaryIndex(char recsize[15] , char id[15])
{
    std::sort(authorIds.begin(), authorIds.end());
    primaryIFile.open("author_pIndex.txt" , ios::out);
    for(int id : authorIds)
    {
        primaryIFile << id;
        primaryIFile << " ";
        primaryIFile << indexing[id];//byteoffset
        primaryIFile << "\n";
    }
    primaryIFile.close();
    char presizechar[15];
    std::snprintf(presizechar, strlen(presizechar), "%d", presize);
    addToLinked(author.ID , author.name);
    presize+=strlen(id)+1+ strlen(presizechar)+1;
}


void SLS::addAuthSecondaryIndex( char name[30], char byteoffset[15]) {
    secondaryFile.open("author_secondaryIndex.txt" , ios::out);
    secondary[name] = stoi(byteoffset);
    for(auto& val : secondary)
    {
        secondaryFile << val.first;
        secondaryFile << ' ';
        secondaryFile << val.second;
        secondaryFile << '\n';
    }
    secondaryFile.close();
}
// Constructors and destructors of Authors and Book structs and system class

// Default constructor of Author
Author::Author() {}

// Constructor of Author with given parameters
Author::Author(char id[15], char n[30], char add[30])
{
    //    used strcpy to copy the char arrays
    strcpy(this->ID, id);
    strcpy(this->name, n);
    strcpy(this->address, add);
}

// Default constructor of Book
Book::Book() {}

// Constructor of Book with given parameters
Book::Book(char isbn[15], char t[30], char aID[15])
{
    strcpy(this->ISBN, isbn);
    strcpy(this->title, t);
    strcpy(this->authorID, aID);
}

// Constructors and destructor of the system

// Default constructor of system class that initializes the AVAIL list
SLS::SLS()
{
    bookFile.open("Book.txt", ios::app);
    bookFile.seekg(0, ios::end);
    int tell = bookFile.tellg();
    if (tell == 0)
    {
        bookFile << "-1|---\n";
    }
    bookFile.close();
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

// destructor of the system
SLS::~SLS()
{
}

// End of the constructors and destructors

// ----------------------------------------------------------------------------------------------

// Load methods to load the indexes into data structures

// Load the primary index into map<string, int> ISBN, byteOffset and vector<string> ISBN
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
    string isbn; // Assuming each name is at most 15 characters long
    int rrn;

    bookIsbnMap.clear();
    bookISBN.clear();

    while (!pISBNFile.eof())
    {
        pISBNFile >> isbn;
        pISBNFile >> rrn;

        bookIsbnMap.insert({isbn, rrn});

        bookISBN.push_back(isbn);

        // Move the file pointer to the next line
        pISBNFile.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    pISBNFile.close();
}

// Load the secondary index into map<string, int> authorID, head of inverted list and vector<string> authorID
void SLS::loadAuthorSecIndex()
{
    sAuthorIDFile.open("secondaryAuthorID.txt", ios::in | ios::app);
    if (!sAuthorIDFile.is_open())
    {
        sAuthorIDFile.open("secondaryAuthorID.txt", ios::in | ios::app);
    }
    if (sAuthorIDFile.peek() == EOF)
    {
        sAuthorIDFile.close();
        return;
    }
    string id; // Assuming each name is at most 15 characters long
    int lineNum;

    secAuthorMap.clear();
    secAuthorIds.clear();

    while (!sAuthorIDFile.eof())
    {
        sAuthorIDFile >> id;
        sAuthorIDFile >> lineNum;
        secAuthorMap.insert({id, lineNum});
        if (lineNum == -1)
        {
            continue;
        }
        secAuthorIds.push_back(id);

        // Move the file pointer to the next line
        sAuthorIDFile.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    sAuthorIDFile.close();
}

// Load the secondary index inverted list into vector<pair<string, int>> ISBN, next pointer
void SLS::loadIsbnSecList()
{
    secIsbnList.clear();
    sAuthorIDListFile.open("secIsbnList.txt", ios::in | ios::app);
    while (!sAuthorIDListFile.fail())
    {
        // Read and extract key and integer value from the 5th line
        string line;
        getline(sAuthorIDListFile, line);

        istringstream iss(line);
        string isbn;
        string lineNum;

        // Read key and value from the line
        if (iss >> isbn >> lineNum)
        {
            try
            {
                int value = stoi(lineNum);
                secIsbnList.push_back({isbn, value});
            }
            catch (const invalid_argument &e)
            {
                cerr << "Error converting value to integer on line: " << line << endl;
            }
            catch (const out_of_range &e)
            {
                cerr << "Value out of range on line: " << line << endl;
            }
        }
    }

    sAuthorIDListFile.close();
}

// End of load methods

// ----------------------------------------------------------------------------------------------

// Update the indexes after adding or deleting records

// Update the AVAIL list of deleted records
void SLS::updateBookAVAIL(int beforeTarget, int target, bool flag)
{
    bookFile.close();
    bookFile.open("Book.txt", ios::out | ios::in);
    if (flag)
    {
        if (beforeTarget == 0)
        {
            bookFile.seekp(beforeTarget);
            bookFile << target << '|';
        }
        else
        {
            short temp;
            bookFile.seekg(beforeTarget + 1, ios::beg);
            bookFile >> temp;
            bookFile.seekp(beforeTarget + 2 + sizeof(temp));
            bookFile << target << '|';
        }
        bookFile.close();
        return;
    }
    string header;
    bookFile.seekg(0, ios::beg);
    getline(bookFile, header, '|');
    string rec;
    bookFile.seekg(target);
    getline(bookFile, rec, '\n');

    bookFile.seekp(target);
    bookFile << '*' << rec.size() << '|' << header << '|';

    bookFile.seekp(0, ios::beg);
    bookFile << target << '|';

    bookFile.close();
}

// Update the primary index
void SLS::updateISBNIndex(char *isbn, int recByteOffset, bool flag)
{
    pISBNFile.open("ISBNIndex.txt", ios::out);
    if (flag)
    {
        bookIsbnMap.insert({isbn, recByteOffset});
    }
    else
    {
        bookIsbnMap.erase(isbn);
    }
    for (auto i : bookIsbnMap)
    {
        pISBNFile << i.first << " " << i.second << "\n";
    }

    pISBNFile.close();
}

// Update the secondary index and inverted list
void SLS::updateSecondaryAuthorIDFile(char *authorID, char *isbn, bool flag)
{
    // map for all author ids in the file before insertion
    // add isbn to its list and link its byte offset to author id or to the previous isbn
    loadAuthorSecIndex();
    loadIsbnSecList();

    if (flag)
    {
        int lineNum = secIsbnList.size();

        if (binarySearch(secAuthorIds, authorID) == -1)
        {
            auto it = secAuthorMap.find(authorID);
            if (it != secAuthorMap.end())
            {
                secAuthorMap[authorID] = lineNum;
            }
            else
            {
                secAuthorMap.insert({authorID, lineNum});
            }
            secIsbnList.push_back({isbn, -1});
        }
        else
        {
            lineNum = secAuthorMap[authorID];
            // sAuthorIDListFile << isbn << ' ' << lineNum << '\n';
            secAuthorMap[authorID] = secIsbnList.size();
            secIsbnList.push_back({isbn, lineNum});
        }
    }
    else
    {
        int check = binarySearch(secAuthorIds, authorID);
        if (check == -1)
        {
            cout << "WARNING: unknown author id " << authorID << endl;
            return;
        }
        else
        {
            cout << "Start deleting from linked list" << endl;
            int isbnBindingIndex = secAuthorMap[authorID];
            string desiredIsbn = secIsbnList[isbnBindingIndex].first;
            int nextIsbnIndex = secIsbnList[isbnBindingIndex].second;
            // case 1
            //  value of author id in map = index && index refers to the required isbn
            //  then take the value from the isbn list item and put it in the secondaryAuthorFile and replace it with #
            if (desiredIsbn == isbn)
            {
                secAuthorMap[authorID] = nextIsbnIndex;
                secIsbnList[isbnBindingIndex].second = -2;
            }
                //  case 2
                //  loop on the linked list items
                //  keep the value of the previous index
                //  when isbn found replace the previous index's value to this value and replace this value with #
            else
            {
                int tmp = isbnBindingIndex;
                while (true)
                {
                    desiredIsbn = secIsbnList[nextIsbnIndex].first;
                    if (desiredIsbn == isbn)
                    {
                        secIsbnList[tmp].second = secIsbnList[nextIsbnIndex].second;
                        secIsbnList[nextIsbnIndex].second = -2;
                        break;
                    }
                    tmp = nextIsbnIndex;
                    nextIsbnIndex = secIsbnList[nextIsbnIndex].second;
                }
            }
        }
    }

    sAuthorIDFile.open("secondaryAuthorID.txt", ios::out);
    for (auto i : secAuthorMap)
    {
        sAuthorIDFile << i.first << " " << i.second << "\n";
    }
    sAuthorIDFile.close();

    sAuthorIDListFile.open("secIsbnList.txt", ios::out);
    for (auto i : secIsbnList)
    {
        sAuthorIDListFile << i.first << " " << i.second << "\n";
    }
    sAuthorIDListFile.close();
}

// End of update methods

// ----------------------------------------------------------------------------------------------

// Needed methods for the program

// Binary search method
// returns -1 if not found
// returns the index of the element if found
int SLS::binarySearch(const vector<string> &iDs, string id)
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

// get the next byteOffset from AVAIL list to add the next record
int SLS::setCurByteOffset()
{
    //    get new byte offset
    short AVAIL;
    string oldSizeRec, nextByteoffsetAVAIL;

    bookFile.seekg(0, ios::beg);
    int target;
    bookFile >> target;
    bookFile.seekg(0, ios::end);
    streampos byteOffset = bookFile.tellg();
    curByteOffset = byteOffset;
    if (target == -1)
    {
        return -1;
    }
    else
    {
        bookFile.seekg(target + 1, ios::beg);
        getline(bookFile, oldSizeRec, '|');
        getline(bookFile, nextByteoffsetAVAIL, '|');

        int previousByteOffset = 0;
        while (true)
        {
            if (curRecordSize <= stoi(oldSizeRec))
            {
                updateBookAVAIL(previousByteOffset, stoi(nextByteoffsetAVAIL), true);
                curByteOffset = target;
                return stoi(oldSizeRec);
            }
            else if (stoi(nextByteoffsetAVAIL) == -1)
            {
                return -1;
            }
            bookFile.seekg(stoi(nextByteoffsetAVAIL) + 1, ios::beg);
            previousByteOffset = target;
            target = stoi(nextByteoffsetAVAIL);
            getline(bookFile, oldSizeRec, '|');
            getline(bookFile, nextByteoffsetAVAIL, '|');
        }
    }
}

// Return Book after searching using ISBN
Book SLS::searchBook(string isbn)
{
    char tmp[15];
    isbn.copy(tmp, sizeof(tmp) - 1);

    int recByteOffset = bookIsbnMap[isbn];

    bookFile.open("Book.txt", ios::in);

    bookFile.seekg(recByteOffset, ios::beg);

    string line;
    getline(bookFile, line);

    stringstream ss(line);
    int length;
    char title[30];
    char aid[15];

    ss >> length;
    ss.ignore();
    ss.getline(tmp, 15, '|');
    ss.getline(title, 30, '|');
    ss.getline(aid, 15);

    bookFile.close();
    return Book(tmp, title, aid);
}

// Add a book in the data file and call update methods
void SLS::addBook(Book b)
{
    if(binarySearch(authorIds,stoi(book.authorID)) == -1)
    {
        cout << "Not valid Author ID!\n";
        return;
    }
    curRecordSize = strlen(b.ISBN) + strlen(b.title) + strlen(b.authorID) + 3;

    bookFile.open("Book.txt", ios::app | ios::in);

    bookFile.seekg(0, ios::end);
    int byteOffset = bookFile.tellg();
    int oldRecordSize = setCurByteOffset();

    if (curByteOffset != byteOffset)
    {
        bookFile.close();
        bookFile.open("Book.txt", ios::out | ios::in);

        // Concatenate the input into the string stream
        string input = "";

        input = to_string(curRecordSize) + '|' + b.ISBN + '|' + b.title + '|' + b.authorID;

        bookFile.seekp(curByteOffset);
        if (oldRecordSize != curRecordSize)
        {
            input += '|';
        }
        bookFile << input;
    }
    else
    {
        bookFile << std::setw(2) << std::setfill('0') << curRecordSize;
        bookFile << '|';
        bookFile.write((char *)b.ISBN, strlen(b.ISBN));
        bookFile << '|';
        bookFile.write((char *)b.title, strlen(b.title));
        bookFile << '|';
        bookFile.write((char *)b.authorID, strlen(b.authorID));
        bookFile << "\n";
    }

    updateISBNIndex(b.ISBN, curByteOffset, true);
    updateSecondaryAuthorIDFile(b.authorID, b.ISBN, true);
    bookFile.flush();
    bookFile.close();
}

// Delete a book from the data file and update methods
void SLS::deleteBook(string isbn)
{
    loadBookIndex();
    if (binarySearch(bookISBN, isbn) == -1)
    {
        cout << "Invalid Book ISBN\n";
        return;
    }
    int byteOffset = bookIsbnMap[isbn];

    book = searchBook(isbn);

    updateBookAVAIL(0, byteOffset, false);
    updateISBNIndex(book.ISBN, 0, false);
    updateSecondaryAuthorIDFile(book.authorID, book.ISBN, false);
}

// this method delete all books related to a deleted author
// to be called in author deletion
void SLS::deleteAllAuthorBooks(string authorId)
{
    vector<string> books;
    loadAuthorSecIndex();
    loadIsbnSecList();
    authorId = string(14 - authorId.length(), '0') + authorId;
    int lineNum = secAuthorMap[authorId];

    while (lineNum > -1)
    {
        int temp = lineNum;
        string isbn = secIsbnList[lineNum].first;
        deleteBook(isbn);
        lineNum = secAuthorMap[authorId];
    }
    sAuthorIDFile.close();
    sAuthorIDFile.open("secondaryAuthorID.txt", ios::out);
    for (auto i : secAuthorMap)
    {
        sAuthorIDFile << i.first << " " << i.second << "\n";
    }
    sAuthorIDFile.close();

    sAuthorIDListFile.open("secIsbnList.txt", ios::out);
    for (auto i : secIsbnList)
    {
        sAuthorIDListFile << i.first << " " << i.second << "\n";
    }
    sAuthorIDListFile.close();
}

// End of needed methods

// ----------------------------------------------------------------------------------------------

void SLS::insertAuthorIndex(int recsize, char *id)
{
    fstream pIndex = fstream("AuthorIDIndex.txt", ios::app);
    pIndex.write((char *)id, strlen(id));
    pIndex << " ";
    pIndex << recsize;
    pIndex << "\n";
}

// ----------------------------------------------------------------------------------------------

// Public main methods to be called in the main program

// Add an author
void SLS::addAuthor()
{
    if( binarySearch(authorIds , stoi(author.ID)) != -1)
    {
        return;
    }
    authorIds.push_back(stoi(author.ID));
    for (int i = 0; i < authorIds.size(); ++i) {
        cout << authorIds[i] << endl;
    }
    authorFile.open("author.txt" , ios::in);
    if(authorFile.is_open())
    {
        cout << "yes";
    }
    string avl;
    getline(authorFile ,avl );
    authorFile.close();
    if(avl != "-1")
    {
        authorFile.open("author.txt" , ios::in | ios::out);
        authorFile.seekg(stoi(avl));
        string record;
        getline(authorFile , record);
        istringstream is(record);
        string num;
        string byteoffset;
        getline(is , num , '|');
        getline(is , byteoffset , '|');
        int check = (strlen((author.ID)) + strlen((author.name)) + strlen((author.address)) + 3);
        if(stoi(byteoffset) >= check)
        {
            authorFile.seekp(stoi(avl));
            authorFile.write((char*)(author.ID) , strlen(author.ID));
            authorFile << '|';
            authorFile.write((char*) (author.name) , strlen(author.name));
            authorFile << '|';
            authorFile.write((char*) (author.address) , strlen(author.address));
            authorFile << "\n";
            char buffer[15];
            std::snprintf(buffer, sizeof(buffer), "%s", (avl.c_str()));
            indexing[stoi(author.ID)] = stoi(avl);
            insertAuthPrimaryIndex(buffer , author.ID);
            authorFile.seekp(0,ios::beg);
            num = num.substr(1,num.size());
            authorFile << num;
            authorFile << '\n';
            authorFile.close();
            return;
        }
    }
    authorFile.open("author.txt" , ios::app);
    authorFile.write((char*)(author.ID) , strlen(author.ID));
    authorFile << '|';
    authorFile.write((char*) (author.name) , strlen(author.name));
    authorFile << '|';
    authorFile.write((char*) (author.address) , strlen(author.address));
    authorFile << "\n";
    char buffer[15];
    std::snprintf(buffer, sizeof(buffer), "%d", recsize);
    indexing[stoi(author.ID)] = recsize;
    insertAuthPrimaryIndex(buffer , author.ID);
    recsize+=(strlen((author.ID)) + strlen((author.name)) + strlen((author.address)) + 3);
    authorFile.close();
}

// Add a book
void SLS::addBook()
{
    cout << "Enter book ISBN: ";
    char temp[15];
    cin.ignore();
    cin >> temp;
    string isbn(temp);
    isbn = string(14 - isbn.length(), '0') + isbn;

    loadBookIndex();

    int check = binarySearch(bookISBN, isbn);
    if (check != -1)
    {
        cout << "A book with ISBN " << isbn << " exist.\n";
        return;
    }

    cout << "Enter book title: ";
    char t[30];
    cin.ignore();
    cin >> t;

    cout << "Enter book author ID: ";
    cin.ignore();
    cin >> temp;
    string aid(temp);
    aid = string(14 - aid.length(), '0') + aid;

    char tmp[15];
    char aTmp[15];
    isbn.copy(tmp, sizeof(tmp) - 1);
    aid.copy(aTmp, sizeof(aTmp) - 1);
    aTmp[14] = '\000';

    book = Book(tmp, t, aTmp);

    addBook(book);
}

// Update the author name using author ID
void SLS::updateAuthorName()
{
}

// Update the book title using book ISBN
void SLS::updateBookTitle()
{
    cout << "Enter book ISBN: ";
    char temp[15];
    cin.ignore();
    cin >> temp;
    string isbn = temp;
    isbn = string(14 - isbn.length(), '0') + isbn;

    loadBookIndex();
    if (binarySearch(bookISBN, isbn) == -1)
    {
        cout << "Invalid Book ISBN\n";
        return;
    }

    int byteOffset = bookIsbnMap[isbn];

    book = searchBook(isbn);

    cout << "Enter the new title: ";
    char newTitle[30];
    cin.ignore();
    cin >> newTitle;
    cout << strlen(newTitle) << endl;

    if (strlen(newTitle) == strlen(book.title))
    {
        strcpy(book.title, newTitle);
        bookFile.open("Book.txt", ios::out | ios::in);
        bookFile.seekp(byteOffset + 18, ios::beg);
        bookFile << newTitle;
        bookFile.close();
    }
    else if (strlen(newTitle) > strlen(book.title))
    {
        // cout << book.title << endl;
        // cout << book.title << endl;

        deleteBook(isbn);
        strcpy(book.title, newTitle);
        addBook(book);
    }
}

// Delete author using author ID
void SLS::deleteAuthor(int Id)
{
    //store index into Map
    store_Index();
    auto check = binarySearch(authorIds,Id);
    if (check != -1)
    {
        auto end = std::remove(authorIds.begin() , authorIds.end() , Id);
        authorIds.erase(end, authorIds.end());
        char List[10];
        ////get Avail List
        authorFile.open("author.txt" , ios::in);
        int ByteOffset=indexing[Id];
        ///get size of record
        string record;
        authorFile.seekg(ByteOffset,ios::beg);
        getline(authorFile,record,'\r');
        string size=to_string(record.length());
        authorFile.seekg(ios::beg);
        authorFile.getline(List,sizeof (List));
        authorFile.close();

        ////get byte offset of deleted record
        string Byte=to_string(ByteOffset);
        authorFile.open("author.txt", std::ios::in | std::ios::out);
        authorFile.seekp(ios::beg);
        authorFile.write(Byte.c_str(),2);
        authorFile.seekp(ByteOffset,ios::beg);
        ///insert size and pre deleted
        authorFile.write("*",1);
        authorFile.write(List,2);
        authorFile.write("|",1);
        authorFile<<size;
        authorFile.write("|",1);
        authorFile.close();
        auto it = indexing.find(Id);
        indexing.erase(it);
        retrieve_into_index();
        cout<<"Done\n";
        deleteAllAuthorBooks(to_string(Id));
    }
    else
        cout<<"This author doesn't exist\n";
}
void SLS::searchAuthor(int Id)
{
    int check= binarySearch(authorIds,Id);
    store_Index();
//    auto check = indexing.find(Id);
    if (check != -1) {
        authorFile.open("file.txt", ios::in);
        long ByteOffset=indexing[Id];
        authorFile.seekg(ByteOffset,ios::beg);
        //don't want print without it
        authorFile.get();
        string line;
        getline(authorFile, line);
        cout<<"the Author Founded.. \n";
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

// Delete book using book ISBN
void SLS::deleteBook()
{

    cout << "Enter book ISBN: ";
    char temp[15];
    cin.ignore();
    cin >> temp;
    string isbn = temp;
    isbn = string(14 - isbn.length(), '0') + isbn;

    deleteBook(isbn);
}


// Print book information using book ISBN
void SLS::printBook()
{
    cout << "Enter book ISBN: ";
    char temp[15];
    cin.ignore();
    cin >> temp;
    string isbn(temp);
    isbn = string(14 - isbn.length(), '0') + isbn;

    loadBookIndex();

    if (binarySearch(bookISBN, isbn) == -1)
    {
        cout << "There's no book with this ISBN: " << temp << "\n";
    }
    else
    {
        book = searchBook(isbn);
        cout << "ISBN: " << book.ISBN << "\nTitle: " << book.title << "\nAuthor's ID: " << book.authorID << endl;
    }
}

// Write a query to fetch the needed information
// from the files using indexes
void SLS::query()
{
}


