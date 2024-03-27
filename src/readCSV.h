#pragma once
#include <string>

#include "Student.h"
#include "Staff.h"

Student* readStudentCSV(string filename, int& numStu);
Staff* readStaffCSV(string filename, int& numStaff);
//Course* readDirectory(string directory, int& numCourse);
Student* readStudentText(string path, int& numStu);
void readSemesterInSchoolYear(string path, Semester& semester);
schoolYear* readSchoolYear(string path, int& numSchoolYear);
void readCourseInSemester(string path, schoolYear* schoolYearArr, int numSchoolYear);

void readStudentTXT(string path,Class& classStu);
Class* readClass(string path, int& numClass);
void printTest(Class* classArr, int numClass, schoolYear* schoolYearArr, int numSchoolYear);