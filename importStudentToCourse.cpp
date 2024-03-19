#include "Struct.h"

#include <fstream>

void ImportStudentsToCoursesInSemester(Student *students, int numStu, Course thisCourse)
{
    thisCourse.listStudentInCourse = students;
    for (int i = 0; i < numStu; i++)
    {
        students[i]
    }
    std::ifstream fin;
    std::ofstream fout;
    for (int i = 0; i < numStu; i++)
    {
        fin.open(students->studentID + ".txt");
        fout.open(students->studentID + "2.txt");
        string line;
        getline(fin, line);
        fout << line << endl;
        fout << thisCourse.ID << endl;
        fin.close();
        fout.close();
        delete(students->studentID + ".txt");
        rename(students->studentID + "2.txt", students->studentID + ".txt");
    }
}