#include <iostream>
using namespace std;
#include "Staff.h"
#include "Student.h"
int sems=3;
schoolYear s;
bool createClass=false;
int main()
{
    s=importSchoolYear();
    addNewSchoolYear(sems,s,createClass);
    return 0;
}
