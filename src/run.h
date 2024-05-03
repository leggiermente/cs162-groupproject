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
void loadUIv2();
void connectPointerofSessionandDow();

// Support function
void saveData();
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
void addYearToStu(Course* thatCourse, Student* thatStu);
void loadUIAll();

// Handle event && Draw UI
void handleStudentPage();
void drawStudentPage();
void handleStuProfilePage();
void drawStuProfilePage();
void handleStuPw();
void drawStuPw();

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
void handleScoreInStuPage();
void drawScoreInStuPage();
void handleEventScoreboardPage();
void drawScoreboardPage();

// Main function
void RunApp();

// Update data and UI dynamically
SchoolYear* loadAddSchoolyear(SchoolYear* schoolYearArr, int& numSchoolYear);
Semester* loadAddSemester(Semester* old, int& numSemester);
Class* loadAddClass();
Student* loadAddStudent();
Course* loadAddCourse();
ScoreStu* loadAddCourseToStu(Student* stuAdd);
void deleteStuInCourse(string stuID);
void deleteScoreInStu(string cID, Student* currStu);
void deleteCourse();

// Free memory
void freeButtons();