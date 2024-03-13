#include "newClass.h"

int main()
{
    string filename = "SchoolYear.txt";
    School_Year targetSchool;
    createNewClass(filename);
    updateClassListOfSchoolYear(filename, targetSchool);
    return 0;
}
