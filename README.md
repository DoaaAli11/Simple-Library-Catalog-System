# Simple-Library-Catalog-System
## This is a simple library catalog system designed using *C++* programming language and *text files* database

In this system the data is stored in text files using **delimited fields and length indicator record** format.


### And the system uses **primary index** and **secondry index** to make any operation as follows:
- Primary index using the Author ID (for Authors data file). 
- Primary index using the ISBN (for Books data file). 
- Secondary index using the Author ID (for the Books data file). 
- Secondary index using the Author Name (for the Authors data file).

### The structure of the files:
| Authors Data file | Books Data file |
|----------|----------|
| Char Author ID [15] //primary key | Char ISBN [15] //primary key |
| Char Author Name [30] | Char Book Title [30] |
| Char Address [30] | Char Author ID [15] // secondary key |

### And this is the main welcome screen:
- Add New Author
- Add New Book 
- Update Author Name (Author ID) 
- Update Book Title (ISBN) 
- Delete Book (ISBN) 
- Delete Author (Author ID) 
- Print Author (Author ID) 
- Print Book (ISBN) 
- Write Query 
- Exi
