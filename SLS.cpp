//
// Created by Doaa Ali on ١٠/١١/٢٠٢٣.
//

// declarations of the structs' and SLS class's functions

#include <bits/stdc++.h>
#include "SLS.h"

using namespace std;

void SLS::insertAuthorIndex(int recsize, char *id)
{
    fstream pIndex = fstream("AuthorIDIndex.txt", ios::app);
    pIndex.write((char *)id, strlen(id));
    pIndex << " ";
    pIndex << recsize;
    pIndex << "\n";
}

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

void SLS::updateBookAVAIL(int beforeTarget, int target, bool flag)
{
    bookFile.open("Book.txt", ios::in | ios::out);
    if (flag)
    {
        short temp;
        if (beforeTarget == 0)
        {
            bookFile.seekp(beforeTarget);
            bookFile << target << '|';
        }
        else
        {
            bookFile.seekg(beforeTarget + 1, ios::beg);
            bookFile >> temp;
            bookFile.seekp(beforeTarget + 1 + sizeof(temp));
            bookFile << target;
        }
        bookFile.close();
        return;
    }
    string header;
    bookFile.seekg(0, ios::beg);
    getline(bookFile, header, '|');
    string recSize;
    bookFile.seekg(target);
    getline(bookFile, recSize, '|');

    bookFile.seekp(target);
    bookFile << '*' << recSize << '|' << header << '|';

    bookFile.seekp(0, ios::beg);
    bookFile << target << '|';

    bookFile.close();
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

SLS::~SLS()
{
}

void SLS::addAuthor()
{

    // int check = binarySearch(authorIds, stoi(author.ID));
    // if (check != -1)
    // {
    //     return;
    // }

    authorFile.open("file.txt", ios::app);
    authorFile.write((char *)author.ID, strlen(author.ID));
    authorFile << '|';
    authorFile.write((char *)author.name, strlen(author.name));
    authorFile << '|';
    authorFile.write((char *)author.address, strlen(author.address));
    authorFile << "\n";
    insertAuthorIndex(curByteOffset, author.ID);
    curByteOffset += strlen(author.ID) + strlen(author.name) + strlen(author.address) + 3;
    authorFile.close();
}

int SLS::getNewByteOffset()
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
        return curByteOffset;
    }
    else
    {
        bookFile.seekg(target + 1, ios::beg);
        getline(bookFile, oldSizeRec, '|');
        getline(bookFile, nextByteoffsetAVAIL, '|');

        int previouseByteOffset = 0;
        while (true)
        {
            if (curRecordSize <= stoi(oldSizeRec))
            {
                bookFile.seekp(target, ios::beg);
                updateBookAVAIL(previouseByteOffset, stoi(nextByteoffsetAVAIL), true);
                return target;
            }
            else if (stoi(nextByteoffsetAVAIL) == -1)
            {
                return curByteOffset;
            }
            bookFile.seekg(stoi(nextByteoffsetAVAIL) + 1, ios::beg);
            previouseByteOffset = target;
            target = stoi(nextByteoffsetAVAIL);
            getline(bookFile, oldSizeRec, '|');
            getline(bookFile, nextByteoffsetAVAIL, '|');
        }
    }
}

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
    char t[15];
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

    this->book = Book(tmp, t, aTmp);

    curRecordSize = strlen(book.ISBN) + strlen(book.title) + strlen(book.authorID) + 3;

    bookFile.open("Book.txt", ios::app | ios::in);

    bookFile.seekg(0, ios::end);
    streampos byteOffset = bookFile.tellg();
    curByteOffset = getNewByteOffset();

    if (curByteOffset != byteOffset)
    {
        ostringstream concatenatedInput;

        // Concatenate the input into the string stream
        concatenatedInput << std::setw(2) << std::setfill('0') << strlen(book.ISBN);
        concatenatedInput << '|';
        concatenatedInput.write(book.ISBN, strlen(book.ISBN));
        concatenatedInput << '|';
        concatenatedInput.write(book.title, strlen(book.title));
        concatenatedInput << '|';
        concatenatedInput.write(book.authorID, strlen(book.authorID));
        concatenatedInput << "\n";

        // Get the concatenated input as a string
        string concatenatedString = concatenatedInput.str();

        bookFile.seekp(curByteOffset, ios::beg);
        bookFile << concatenatedString;
    }
    else
    {
        bookFile << std::setw(2) << std::setfill('0') << curRecordSize;
        bookFile << '|';
        bookFile.write((char *)book.ISBN, strlen(book.ISBN));
        bookFile << '|';
        bookFile.write((char *)book.title, strlen(book.title));
        bookFile << '|';
        bookFile.write((char *)book.authorID, strlen(book.authorID));

        bookFile << "\n";
    }

    // insertSortedPrimaryIndex(book.ISBN, curByteOffset);
    updateISBNIndex(book.ISBN, curByteOffset, true);
    updateSecondaryAuthorIDFile(book.authorID, book.ISBN, true);
    bookFile.flush();
    bookFile.close();
}

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
            if (it != secAuthorMap.end()) {
                secAuthorMap[authorID] = lineNum;
            } else {
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
    cout << "Enter book ISBN: ";
    char temp[15];
    cin.ignore();
    cin >> temp;
    string isbn(temp);
    isbn = string(14 - isbn.length(), '0') + isbn;

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

void SLS::printAuthor()
{
}

void SLS::printBook()
{
    cout << "Enter book ISBN: ";
    char temp[15];
    cin.ignore();
    cin >> temp;
    string isbn(temp);
    isbn = string(14 - isbn.length(), '0') + isbn;

    loadBookIndex();

    if(binarySearch(bookISBN, isbn) == -1)
    {
        cout<< "There's no book with this ISBN: "<< temp<<"\n";
    }
    else
    {
        book = searchBook(isbn);
        cout << "ISBN: " << book.ISBN << "\nTitle: " << book.title << "\nAuthor's ID: " << book.authorID << endl;
    }

}


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

void SLS::query()
{
}
