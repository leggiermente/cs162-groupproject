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
bool readCSVStuToClass(string path, Class& thatClass, int& numIc);
bool readCSVStuToCourse(string path, Class* allClass, Course& thatCourse, int& numStuAdd, int numClass);
bool readScoreCSV(string path, Course& thatCourse);
bool exportFileIdStu(string path, Course& thatCourse);
void printTest(Class* classArr, int numClass, SchoolYear* schoolYearArr, int numSchoolYear);