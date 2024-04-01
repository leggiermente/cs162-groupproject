#pragma once
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#include "HandleData.h"
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
LinkedButton** loadAddSemeButton(Semester* semeArr, LinkedButton** old, int& numSeme);
SchoolYear* loadAddSchoolyear(SchoolYear* schoolYearArr, int& numSchoolYear);
Semester* loadAddSemester(Semester* old, int& numSemester);
Class* loadAddClass();
LinkedButton** loadAddClassButton();
Student* loadAddStudent();
LinkedButton** loadAddStuButton();