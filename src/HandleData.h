#pragma once
#include <string>

#include "Student.h"
#include "Staff.h"

Student* readStudentCSV(string filename, int& numStu);
Staff* readStaffCSV(string filename, int& numStaff);
//Course* readDirectory(string directory, int& numCourse);
void readSemesterInSchoolYear(string path, Semester& semester);
SchoolYear* readSchoolYear(string path, int& numSchoolYear);
void readCourseInSemester(string path, SchoolYear* schoolYearArr, int numSchoolYear, Class* classArr, int numClass);
void readStudentTXT(string path,Class& classStu);
Class* readClass(string path, int& numClass);
void printTest(Class* classArr, int numClass, SchoolYear* schoolYearArr, int numSchoolYear);

void saveSchoolYear(string path, SchoolYear* schoolYearArr, int numSchoolYear);
void saveSemesterInSchoolYear(string path, Semester semester);
void saveCourseInSemester(string path, SchoolYear* schoolYearArr, int numSchoolYear, int numCourse);
void saveClass(string path, Class* classesArr, int numClass);
void saveStudentTXT(string path,Class classStu);
