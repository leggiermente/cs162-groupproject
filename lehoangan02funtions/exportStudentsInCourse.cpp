#include "exportStudentsInCourse.hpp"
#include <iostream>
#include <fstream>
void exportStudentsInCourse(string filename, Course thisCourse)
{
    fstream f;
    f.open(filename, ios::out);
    for (int i = 0; i < thisCourse.numStu; i++)
    {
        f << thisCourse.listStudentInCourse[i].studentID << "," << thisCourse.listStudentInCourse[i].firstName << "," << thisCourse.listStudentInCourse[i].lastName << endl;
    }
    f.close();
}