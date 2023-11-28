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
    bookIsbnMap.insert({isbn, recByteOffset});
    pISBNFile.open("ISBNIndex.txt", ios::out);

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
    char isbn[15]; // Assuming each name is at most 15 characters long
    int rrn;

    while (!pISBNFile.eof())
    {
        pISBNFile >> isbn;
        pISBNFile >> rrn;
        // cout << isbn << " " << rrn << endl;
        bookIsbnMap.insert({isbn, rrn});

        bookISBN.push_back(isbn);

        // Move the file pointer to the next line
        pISBNFile.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    pISBNFile.close();
}

void SLS::updateBookAVAIL(int beforeTarget, int target, bool flag)
{
    if (flag)
    {
    }
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
    bookFile.open("Book.txt", ios:: app);
    bookFile.seekg(0, ios::end);
    int tell = bookFile.tellg();
    if(tell == 0)
        bookFile << "-1\n";
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
    short oldSizeRec, nextByteoffsetAVAIL;

    bookFile.seekg(0, ios::beg);
    short target;
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
        bookFile.seekg(target, ios::beg);
        bookFile.ignore('*');
        bookFile >> oldSizeRec;
        bookFile.ignore('|');
        bookFile >> nextByteoffsetAVAIL;

        int previouseByteOffset = 0;
        while (true)
        {

            if (curRecordSize <= oldSizeRec)
            {
                bookFile.seekp(target, ios::beg);
                updateBookAVAIL(previouseByteOffset, nextByteoffsetAVAIL, true);
                return target;
            }
            else if (nextByteoffsetAVAIL == -1)
            {
                updateBookAVAIL(previouseByteOffset, nextByteoffsetAVAIL, true);
                return curByteOffset;
            }
            bookFile.seekg(nextByteoffsetAVAIL, ios::beg);
            previouseByteOffset = target;
            target = nextByteoffsetAVAIL;
            bookFile.ignore('*');
            bookFile >> oldSizeRec;
            bookFile.ignore('|');
            bookFile >> nextByteoffsetAVAIL;
        }
    }

}

void SLS::addBook()
{
    cout << "Enter book ISBN: ";
    char isbn[15];
    cin.ignore();
    cin >> isbn;

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
    char aid[15];
    cin.ignore();
    cin >> aid;

    this->book = Book(isbn, t, aid);

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

        bookFile.seekp(curByteOffset, std::ios::beg);
        for (char i : concatenatedString)
        {
            bookFile.put(i);
        }
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
    cout << "Enter book ISBN: ";
    char isbn[15];
    cin.ignore();
    cin >> isbn;

    loadBookIndex();

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
    ss.getline(isbn, 15, '|');
    ss.getline(title, 30, '|');
    ss.getline(aid, 15);
    cout << "Length: " << length << endl;

    cout << "ISBN: " << isbn << ", title: " << title << ", aID: " << aid << endl;

    bookFile.close();
}

void SLS::query()
{
}
