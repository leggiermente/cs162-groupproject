#include <iostream>
using namespace std;
#include "Staff.h"
int sems=1;
Semester curSem;
schoolYear s;
bool createClass=false;
int main()
{
    s=importSchoolYear("2023-2024");
    importSemesterandCourse(s,curSem,1);
    outputCourseScoreBoard(s,curSem,curSem.coursesListInSemester[0]);
    return 0;
}
