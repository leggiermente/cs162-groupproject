#pragma once
#include <string>

#include "Student.h"
#include "Staff.h"

struct CurrentUser {
    bool isStaff;
    bool isLogin = false;
    Staff staff;
    Student student;
};

Student* readStudentCSV(string filename, int& numStu);
Staff* readStaffCSV(string filename, int& numStaff);