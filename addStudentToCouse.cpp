#include <fstream>
#include "Struct.h"
#include "Student.h"

using namespace std;
void addStudentToCourse(Course thisCourse, Student *student, int numStu)
{
    thisCourse.listStudentInCourse = student;
    ofstream fout;
    fout.open(thisCourse.ID + ".csv");
    fout << numStu << " : number of students in this course\n";
    fout << "Student ID, First Name, Last Name, Total Mark, Final Mark, Midterm Mark, Other Mark\n";
    for (int i = 0; i < numStu; i++)
    {
       fout << student[i].Student_ID << ", " << student[i].FirstName << ", " << student[i].LastName << "\n";
    }
    fout.close();
}