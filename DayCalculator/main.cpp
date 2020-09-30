#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//  1,2,3,4,5,6,7,8,9,10,11,12
// Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sept, Oct, Nov, Dec
//  31, 28/29, 30, 31, 30, 31, 31, 30, 31, 30, 31

const string LOG_WARN_TAG = "WARN: ";

string calculateDate(int date,int month,int year,int days)
{
    date += days;
    bool isCalculationDone = false;
    int monthDays =0;
    string dayString;
    while (!isCalculationDone)
    {
        switch (month)
        {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                monthDays = 31;    
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                monthDays = 30;
                break;
            case 2:
                if (year % 4 == 0) monthDays = 29;
                else monthDays = 28;
                break;
                
        }

        if (date > monthDays)
        {
            date = date - monthDays;
            month++;
            if (month > 12)
            {
                month = 1;
                year++;
            }
        }else
        {
            isCalculationDone = true;
        }

    }

    dayString = to_string(date);
    dayString.append("-");
    dayString.append(to_string(month));
    dayString.append("-");
    dayString.append(to_string(year));

    return dayString;
}

bool isNumber(string s) 
{ 
    for (int i = 0; i < s.length(); i++) 
        if (isdigit(s[i]) == false) 
            return false; 
  
    return true; 
} 

int main(int argc, char** argv)
{
    int date,month,year;
    int days;
    if (argc != 5)
    {
        cout << LOG_WARN_TAG << "Couldnt found valid argument count " << endl;
        cout << LOG_WARN_TAG << "Entering default arguments" << endl;
        date = 15;
        month = 8;
        year = 2020;
        days = 84;
        
    } 
    else
    {
        cout << "Parsing entered arguments" << endl;
        if (!isNumber(argv[1])) return 1;
        date = atoi(argv[1]);
        
        month = atoi(argv[2]);
        year = atoi(argv[3]);
        days = atoi(argv[4]);    
    }
    string newDate = calculateDate(date,month,year,days);
    cout << "New Date: " << newDate << endl;
    
    return 0;
}
