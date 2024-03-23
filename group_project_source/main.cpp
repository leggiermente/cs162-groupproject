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
    importSemesterandCourse(curSem);
    removeCourse(curSem);
    return 0;
}
