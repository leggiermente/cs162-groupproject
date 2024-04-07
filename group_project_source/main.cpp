#include <iostream>
using namespace std;
#include "Staff.h"
#include "Student.h"
int sems=1;
Semester curSem;
schoolYear s;
bool createClass=false;
int main()
{
    s=importSchoolYear("2023-2024");
    importSemesterandCourse(s,curSem,1);
    return 0;
}
