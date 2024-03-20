#include "newSemester.h"
#include <iostream>
#include <fstream>
using namespace std;
void createNewSemesterToFile(string &filename)
{
    Semester s;
    cout <<"Input the numbers of semester in school year: ";
    cin >> s.numSemesterInSchoolYear;
    
    cout <<"Input the start date (DD MM YYYY): ";
    cin >> s.startDate >> s.startMonth >> s.startYear;
    
    cout <<"Input the end date (DD MM YYYY): ";
    cin >> s.endDate >> s.endMonth >> s.endYear;
    
    ofstream file(filename, ios::app);
    if (file.is_open())
    {
        file << s.numSemesterInSchoolYear <<",";
        file << s.startDate <<"/" << s.startMonth <<"/"<< s.startYear <<",";
        file << s.endDate <<"/" <<s.endMonth <<"/"<< s.endYear <<"\n";
    }
    
}

