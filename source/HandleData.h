#pragma once
#include <string>

#include "Student.h"
#include "Staff.h"
#include "Struct.h"
#include "UI.h"

std::string floatToString(float num);
Student* readStudentCSV(string filename, int& numStu);
Staff* readStaffCSV(string filename, int& numStaff);
//Course* readDirectory(string directory, int& numCourse);
void readSemesterInSchoolYear(string path, Semester& semester);
SchoolYear* readSchoolYear(string path, int& numSchoolYear);
void readCourseInSemester(string path, SchoolYear* schoolYearArr, int numSchoolYear);
void readStudentTXT(string path,Class& classStu);
Class* readClass(string path, int& numClass);
void printTest(Class* classArr, int numClass, SchoolYear* schoolYearArr, int numSchoolYear);

void copyCourse(Course src, Course &dis);
void saveStudent(Course &src, RowInfor* &stu);