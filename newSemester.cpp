#include "newSemester.h"
#include <iostream>
#include <fstream>
using namespace std;
void createNewSemester(SchoolYear* &schoolYear)
{
    Semester* newListSemes = new Semester[++schoolYear->numSemester];
    for (int i=0; i < schoolYear->numSemester-1; i++)
        newListSemes[i] = schoolYear->listSemester[i];
    cin >> newListSemes[schoolYear->numSemester-1].startDate;
    cin >> newListSemes[schoolYear->numSemester-1].endDate;
    cin >> newListSemes[schoolYear->numSemester-1].numCourses;
    
    delete [] schoolYear->listSemester;
    schoolYear->listSemester = newListSemes;
}

