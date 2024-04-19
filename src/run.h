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

// Load UI
void loadUI();
void loadUIfromDatabase();
void connectPointerofSessionandDow();

// Support function
bool validateUser();
bool isNumber(const std::string& str);
void assignCourseForModify();
void clearInput();

// Handle event && Draw UI
void handleStaffSchoolYearPage();
void drawStaffSchoolYearPage();
void handleEventCoursePage();
void drawCoursePage();
void handleEventDetailCoursePage();
void drawDetailCoursePage();
void handleEventDetailStudentPage();
void drawDetailStudentPage();
void handleStaffClassPage();
void drawStaffClassPage();

// Main function
void RunApp();

// Update data and UI dynamically
LinkedButton** loadAddYearButton(SchoolYear* schoolYearArr, LinkedButton** old, int& numSchoolYear);
LinkedButton** loadAddSemeButton(Semester* semeArr, LinkedButton** old, int& numSeme);
SchoolYear* loadAddSchoolyear(SchoolYear* schoolYearArr, int& numSchoolYear);
Semester* loadAddSemester(Semester* old, int& numSemester);
Class* loadAddClass();
LinkedButton** loadAddClassButton();
Student* loadAddStudent();
LinkedButton** loadAddStuButton();
Course* loadAddCourse();
LinkedButton** loadAddCourseButton();

// Free memory
void freeButtons();
