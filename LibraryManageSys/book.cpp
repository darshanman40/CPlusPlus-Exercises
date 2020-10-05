
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <string.h>

using namespace std;

class book
{
    char bookNum[6];
    char bookName[50];
    char authorName[20];
    
public:
    void createBook()
    {
        cout << "\nNew Book Entry...\n";
        cout << "\nEnter Book Number: ";
        fgets(bookNum, 6, stdin);
        cout << "\nEnter The Name of The Book: ";
        fgets(bookName, 50, stdin);
        cout << "\nEnter The Author Name: ";
        fgets(authorName, 20, stdin);
    };
    
    void showBook()
    {
        cout << "\n\nBook number : " << bookNum;
        cout << "\nBook Name: " << bookName;
        cout << "\nAuthor Name: " << authorName;
    };
    
    void modifyBook()
    {
        cout << "\nBook No.: " << bookNum;
        cout << "\nModify Book Name: " << bookName;
        cout << "\nModify Author's Name: " << authorName;
    };
    
    char* getBookNum()
    {
        return bookNum;
    };
    
    void report()
    {
        cout << bookNum << setw(30) << bookName << setw(30) << authorName << endl;
    };
};