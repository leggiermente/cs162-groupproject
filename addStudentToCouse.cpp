#include <fstream>
#include "Struct.h"
#include "Student.h"
#include <iostream>

using namespace std;
void addStudentToCourse(Course thisCourse, Student *student, int numStu)
{
    if (thisCourse.numStu + numStu > thisCourse.maxStudents)
    {
        cout << "Cannot add student to course because the number of students in the course exceeds the maximum number of students allowed in the course." << endl;
        return;
    }
    int newNumStu = thisCourse.numStu + numStu;
    Student *newListStudent = new Student[newNumStu];
    for (int i = 0; i < thisCourse.numStu; ++i)
    {
        newListStudent[i] = thisCourse.listStudentInCourse[i];
    }
    for (int i = 0; i < numStu; ++i)
    {
        newListStudent[thisCourse.numStu + i] = student[i];
    }
    thisCourse.numStu = newNumStu;
    thisCourse.listStudentInCourse = newListStudent;
    delete[] thisCourse.listStudentInCourse;
    ifstream fin;
    fin.open(thisCourse.ID + ".csv");
    if (!fin.is_open())
    {
        ofstream fout;
        fin.close();
        // File not found
        fout.open(thisCourse.ID + ".csv");
        fout << thisCourse.className << "," << thisCourse.teacher << "," << thisCourse.numCredits << "," << thisCourse.maxStudents << endl;
        fout << numStu << endl;
        fout << "Student ID,First Name,Last Name,Total Mark,Final Mark,Midterm Mark,Other Mark\n";
        for (int i = 0; i < numStu; i++)
        {
            fout << student[i].Student_ID << "," << student[i].FirstName << "," << student[i].LastName << "\n";
        }
        fout.close();
    }
    else{
        ofstream fout; fout.open(thisCourse.ID + "2" + ".csv");
        string line;
        getline(fin, line); fout << line << endl;
        fin >> numStu; fout << numStu + thisCourse.numStu << endl;
        for (int i = 0; i < numStu; i++)
        {
            getline(fin, line); fout << line << endl;
        }
        for (int i = numStu; i < newNumStu; ++i)
        {
            fout << student[i].Student_ID << "," << student[i].FirstName << "," << student[i].LastName << "\n";
        }
        fin.close(); fout.close();
        string oldFileName = thisCourse.ID + ".csv";
        string newFileName = thisCourse.ID + "2" + ".csv";
        remove(oldFileName.c_str());
        rename(oldFileName.c_str(), newFileName.c_str());
    }
}