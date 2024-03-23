#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#include "readCSV.h"
#include "run.h"
struct CurrentUser {
    bool isStaff;
    Staff staff;
    Student student;
    std::string id = "";
    std::string password = "";
    int indexSchoolyear,
        indexSemester,
        indexClass,
        indexCourse,
        indexStudentInClass;
};
void init();
void loadSchoolyears();
bool validateUser();
bool isNumber(const std::string& str);
void clearInput();
void RunApp();
