#include "removeStudent.h"

void removeStudentFromCourse(Student* student, Course* course )
{
    int indexFound = -1;
    
    for (int i=0; i<course->numStudents; i++)
    {
        if (course->listStudentInCourse[i].studentID == student->studentID)
        {
            indexFound = i;
            break;
        }
    }
    
    if (indexFound == -1) cout <<"Student not found in the course\n";
    else
    {
        if (course->numStudents == 1)
        {
            delete [] course->listStudentInCourse;
            course->listStudentInCourse = nullptr;
        }
        else
        {
            Student* newListStu = new Student[course->numStudents-1];
            
            for (int i=0; i< indexFound; i++)
                newListStu[i] = course->listStudentInCourse[i];
            
            for (int i=indexFound; i < course->numStudents -1 ; i++)
                newListStu[i] = course->listStudentInCourse[i+1];
            
            course->numStudents--;
            delete [] course->listStudentInCourse;
            course->listStudentInCourse = newListStu;
            cout <<"Student with ID: " <<student->studentID<<" is removed from the course successfully.\n";
        }
    }
}
