#include "Struct.h"

#include <fstream>

void addToCoursesInSemesterToStudents(Student *students, int numStu, Course thisCourse)
{
    for (int i = 0; i < numStu; ++i)
    {
        students[i].numCourse++;
        Course* temp = new Course[students[i].numCourse];
        for (int j = 0; j < students[i].numCourse - 2; ++j)
        {
            temp[j] = students[i].courseOfStudent[j];
        }
        temp[students[i].numCourse - 1] = thisCourse;
        students[i].courseOfStudent = temp;
        delete [] temp;
    }
    
    // add to student files
    std::ifstream fin;
    std::ofstream fout;
    for (int i = 0; i < numStu; i++)
    {
        fin.open(students->studentID + ".txt");
        fout.open(students->studentID + "2.txt");
        string line;
        for (int i = 0; i < 9; i++) // chừa 9 dòng đầu
        {
            getline(fin, line);
            fout << line << endl;
        }
        int num = students[i].numCourse;
        fin >> line; //ignore the nummber of courses, already in the RAM
        for (int i = 0; i < num; ++i)
        {
            fout << thisCourse.ID << endl;
        }
        while (getline(fin, line))
        {
            fout << line << endl;
        }
        fin.close();
        fout.close();
        std::string oldFile = students->studentID + ".txt";
        std::string newFile = students->studentID + "2.txt";
        std::string renamedFile = students->studentID + ".txt";

        remove(oldFile.c_str());
        rename(newFile.c_str(), renamedFile.c_str());
    }
}
