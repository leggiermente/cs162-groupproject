#include "newClass.h"

int main()
{
    string filename = "SchoolYear.csv";
    School_Year targetSchool;
    int numClass = 0;
    createNewClass(targetSchool, numClass);
    updateSchoolYearCSV(filename, targetSchool, numClass);
    return 0;
}
