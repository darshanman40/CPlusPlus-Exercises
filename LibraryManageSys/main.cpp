//
//  main.cpp
//  LibraryManageSys
//
//  Created by Darshan Manchekar on 5/14/18.
//  Copyright © 2018 Darshan Manchekar. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <string.h>

// Local imports
#include "student.cpp"
#include "book.cpp"

using namespace std;


/*
 GLOBAL DECLARATION
 */

fstream fp, fp1;
book bk;
student st;


void writeBook()
{
    char ch;
    fp.open("./data/book.dat", ios::out|ios::app);
    do
    {
        bk.createBook();
        fp.write((char*)&bk, sizeof(book));
        cout << "\n\nDo you want add more records..(y/n)? ";
        cin >> ch;
    }while(ch == 'y' || ch == 'Y');
    fp.close();
};


void writeStudent()
{
    char ch;
    fp.open("./data/stdent.dat", ios::out|ios::app);
    do
    {
        st.createStudent();
        cout << "\n\nDo you want to add more record..(y/n)? ";
        cin >> ch;
    } while(ch == 'y'|ch == 'Y');
    fp.close();
};


void displaySpcificBook(char n[])
{
    cout << "\nBook Details\n";
    int flag = 0;
    fp.open("./data/book.dat", ios::in);
    while(fp.read((char*)&bk, sizeof(book)))
    {
        if(strcmp(bk.getBookNum(), n) == 0)
        {
            bk.showBook();
            flag = 1;
        }
    };
    
    fp.close();
    if(flag == 0)
        cout << "\n\nBook does not exist";
//    getch();
//    system("clear");
};


void displaySpecificStudent(char n[])
{
    int flag=0;
    cout << "\nStudent Details\n";
    fp.open("./data/student.dat", ios::in);
    while(fp.read((char*)&st, sizeof(student)))
    {
        if(strcmp(st.getAdmissionNum(), n) == 0)
        {
            st.showStudent();
            flag = 1;
        }
    }
    fp.close();
    if(flag == 0)
        cout << "\nStudent " << n << " does not exist";
};


// Function to modify book
void modifyBook()
{
    char n[6];
    int found = 0;
    system("clear");
    cout << "\n\n\tModify Book Record";
    cout << "\n\n\tEnter the book no. of The book";
    cin >> n;
    fp.open("./data/book.dat", ios::in|ios::out);
    while(fp.read((char*)&bk, sizeof(book)) && found == 0)
    {
        if(strcmp(bk.getBookNum(),n) == 0)
       {
           bk.showBook();
           cout << "Enter the details" << endl;
           bk.modifyBook();
           long pos = -1 * sizeof(bk);
           fp.seekp(pos, ios::cur);
           fp.write((char*)&bk, sizeof(book));
           cout << "\n\nRecord Updated for book: " << n;
           found = 1;
       }
    }
    if(found == 0)
        cout << "\nRecord " << n << " Not Found";
    //getch();
};


// Function to modify student details
void modifyStudent()
{
    char n[6];
    int found = 0;
    system("clear");
    cout << "\n\n\tModify Student Record. ";
    cout << "\n\n\tEnter the admission no. of the student";
    cin >> n;
    fp.open("./data/student.dat", ios::in|ios::out);
    while(fp.read((char*)&st, sizeof(student)))
    {
        if(strcmp(st.getAdmissionNum(), n) == 0)
        {
            st.showStudent();
            cout << "\nEnter The New Details of student" << endl;
            st.modifyStudent();
            long pos = -1 * sizeof(st);
            fp.seekp(pos, ios::cur);
            fp.write((char*)&st, sizeof(student));
            cout << "\n\nRecord updated for student " << n << endl;
            found=1;
        }
    }
    fp.close();
    if(found == 0)
        cout << "\n\nRecord " << n << " not found";
    //getch();
}


// Function to delete student record
void deleteStudent()
{
    char n[6];
    int found = 0;
    cout << "\n\nDelete Student...";
    cout << "\nEnter Student admission no. ";
    cin >> n;
    fp.open("./data/student.dat", ios::in|ios::out);
    fstream fp2;
    fp2.open("./data/dataTemp.dat", ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&st, sizeof(student)))
    {
        if(strcmp(st.getAdmissionNum(), n) != 0)
            fp2.write((char*)&st, sizeof(student));
        else
            found = 1;
    };
};


int main(int argc, const char * argv[]) 
{
    book b;
    student s;

    b.createBook();
    cout << "\n\nCreated following book,";
    b.showBook();

    return 0;
}