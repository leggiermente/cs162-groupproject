#pragma once
#include <string>

#include "Student.h"
#include "Staff.h"

struct CurrentUser {
    bool isStaff;
    Staff staff;
    Student student;
};

Student* readStudentCSV(string filename, int& numStu);
Staff* readStaffCSV(string filename, int& numStaff);
Course* readDirectory(string directory, int& numCourse);