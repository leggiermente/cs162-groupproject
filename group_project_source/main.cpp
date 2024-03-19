#include <iostream>
using namespace std;
#include "Staff.h"
#include "Student.h"
int sems=3;
Semester curSem;
schoolYear s;
bool createClass=false;
int main()
{
    s=importSchoolYear();
    curSem.numSemesterInSchoolYear=sems;
    addCourse(curSem);
    return 0;
}
