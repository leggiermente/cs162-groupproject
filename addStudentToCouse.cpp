#include <fstream>

using namespace std;
void addStudentToCourse(Course thisCourse, Student *student, int numStu)
{
    thisCourse.listStudentInCourse = student;
    ofstream fout;
    fout.open(thisCourse.courseID + ".csv");
    fout << numStu << " : number of students in this course\n";
    fout << "Student ID, Student Name, Total Mark, Final Mark, Midterm Mark, Other Mark\n";
    for (int i = 0; i < numStu; i++)
    {
       fout << student[i].studentID << ", " << student[i].studentName << "\n";
    }
    fout.close();
}