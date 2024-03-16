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
    addStudentintoClass(s,true);
    int test=0; //test if the update can be completed
    for (int i=0;i<s.classCount;i++){
        if (s.classList[i].classID=="22TT1"){
            test=i;
        }
    }
    outputClass("../database/class/"+s.classList[test].classID+".txt",s.classList[test]);
    return 0;
}
