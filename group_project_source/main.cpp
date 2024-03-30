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
    s=importSchoolYear();
    importSemesterandCourse(s,curSem);
    removeCourse(s,curSem);
    return 0;
}
