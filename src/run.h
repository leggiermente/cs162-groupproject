#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#include "readCSV.h"
#include "run.h"
#include "UI.h"
struct CurrentUser {
    bool isStaff = false;
    Staff* staff = nullptr;
    Student* student = nullptr;
    std::string id = "";
    std::string password = "";
    int indexSchoolyear = -1,
        indexSemester,
        indexClass,
        indexCourse,
        indexStudentInClass;
};
void loadSchoolyears();
bool validateUser();
bool isNumber(const std::string& str);
void clearInput();
void RunApp();
void freeButtons();
LinkedButton** loadAddYearButton(SchoolYear* schoolYearArr, LinkedButton** old, int& numSchoolYear);
SchoolYear* loadAddSchoolyear(SchoolYear* schoolYearArr, int& numSchoolYear);
