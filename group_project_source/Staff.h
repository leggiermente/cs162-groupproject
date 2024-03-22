#include "Struct.h"
#ifndef STAFF_H_INCLUDED
#define STAFF_H_INCLUDED
struct Staff;
struct Staff{
    int staffID;
    string password;
    string firstName,lastName;
};
schoolYear importSchoolYear();
Class readClass(string fileName,string nameClass);
Student *readStudentCSV(string fileName, int& numStu);
void updateStudentFromInput(Class &curClass);
void ImportStudentsToCoursesInSemester(Student *students, int numStu, Course thisCourse);
void addNewSchoolYear(int &sems, schoolYear schyrs, bool &createClassOption);
void addStudentintoClass(schoolYear &schyrs, bool createClassOption);
void addCourse(Semester &sems);
void outputClass(string fileName,Class curClass);
void outputSchoolYear(schoolYear &schyrs);
void outputCourse(string fileName,Course curCourse);
bool checkFormatDayOfTheWeek(string format);
bool checkFormatSession(string format);
#endif // STAFF_H_INCLUDED
