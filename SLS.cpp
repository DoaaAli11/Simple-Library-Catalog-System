//
// Created by Doaa Ali on ١٠/١١/٢٠٢٣.
//

// declarations of the structs' and SLS class's functions
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

void SLS::deleteBook()
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
        bookFile.write((char*)&firstIntegerStr,sizeof(firstIntegerStr));
        return size;
    }

}

