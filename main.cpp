#include "newClass.h"
#include "newSemester.h"

int main()
{
    string filename = "semester.txt";
    //schoolYear targetSchool;
    //loadClassFromFile(filename, targetSchool);
    //createNewClass(targetSchool);
    //updateFileSchoolYear(filename, targetSchool);
    createNewSemesterToFile(filename);
    return 0;
}
