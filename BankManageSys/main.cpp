//
//  main.cpp
//  BankManageSys
//
//  Created by Darshan Manchekar on 5/7/18.
//  Copyright © 2018 Darshan Manchekar. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <curses.h>
#include <ctype.h>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

class account {
    int acno;
    char name[50];
    int deposite;
    char type;
    
public:
    void create_account();
    void show_account();
    void modify();
    void deposit(int);
    void withdraw(int);
    void report() const;
    int return_account_no() const;
    int return_deposit() const;
    char return_type() const;
};

void account::create_account(){
    cout<<"\nEnter Account Number: ";
    cin>>acno;
    cout<<"\nEnter the Account holder name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout<<"\nEnter Account type (C/S): ";
    cin>>type;
    type = toupper(type);
    cout << "\nEnter the Inital ammount to deposite (>=1000 for current and >=500 for savings): ";
    cin >> deposite;
    cout << "\nAccount Created";
    
};

void account::show_account(){
    cout<<"\nAccount no.: "<<acno;
    cout<<"\nAccount Holder name: "<<name;
    cout<<"\nType of account: "<<type;
    cout<<"\nBalance amount: "<<deposite;
};

void account::modify(){
    cout<<"\nAccount No. : "<<acno;
    cout<<"\nModify Account Holder Name: ";
    cin.ignore();
    cin.getline(name, 50);
    cout<<"\nModify Type of Account: ";
    cin>>type;
    type=toupper(type);
    cout<<"\nModify Balance Amount: ";
    cin>>deposite;
};

void account::deposit(int x)
{
    deposite+=x;
};

void account::withdraw(int x)
{
    deposite-=x;
};

void account::report() const
{
    cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposite<<endl;
};

int account::return_account_no() const
{
    return acno;
};

int account::return_deposit() const
{
    return deposite;
};

char account::return_type() const
{
    return type;
};

//
// File Handling functions declaration
//

void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int,int);
void intro();


// Function to write in file
void write_account(){
    account ac;
    ofstream outFile;
    outFile.open("account.dat",ios::binary|ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
    outFile.close();
};

// Read specific record from file
void display_sp(int n){
    account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"\nFile could not be open!! Press any key...";
        return;
    }
    cout<<"\nBALANCE DETAILS\n";
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if (ac.return_account_no()==n)
        {
            ac.show_account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
        cout<<"\n\nAccount number doesnot exist";
};

// Modify specific record from file
void modify_account(int n)
{
    bool found=false;
    account ac;
    fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"\nFile could not be open !! Press any key...";
        return;
    }
    while(!File.eof() && !found)
    {
        File.read(reinterpret_cast<char *> (&ac),sizeof(account));
        if(ac.return_account_no()==n)
        {
            ac.show_account();
            cout<<"\n\nEnter The New Details of account"<<endl;
            ac.modify();
            int pos=(-1)*static_cast<int>(sizeof(account));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac),sizeof(account));
            cout<<"\n\n\t Record Updated";
            found=true;
        }
    }
    File.close();
    if(found==false)
        cout<<"\n\n No Record Found";
};

// function to delete record of file

void delete_account(int n){
    account ac;
    ifstream inFile; //, outFile;
    ofstream outFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if(ac.return_account_no()!=n)
            outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat","account.dat");
    cout<<"\n\nRecord Deleted ..";
};

// Display all accounts
void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open!! Press any key...";
        return;
    }
    cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout<<"====================================================\n";
    cout<<"A/c no.      NAME           Type  Balance\n";
    cout<<"====================================================\n";
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
};

// deposit or withdraw the amount
void deposit_withdraw(int n, int option)
{
    int amt;
    bool found=false;
    account ac;
    fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not be open !! Press any key...";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if(ac.return_account_no()==n)
        {
            ac.show_account();
            if(option==1)
            {
                cout<<"\n\nTo Deposit Amount ";
                cout<<"\n\nEnter the amount to be deposited: ";
                cin>>amt;
                ac.deposit(amt);
            }
            if(option==2)
            {
                cout<<"\n\nTo Withdraw Amount ";
                cout<<"\n\nEnter the amount to withdraw: ";
                cin>>amt;
                int bal=ac.return_deposit() - amt;
                if((bal<500 && ac.return_type()=='S') || (bal<1000 && ac.return_type()=='C'))
                    cout<<"\n\nInsufficience balance";
                else
                    ac.withdraw(amt);
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac),sizeof(account));
            cout<<"\n\nRecord updated";
            found = true;
        }
    }
    File.close();
    if(found==false)
        cout<<"\n\nRecord not found";
};



void intro()
{
    cout<<"\n\n\n\t  BANK";
    cout<<"\n\n\tMANAGEMENT";
    cout<<"\n\n\t  SYSTEM";
    cout<<"\n\n\n\nMADE BY : Darshan Manchekar";
    cout<<"\n\nSCHOOL : CSU";
    cout<<"\n";
//    getch();
}

int main(int argc, const char * argv[]) {
    // insert code here...
    char ch;
    int num;
    intro();
//    account ac;
    do{
        system("clear");
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01. NEW ACCOUNT";
        cout<<"\n\n\t02. DEPOSIT AMOUNT";
        cout<<"\n\n\t03. WITHDRAW AMOUNT";
        cout<<"\n\n\t04. BALANCE ENQUIRY";
        cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
        cout<<"\n\n\t06. CLOSE AN ACCOUNT";
        cout<<"\n\n\t07. MODIFY AN ACCOUNT";
        cout<<"\n\n\t08. EXIT";
        cout<<"\n\n\tSelect Your Option (1-8) ";
        cin>>ch;
        system("clear");
        switch(ch){
            case '1':
                write_account();
                break;
            case '2':
                cout<<"\n\nEnter the account number: "; cin>>num;
                deposit_withdraw(num, 1);
                break;
            case '3':
                cout<<"\n\nEnter the account number: "; cin>>num;
                deposit_withdraw(num, 2);
                break;
            case '4':
                cout<<"\n\n\tEnter The account No.: "; cin>>num;
                display_sp(num);
                break;
            case '5':
                display_all();
                break;
            case '6':
                cout<<"\n\nEnter the Account No.: "; cin>>num;
                deposit_withdraw(num, 2);
                delete_account(num);
                break;
            case '7':
                cout<<"\n\nEnter the Acoount No.: "; cin>>num;
                modify_account(num);
                break;
//            case '8':
//                cout<<"Thank you for using Bank Management System.";
//                break;
            };
    }while(ch!='8');
    
    
    return 0;
}
