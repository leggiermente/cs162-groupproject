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
struct SearchArrPointerUI {
    LinkedButton** linkedButton = nullptr;
    string* nameButton = nullptr;
    int* idButton = nullptr;
    int mxNumButton = 0;
    int curNumButton = 0;
    bool active = false;
    SearchArrPointerUI(int mxNumButton) {
        this->mxNumButton = mxNumButton;
    	linkedButton = new LinkedButton * [mxNumButton];
        nameButton = new string[mxNumButton];
        idButton = new int[mxNumButton];
    }
    void loadButtonUI() {
        float x = 115, y = 210;
        for (int i = 0; i < curNumButton; ++i) {
            if (i % 12 == 0 && i != 0) { // Return origin when need new page
                x = 115;
                y = 210;
            }
            else if (i % 6 == 0 && i != 0) { // x,y coordinate of button for each page
                x += 225.0f;
                y = 210;
            }
            linkedButton[i] = new LinkedButton(x, y, "image/Button200x45.png", nameButton[i]);
            y += 65.0f;
        }
	}
    void reset() {
        for (int i = 0; i < curNumButton; i++) {
			delete linkedButton[i];
		}
		delete[] linkedButton;
		delete[] nameButton;
		delete[] idButton;
	}
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
bool isFloat(const std::string& s);
void searchYear();
void searchClass();
int searchCourse();
Student* findPointerStu(string stuID);
bool isStuNotInCourse(string stuID);
void calculateOneStuGPA(Student* thatStu);
bool isScoreHandValid();
void updateScoreByHand();
void calculateAllStuGPA();

// Handle event && Draw UI
void handleChangePassword();
void drawChangePassword();
void handleProfile();
void drawProfile();
void handleStaffSchoolYearPage();
void drawStaffSchoolYearPage();
void handleEventCoursePage();
void drawCoursePage();
void handleEventDetailCoursePage();
void drawDetailCoursePage();
void handleStaffClassPage();
void drawStaffClassPage();
void handleStaffClassDetailPage();
void drawStaffClassDetailPage();
void handleStuDetailPage();
void drawStuDetailPage();
void handleEventScoreboardPage();
void drawScoreboardPage();

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
ScoreStu* loadAddCourseToStu(Student* stuAdd);
void loadNewScoreRowButton(int numOdd);
void deleteStuInCourse(string stuID);
void deleteScoreInStu(string courseID, string stuID);
void loadNewGPAtoStu(ScoreRowInStu*& thatRowArr, Student* thatStu);
void loadNewGPAtoStuInCourse();
void deleteCourse();
void loadNewCourseButton();
LinkedButton** loadAddCSVStuToClassButton(int numIc);

// Free memory
void freeButtons();