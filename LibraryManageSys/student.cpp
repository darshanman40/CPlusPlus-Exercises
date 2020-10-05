
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <string.h>

using namespace std;

class student 
{
    char admissionNum[6];
    char name[20];
    char studentBookNum[6];
    int token;

public:
    void createStudent()
    {
        cout << "\n\n NEW STUDENT ENTRY\n";
        
        cout << "\nEnter The Admission No.: ";
        fgets(admissionNum, 6, stdin);
        
        cout << "\nEnter The Student Name: ";
        fgets(name, 20, stdin);
        token = 0;
        studentBookNum[0] ='\0';
        cout << "\n\nStudent Record Created..";
    };
    
    void showStudent()
    {
        cout << "\nAdmission No.: " << admissionNum;
        cout << "\nStudent Name: " << name;
        cout << "\nNo. of Book Issued: " << token << endl;
        if (token==1)
            cout << "\nBook No.: " << studentBookNum << endl;
    };
    
    void modifyStudent()
    {
        cout << "\nAdmission No.: " << admissionNum;
        cout << "\nModify Student Name: ";
        fgets(name,20,stdin);
    };
    
    char* getAdmissionNum()
    {
        return admissionNum;
    };
    
    char* getStudentBookNum()
    {
        return studentBookNum;
    };
    
    int getToken()
    {
        return token;
    };
    
    void addToken()
    { token = 1; }
    
    void resetToken()
    { token = 0; }
    
};