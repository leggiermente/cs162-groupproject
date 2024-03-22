#include "newClass.h"
#include "newSemester.h"
#include "removeStudent.h"
int main()
{
    
    string filename = "SchoolYear.txt";
    schoolYear targetSchool;
    targetSchool.classList = nullptr;
    loadClassFromFile(filename, targetSchool);
    createNewClassToFile(filename);
    //updateFileSchoolYear(filename, targetSchool);
    //createNewSemesterToFile(filename);
    return 0;
}
