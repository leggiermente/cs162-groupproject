#include <iostream>

#include "run.h"
#include "HandleData.h"
#include "UI.h"

sf::RenderWindow window(sf::VideoMode(1280, 720), "Course Management", sf::Style::Close);
sf::Event event;
sf::Clock myClock;
const float xMid = window.getSize().x / 2.0f;
const float yMid = window.getSize().y / 2.0f;

// General UI
Button background(0,0,"image/Backgound.png");
InputWithHead inputUserBox(339.0f, 284.0f, "image/TextBox.png", "Username (ID)");
PasswordBox inputPassBox(339.0f, 390.0f, "image/TextBox.png", "Password");
ShowPasswordButton showPassButton(339, 451);
LoginButton loginButton(339, 538, "image/LoginButton.png");
Button loginBox(308, 56, "image/LoginBox.png");
CheckStaffButton checkStaffButton(xMid - 285.0f, yMid + 110.0f, "image/CheckStaffButton.png", "image/CheckedStaffButton.png");
Button menu(xMid, yMid, "image/MenuBackground.png");
Button passwordChange(1128, 170, "image/Password.png");
Button logOutButton(1128, 204, "image/LogOut.png");
HrztBar hrztBarYear(415, 150, 117, 5);
HrztBar hrztBarClass(582, 150, 54, 5);
HrztBar hrztBarCourseDetails(686, 150, 146, 5);
HrztBar hrztBarStudentDetails(882, 150, 156, 5);
Buttonv2 userIcon(1115,85,"image/Profile.png");
Button burgerMenu(1115, 111, "image/BurgerExpand.png");
PasswordBox currentPassword(115,235,"image/Input425x45.png", "Current Password");
PasswordBox newPassword(115, 305, "image/Input425x45.png", "New Password");
PasswordBox confirmPassword(115, 375, "image/Input425x45.png", "Confirm Password");
Button savePasswordButton(440, 490, "image/SaveButton.png");
Button cancelPasswordButton(115, 490, "image/CancelButton.png");
ShowPasswordButton showNewPassButton(115, 430, "Show new password");

// Profile
AvatarProfile avatarProfile(115, 215, "image/Profile.png", "Profile");
InputWithHead seeProfileID(115, 305, "image/Input250x45.png", "ID");
InputWithHead seeProfileSocialID(390, 305, "image/Input250x45.png", "Social ID");
InputWithHead seeProfileFirstName(115, 375, "image/Input250x45.png", "First Name");
InputWithHead seeProfileLastName(390, 375, "image/Input250x45.png", "Last Name");
InputWithHead seeProfileDOB(115, 445, "image/Input250x45.png", "Date of Birth");
GenderSelect seeProfileGender(390, 425, "image/female.png", "image/male.png", "Gender");

// Staff UI
Button profileStaff(1128, 135, "image/ProfileDetail.png");
Button classesButtonSelect(582, 103, "image/ClassButton.png");
Button schoolyearsSelect(415, 103, "image/SchoolyearButton.png");
Button viewingPage(65, 60, "image/ViewingPage.png");
NavigateButton backButton(115, 170, "image/BackButton.png");
NavigateButton rPageButton(495, 604, "image/RightPageButton.png");
NavigateButton lPageButton(115, 604, "image/LeftPageButton.png");

// Button in Schoolyear && semesterpage
InputWithHead inputYear(640, 315, "image/Input425x45.png", "Add year");
InputWithHead inputSearchYear(640, 236, "image/Input425x45.png", "Search year");
Line viewLine(590, 210, 2.0f, 434.0f);
TextBox semesterBox(640, 372, "image/ViewSeme.png", "");
Button addYearButton(1090, 315, "image/AddButton.png");
Button searchYearButton(1090, 236, "image/EnterButton.png");
InputWithHead inputStartDateSem(865, 398, "image/InputDataSeme.png", "Start Date");
InputWithHead inputEndDateSem(865, 469, "image/InputDataSeme.png", "End Date");
Button addSemeButton(1091, 469, "image/AddButton.png");

// Button in class page
InputWithHead inputSearchClass(640, 235, "image/Input425x45.png", "Search Class");
InputWithHead inputClass(640, 305, "image/Input425x45.png", "Class");
Button searchClassButton(1090, 235, "image/EnterButton.png");
Button addClassButton(1090, 305, "image/AddButton.png");

// Button in student of class page
InputWithHead inputSearchStu(640, 235, "image/Input425x45.png", "Search ID");
Button searchStuButton(1090, 235, "image/EnterButton.png");
InputWithHead inputClassFile(640, 305, "image/Input425x45.png", "CSV file path");
Button importClassButton(1090, 305, "image/ImportButton.png");
TextBox numStuBox(640, 360, "image/NumStuBox.png", "Number students: ");
InputWithHead inputStuID(640, 430, "image/Input250x45.png", "Student ID");
InputWithHead inputSocialID(915, 430, "image/Input250x45.png", "Social ID");
InputWithHead inputFirstName(640, 500, "image/Input250x45.png", "First name");
InputWithHead inputLastName(915, 500, "image/Input250x45.png", "Last name");
InputWithHead inputDOB(640, 570, "image/Input250x45.png", "Date of Birth");
GenderSelect genderCheckBox(915, 550, "image/female.png", "image/male.png", "Gender");
Button addStuButton(1065, 570, "image/AddButton.png");

// Profile in student page of class
AvatarProfile avatarStu(115, 215, "image/Profile.png", "Profile of Student");
InputWithHead seeStuID(115, 305, "image/Input250x45.png", "ID");
InputWithHead seeStuSocialID(390, 305, "image/Input250x45.png", "Social ID");
InputWithHead seeStuFirstName(115, 375, "image/Input250x45.png", "First Name");
InputWithHead seeStuLastName(390, 375, "image/Input250x45.png", "Last Name");
InputWithHead seeStuDOB(115, 445, "image/Input250x45.png", "Date of Birth");
GenderSelect seeStuGender(390, 425, "image/female.png", "image/male.png", "Gender");

// Button in course page
//Input
InputWithHead inputSearchCourse(640,230,"image/Input300x45.png", "Search Course");
InputWithHead inputCourseID(640, 300, "image/Input250x45.png", "Course ID");
InputWithHead inputClassIDforCourse(915, 300, "image/Input250x45.png", "Class ID");
InputWithHead inputTeacherName(640, 370, "image/Input525x45.png", "Teacher Name");
InputWithHead inputCourseName(640, 440, "image/Input425x45.png", "Course Name");
InputWithHead inputCredit(1090, 440, "image/Input75x45.png", "Credit");
InputWithHead inputMaxStuInCourse(640, 510, "image/Input125x45.png", "Max Students");
ChooseBoxWithHead inputDoWLeft(790, 510.0f, "image/InputDayLeft.png", "Day of the week", "MON");
ChooseBoxWithHead inputDoWMid1(852, 510.0f, "image/InputDayMid.png", "", "TUE");
ChooseBoxWithHead inputDoWMid2(914, 510.0f, "image/InputDayMid.png", "", "WED");
ChooseBoxWithHead inputDoWMid3(976, 510.0f, "image/InputDayMid.png", "", "THU");
ChooseBoxWithHead inputDoWMid4(1038, 510.0f, "image/InputDayMid.png", "", "FRI");
ChooseBoxWithHead inputDoWRight(1100, 510.0f, "image/InputDayRight.png", "", "SAT");
ChooseBoxWithHead inputSessionLeft(640, 580, "image/InputSessionLeft.png", "Session", "S1 (07:30)");
ChooseBoxWithHead inputSessionMid1(740, 580, "image/InputSessionMid.png", "", "S2 (09:30)");
ChooseBoxWithHead inputSessionMid2(840, 580, "image/InputSessionMid.png", "", "S3 (13:30)");
ChooseBoxWithHead inputSessionRight(940, 580, "image/InputSessionRight.png", "", "S4 (15:30)");
Button searchCourseButton(965, 230, "image/EnterButton.png");
Button addCourseButton(1065, 580, "image/AddButton.png");
// Course features
Button courseDetailSelect(686,103,"image/CourseDetails.png");
Button studentDetailSelect(882,103,"image/StudentDetails.png");
Button importStuButton(1090, 240, "image/ImportButton.png");
Button importScoreButton(1090, 310, "image/ImportButton.png");
Button exportStuButton(665,380,"image/ExportStuButton.png");
Button deleteCourseButton(115, 595, "image/DeleteCourseButton.png");

// Modify Detail course
InputWithHead inputImportStuToCourse(665, 240, "image/Input400x45.png", "Import Student (File path)");
InputWithHead inputImportScore(665, 310, "image/Input400x45.png", "Import Score (File path)");
InputWithHead modifyCourseID(115, 240, "image/Input250x45.png", "Course ID");
InputWithHead modifyClassIDforCourse(390, 240, "image/Input250x45.png", "Class ID");
InputWithHead modifyTeacherName(115, 310, "image/Input525x45.png", "Teacher Name");
InputWithHead modifyCourseName(115, 380, "image/Input425x45.png", "Course Name");
InputWithHead modifyCredit(565, 380, "image/Input75x45.png", "Credit");
ChooseBoxWithHead modifyDoWLeft(265, 450, "image/InputDayLeft.png", "Day of the week", "MON");
ChooseBoxWithHead modifyDoWMid1(327, 450, "image/InputDayMid.png", "", "TUE");
ChooseBoxWithHead modifyDoWMid2(389, 450, "image/InputDayMid.png", "", "WED");
ChooseBoxWithHead modifyDoWMid3(451, 450, "image/InputDayMid.png", "", "THU");
ChooseBoxWithHead modifyDoWMid4(513, 450, "image/InputDayMid.png", "", "FRI");
ChooseBoxWithHead modifyDoWRight(575, 450, "image/InputDayRight.png", "", "SAT");
InputWithHead modifyMaxStuInCourse(115, 450, "image/Input125x45.png", "Max Students");
ChooseBoxWithHead modifySessionLeft(115, 520, "image/InputSessionLeft.png", "Session", "S1 (07:30)");
ChooseBoxWithHead modifySessionMid1(215, 520, "image/InputSessionMid.png", "", "S2 (09:30)");
ChooseBoxWithHead modifySessionMid2(315, 520, "image/InputSessionMid.png", "", "S3 (13:30)");
ChooseBoxWithHead modifySessionRight(415, 520, "image/InputSessionRight.png", "", "S4 (15:30)");
Button saveModifyCourseButton(540, 520, "image/SaveButton.png");

//Scoreboard Page
Button scoreBar(115, 290, "image/ScoreBar.png");
Button scoreSaveButton(1065, 595, "image/SaveButton.png");
Button searchStuCourseButton(930, 220, "image/EnterButton.png");
Button addStuCourseButton(505,220, "image/AddButton.png");
InputWithHead inputSearchStuCourse(705, 220, "image/Input200x45.png", "Search Student ID");
InputWithHead inputAddStuCourse(280, 220, "image/Input200x45.png", "Add student ID");

//Stu account
Button profileStu(207.0f, 185.0f, "image/ProfileStu.png");

// Color Text alert
ColorText passScAlert(115, 545, 20, "Password changed!");
ColorText passFlAlert(115, 545, 20, "Password change failed!");
ColorText notFoundClassAlert(740, 215, 15, "Oops! Class not found");
ColorText foundClassAlert(740, 215, 15, "Class found");
ColorText notFoundCourseAlert(750, 210, 15, "Oops! Course not found");
ColorText foundCourseAlert(750, 210, 15, "Course found");
ColorText notFoundStuAlert(750, 210, 15, "Oops! Student not found");
ColorText foundStuAlert(750, 210, 15, "Student found");
ColorText notFoundYearAlert(750, 210, 15, "Oops! Year not found");
ColorText foundYearAlert(750, 210, 15, "Year found");

// Page control
int prevPage = 0,
    page = 0,
    yearPage = 0,
    classPage = 0,
    stuPage = 0,
    coursePage = 0,
    scorePage = 0;

//Size of data from database
int numStaff = 0,
numCourse = 0,
numClass = 0,
numSchoolYear = 0;

//Data from database
SchoolYear* schoolyearArr = nullptr;
Class* classesArr = nullptr;
Staff* staffArr = nullptr;

// UI arrays
LinkedButton** schoolyearButton = nullptr;
LinkedButton** classesButton = nullptr;

ChooseBoxWithHead** sessionCourseButtonArr = new ChooseBoxWithHead * [4];
ChooseBoxWithHead** doWCourseButtonArr = new ChooseBoxWithHead * [6];
ChooseBoxWithHead** modifySessionCourseButtonArr = new ChooseBoxWithHead * [4];
ChooseBoxWithHead** modifyDoWCourseButtonArr = new ChooseBoxWithHead * [6];

//Currect user
CurrentUser user;

// Finding variable
SearchArrPointerUI* searchArrUI = nullptr;

// Main function
void RunApp() 
{
    classesArr = readClass("database/class", numClass);
    staffArr = readStaffCSV("staff.csv", numStaff);
    schoolyearArr = readSchoolYear("database/schoolyear", numSchoolYear);
    readCourseInSemester("database/course", schoolyearArr, numSchoolYear, classesArr, numClass);

    schoolyearButton = new LinkedButton * [numSchoolYear];
    classesButton = new LinkedButton * [numClass];
    loadUI();
    //printTest(classesArr, numClass, schoolyearArr, numSchoolYear);

    window.setFramerateLimit(60);
    while (window.isOpen()) 
    {
        window.clear();
        background.draw(window);
        switch (page) {
        case 0: // Login Page
        {
            // Read input from mouse and keyboard
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) window.close();
                inputUserBox.isHovering(window);
                inputPassBox.isHovering(window);
                inputPassBox.isHovering(window);

                inputUserBox.isClicked(event, window);
                inputPassBox.isClicked(event, window);
                showPassButton.isClicked(window, event);

                if (loginButton.isClicked(window, event, inputUserBox.text, inputPassBox.text, user.id, user.password)) {
                    if (validateUser()) {
                        if (user.isStaff) page = 10;                        
                        else page = 30;
                        break;
                    }
                    else {
                        clearInput();
                    }
                }
            }
            
            // Draw Element 
            loginBox.draw(window);
            loginButton.draw(window);
            if (showPassButton.active) {
                inputPassBox.drawText(window);
            }
            else {
				inputPassBox.drawStar(window);
			}
            showPassButton.draw(window);
            inputUserBox.draw(window);               
            break;
        }
        case 10: // Staff school year (Page 10 - 29 / Staff)
        {
            handleStaffSchoolYearPage();
            drawStaffSchoolYearPage();
            break;
        }
        case 11: // Classes Page
        {
            handleStaffClassPage();
            drawStaffClassPage();
            break;
        }
        case 13: // Course Page
        {
            handleEventCoursePage();
            drawCoursePage();
            break;
        }
        case 14: // Change password
        {
            handleChangePassword();
            drawChangePassword();
            break;
        }
        case 15: // Staff profile
        {
            handleProfile();
            drawProfile();
            break;
        }
        case 16: // Class detail
        {
            handleStaffClassDetailPage();
            drawStaffClassDetailPage();
            break;
        }
        case 17: // Student detail in class
        {
            handleStuDetailPage();
            drawStuDetailPage();
            break;
        }
        case 18: // Detail course
        {
            handleEventDetailCoursePage();
            drawDetailCoursePage();
            break;
        }
        case 19: // Scoreboard course
		{
			handleEventScoreboardPage();
			drawScoreboardPage();
			break;
		}
        case 30: // Student menu page (Page 30 -> Student)
        {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                if (logOutButton.isClicked(window,event)) {
                    user.isStaff = false;
                    page = 0;
                    user.student = nullptr;
                    clearInput();
                    break;
                }
                passwordChange.isClicked(window, event);
            }
            // Draw
            menu.draw(window);
            profileStu.draw(window);
            passwordChange.draw(window);
            logOutButton.draw(window);
            break;
        }
        case 31: // Stu profile
        {
            break;
        }
        default: 
        {
            break;
        }
        }
        window.display();
    }
    // Console check
    std::cout << "Username: " << user.id << std::endl;
    std::cout << "Password: " << user.password << std::endl;
    return;
}

// Support function
bool validateUser() {
    if (user.id.empty()) return false;
    if (!isNumber(user.id)) return false;
    
    for (int i = 0; i < numStaff; ++i) {
        if (user.id == staffArr[i].staffID && user.password == staffArr[i].password) {
            user.staff = &staffArr[i];
            user.isStaff = true;
            return 1;
        }
    }
    for (int i = 0; i < numClass; ++i) {
        for (int j = 0; j < classesArr[i].numStudent; ++j) {
            if (user.id == classesArr[i].listStudent[j].studentID && user.password == classesArr[i].listStudent[j].password) {
                user.student = &classesArr[i].listStudent[j];
				user.isStaff = false;
				return 1;
			}
        }
    }
    return 0;
}
bool isNumber(const std::string& str) {
    for (char const& c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}
void assignCourseForModify() {
    modifyCourseID.text.setString(schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[user.indexCourse].ID);
    modifyClassIDforCourse.text.setString(schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[user.indexCourse].className);
    modifyTeacherName.text.setString(schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[user.indexCourse].teacher);
    modifyCourseName.text.setString(schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[user.indexCourse].courseName);
    modifyCredit.text.setString(to_string(schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[user.indexCourse].numCredits));
    modifyMaxStuInCourse.text.setString(to_string(schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[user.indexCourse].maxStudents));
    for (int i = 0; i < 6; ++i) {
        if (schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[user.indexCourse].dayOfWeek == modifyDoWCourseButtonArr[i]->text.getString())
            modifyDoWCourseButtonArr[i]->isSelect = true;
        else
            modifyDoWCourseButtonArr[i]->isSelect = false;
    }
    for (int i = 0; i < 4; ++i) {
        if (schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[user.indexCourse].session == modifySessionCourseButtonArr[i]->text.getString())
            modifySessionCourseButtonArr[i]->isSelect = true;
        else
            modifySessionCourseButtonArr[i]->isSelect = false;
    }
}
void clearInput() {
    inputUserBox.text.setString("");
    inputPassBox.text.setString("");
    inputPassBox.star.setString("");
}
void searchYear() {
    string substring = inputSearchYear.text.getString().toAnsiString();
    if (searchArrUI != nullptr) {
        searchArrUI->reset();
		delete searchArrUI;
        searchArrUI = nullptr;
    }
    if (!substring.empty()) {
		searchArrUI = new SearchArrPointerUI(numSchoolYear);
        for (int i = 0; i < numSchoolYear; ++i) {
			string str = schoolyearArr[i].period;
            if (str.find(substring) != string::npos) {
				searchArrUI->nameButton[searchArrUI->curNumButton] = str;
				searchArrUI->idButton[searchArrUI->curNumButton] = i;
				searchArrUI->curNumButton++;
				searchArrUI->active = true;
			}
		}
        if (searchArrUI->active) {
			searchArrUI->loadButtonUI();
			foundYearAlert.setColor(sf::Color(0, 168, 37));
			foundYearAlert.trigger = true;
		}
        else {
			delete searchArrUI;
			searchArrUI = nullptr;
			notFoundYearAlert.setColor(sf::Color::Red);
			notFoundYearAlert.trigger = true;
		}
	}
    yearPage = 0;
    myClock.restart();
    inputSearchYear.text.setString("");
    return;
}
void searchClass() {
    string substring = inputSearchClass.text.getString().toAnsiString();
    if (searchArrUI != nullptr) {
        searchArrUI->reset();
        delete searchArrUI;
        searchArrUI = nullptr;
    }
    if (!substring.empty()) {
        searchArrUI = new SearchArrPointerUI(numClass);
        for (int i = 0; i < numClass; ++i) {
            string str = classesArr[i].classID;
            if (str.find(substring) != string::npos) {
                searchArrUI->nameButton[searchArrUI->curNumButton] = str;
                searchArrUI->idButton[searchArrUI->curNumButton] = i;
                searchArrUI->curNumButton++;
                searchArrUI->active = true;
            }
        }
        if (searchArrUI->active) {
            searchArrUI->loadButtonUI();
            foundClassAlert.setColor(sf::Color(0,168,37));
            foundClassAlert.trigger = true;
        }
        else {
            delete searchArrUI;
            searchArrUI = nullptr;
            notFoundClassAlert.setColor(sf::Color::Red);
            notFoundClassAlert.trigger = true;
        }
    }
    classPage = 0;
    myClock.restart();
    inputSearchClass.text.setString("");
    return;
}
int searchCourse() {
    for (int i = 0; i < schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].numCourses; ++i) 
		if (schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[i].ID == inputSearchCourse.text.getString()) return i;
    return -1;
}

// Load UI
void loadUI() {
    loadUIfromDatabase();
    connectPointerofSessionandDow();
    return;
}
void loadUIfromDatabase() {
    // Create year & semester & course buttons
    float x = 115, y = 210;
    for (int i = 0; i < numSchoolYear; ++i) {
        if (i % 12 == 0 && i != 0) { // Return origin when need new page
            x = 115;
			y = 210;
		}
        else if (i % 6 == 0 && i != 0) { // x,y coordinate of button for each page
            x += 225.0f;
            y = 210;
        }
        schoolyearButton[i] = new LinkedButton(x, y, "image/Button200x45.png", schoolyearArr[i].period);
        y += 65.0f;

        // Create semester button in year
        if (schoolyearArr[i].numSemester != 0) {
            schoolyearButton[i]->linkedButton = new LinkedButton * [schoolyearArr[i].numSemester];
            schoolyearButton[i]->linkedButton = new LinkedButton * [schoolyearArr[i].numSemester];
            float x2 = 640, y2 = 437;
            for (int j = 0; j < schoolyearArr[i].numSemester; j++) {
                schoolyearButton[i]->linkedButton[j] = new LinkedButton(x2, y2, "image/Button200x45.png", "Semester " + to_string(j + 1));
                y2 += 65.0f;

                // Create course buttons in semester
                if (schoolyearArr[i].listSemester[j].numCourses != 0) {
                    schoolyearButton[i]->linkedButton[j]->linkedButton = new LinkedButton * [schoolyearArr[i].listSemester[j].numCourses];
                    float x3 = 115, y3 = 210;
                    for (int k = 0; k < schoolyearArr[i].listSemester[j].numCourses; k++) {
                        if (k % 12 == 0 && k != 0) { // Return origin when need new page
                            x3 = 115;
                            y3 = 210;
                        }
                        else if (k % 6 == 0 && k != 0) { // x,y coordinate of button for each page
                            x3 += 225.0f;
                            y3 = 210;
                        }
                        schoolyearButton[i]->linkedButton[j]->linkedButton[k]
                                = new LinkedButton(x3, y3, "image/Button200x45.png",
                                schoolyearArr[i].listSemester[j].coursesListInSemester[k].ID);
                        y3 += 65.0f;
                        
                        int nSIC = schoolyearArr[i].listSemester[j].coursesListInSemester[k].currStudents;
                        if (nSIC != 0) schoolyearButton[i]->linkedButton[j]->linkedButton[k]->scoreList = new ScoreRow * [nSIC];
                        int xS = 115, yS = 340;
                        for (int l = 0; l < schoolyearArr[i].listSemester[j].coursesListInSemester[k].currStudents; ++l) {
                            if (l % 6 == 0) {
                                xS = 115;
								yS = 340;
							}
                            string noS = to_string(l + 1);
                            string idS = schoolyearArr[i].listSemester[j].coursesListInSemester[k].listStudentInCourse[l]->studentID;
                            string firstS = schoolyearArr[i].listSemester[j].coursesListInSemester[k].listStudentInCourse[l]->firstName;
                            string lastS = schoolyearArr[i].listSemester[j].coursesListInSemester[k].listStudentInCourse[l]->lastName;
                            int nC = schoolyearArr[i].listSemester[j].coursesListInSemester[k].listStudentInCourse[l]->numCourse;
                            string idCourse = schoolyearArr[i].listSemester[j].coursesListInSemester[k].ID;
                            string totalS = "_";
                            string finalS = "_";
                            string midS = "_";
                            string otherS = "_";
                            for (int r = 0; r < nC; ++r) {
								if (schoolyearArr[i].listSemester[j].coursesListInSemester[k].listStudentInCourse[l]->scoreList[i].courseID == idCourse) {
                                    totalS = to_string(schoolyearArr[i].listSemester[j].coursesListInSemester[k].listStudentInCourse[l]->scoreList[i].total);
                                    finalS = to_string(schoolyearArr[i].listSemester[j].coursesListInSemester[k].listStudentInCourse[l]->scoreList[i].final);
                                    midS = to_string(schoolyearArr[i].listSemester[j].coursesListInSemester[k].listStudentInCourse[l]->scoreList[i].mid);
                                    otherS = to_string(schoolyearArr[i].listSemester[j].coursesListInSemester[k].listStudentInCourse[l]->scoreList[i].other);
                                }
							}
                            schoolyearButton[i]->linkedButton[j]->linkedButton[k]->scoreList[l] = new ScoreRow(115, 340, "image/DeleteStu.png",
                                noS, idS, firstS, lastS, totalS, finalS, midS, otherS);
                            yS += 50;
                        }
                    }
                }
            }
        }
    }
    
    // Create button for all classes have existed
    x = 115; y = 210;
    for (int i = 0; i < numClass; ++i) {
        if (i % 12 == 0 && i != 0) { // Return origin when need new page
            x = 115;
            y = 210;
        }
        else if (i % 6 == 0 && i != 0) { // x,y coordinate of button for each page
            x += 225.0f;
            y = 210;
        }
        classesButton[i] = new LinkedButton(x, y, "image/Button200x45.png", classesArr[i].classID);
        y += 65.0f;
	}

    // Create button for all students of all classes
    
    for (int i = 0; i < numClass; i++) {
        x = 115; y = 210;
        int numStuClass = classesArr[i].numStudent;
        if (numStuClass != 0) {
            classesButton[i]->linkedButton = new LinkedButton * [numStuClass];
            for (int j = 0; j < numStuClass; j++) {
                if (j % 12 == 0 && j != 0) { // Return origin when need new page
                    x = 115;
                    y = 210;
                }
                else if (j % 6 == 0 && j != 0) { // x,y coordinate of button for each page
                    x += 225.0f;
                    y = 210;
                }
                classesButton[i]->linkedButton[j] = new LinkedButton(x, y, "image/Button200x45.png", classesArr[i].listStudent[j].studentID);
                y += 65.0f;
            }
        }
    }

}
void connectPointerofSessionandDow() {
    // Array of pointer to session input course
    sessionCourseButtonArr[0] = &inputSessionLeft;
    sessionCourseButtonArr[1] = &inputSessionMid1;
    sessionCourseButtonArr[2] = &inputSessionMid2;
    sessionCourseButtonArr[3] = &inputSessionRight;
    // Array of pointer to day of week input course
    doWCourseButtonArr[0] = &inputDoWLeft;
    doWCourseButtonArr[1] = &inputDoWMid1;
    doWCourseButtonArr[2] = &inputDoWMid2;
    doWCourseButtonArr[3] = &inputDoWMid3;
    doWCourseButtonArr[4] = &inputDoWMid4;
    doWCourseButtonArr[5] = &inputDoWRight;
    // Array of pointer to session modify course
    modifySessionCourseButtonArr[0] = &modifySessionLeft;
    modifySessionCourseButtonArr[1] = &modifySessionMid1;
    modifySessionCourseButtonArr[2] = &modifySessionMid2;
    modifySessionCourseButtonArr[3] = &modifySessionRight;
    // Array of pointer to day of week modify course
    modifyDoWCourseButtonArr[0] = &modifyDoWLeft;
    modifyDoWCourseButtonArr[1] = &modifyDoWMid1;
    modifyDoWCourseButtonArr[2] = &modifyDoWMid2;
    modifyDoWCourseButtonArr[3] = &modifyDoWMid3;
    modifyDoWCourseButtonArr[4] = &modifyDoWMid4;
    modifyDoWCourseButtonArr[5] = &modifyDoWRight;
}

// Handle and draw in every page
void handleChangePassword() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        
        schoolyearsSelect.isHovering(window);
        if (schoolyearsSelect.isClicked(window, event)) {
            page = 10;
            break;
        }

        classesButtonSelect.isHovering(window);
        if (classesButtonSelect.isClicked(window, event)) {
            page = 11;
            break;
        }

        if (userIcon.isClicked(window, event)) {}
        if (userIcon.isSelect) {
            profileStaff.isHovering(window);
            logOutButton.isHovering(window);
            passwordChange.isHovering(window);
            if (profileStaff.isClicked(window, event)) {
                prevPage = page;
                page = 15;
                break;
            }
            if (logOutButton.isClicked(window, event)) {
                user.isStaff = false;
                page = 0;
                user.staff = nullptr;
                clearInput();
                break;
            }
        }

        currentPassword.isHovering(window);
        currentPassword.isClicked(event, window);
        
        newPassword.isHovering(window);
        newPassword.isClicked(event, window);

        confirmPassword.isHovering(window);
        confirmPassword.isClicked(event, window);

        showNewPassButton.isClicked(window,event);

        if (savePasswordButton.isClicked(window, event)) {
            if (currentPassword.text.getString() == user.staff->password 
                && newPassword.text.getString() == confirmPassword.text.getString()) {
					user.staff->password = newPassword.text.getString();
                    passScAlert.trigger = true;
			}
            else {
                passFlAlert.trigger = true;
            }
            currentPassword.text.setString("");
            newPassword.text.setString("");
            confirmPassword.text.setString("");
            myClock.restart();
            break;
        }

        if (cancelPasswordButton.isClicked(window, event)) {
			page = prevPage;
			break;
		}
    }
    return;
}
void drawChangePassword() {
    viewingPage.draw(window);
    userIcon.draw(window);
    if (userIcon.isSelect) {
        burgerMenu.draw(window);
        profileStaff.draw(window);
        logOutButton.draw(window);
        passwordChange.draw(window);
    }
    if (classesButtonSelect.isHover) hrztBarClass.draw(window);
    if (schoolyearsSelect.isHover) hrztBarYear.draw(window);
    schoolyearsSelect.draw(window);
    classesButtonSelect.draw(window);
    userIcon.draw(window);
    currentPassword.drawStar(window);
    if (showNewPassButton.active) {
		newPassword.drawText(window);
		confirmPassword.drawText(window);
	}
	else {
    	newPassword.drawStar(window);
        confirmPassword.drawStar(window);
    } 
    cancelPasswordButton.draw(window);
    savePasswordButton.draw(window);
    showNewPassButton.draw(window);
    if (passScAlert.trigger) {
        if (myClock.getElapsedTime().asSeconds() > 3) {
            passScAlert.trigger = false;
            myClock.restart();
		}
        passScAlert.setColor(sf::Color(0,168,37));
        passScAlert.draw(window);
    }
    if (passFlAlert.trigger) {
        if (myClock.getElapsedTime().asSeconds() > 3) {
            passFlAlert.trigger = false;
            myClock.restart();
        }
        passFlAlert.setColor(sf::Color(255, 0, 0));
        passFlAlert.draw(window);
    }
}

void handleProfile() {
    if (user.isStaff) {
		seeProfileID.text.setString(user.staff->staffID);
        seeProfileSocialID.text.setString(user.staff->socialID);
		seeProfileFirstName.text.setString(user.staff->firstName);
		seeProfileLastName.text.setString(user.staff->lastName);
		seeProfileDOB.text.setString(user.staff->dob);
        if (user.staff->gender) seeProfileGender.female = true;
		else seeProfileGender.female = false;
    }
    else {
        seeProfileID.text.setString(user.student->studentID);
		seeProfileSocialID.text.setString(user.student->socialID);
		seeProfileFirstName.text.setString(user.student->firstName);
		seeProfileLastName.text.setString(user.student->lastName);
		seeProfileDOB.text.setString(user.student->dob);
        if (user.student->femaleGender) seeProfileGender.female = true;
        else seeProfileGender.female = false;
    }
    
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        
        backButton.isHovering(window);
        if (backButton.isClicked(window, event)) {
			page = prevPage;
            prevPage = page;
			break;
		}
        
        schoolyearsSelect.isHovering(window);
        classesButtonSelect.isHovering(window);

        if (userIcon.isClicked(window, event)) {}
        if (userIcon.isSelect) {
            profileStaff.isHovering(window);
            logOutButton.isHovering(window);
            passwordChange.isHovering(window);
            if (profileStaff.isClicked(window, event)) {
                prevPage = page;
                page = 15;
                break;
            }
            if (logOutButton.isClicked(window, event)) {
                user.isStaff = false;
                page = 0;
                prevPage = page;
                user.staff = nullptr;
                clearInput();
                break;
            }
            if (passwordChange.isClicked(window, event)) {
                prevPage = page;
				page = 14;
				break;
            }
        }
        if (schoolyearsSelect.isClicked(window, event)) {
            page = 10;
            prevPage = page;
            break;
        }
        if (classesButtonSelect.isClicked(window, event)) {
            page = 11;
            prevPage = page;
            break;
        }
    }
}
void drawProfile() {
    viewingPage.draw(window);
    userIcon.draw(window);
    if (userIcon.isSelect) {
        burgerMenu.draw(window);
        profileStaff.draw(window);
        logOutButton.draw(window);
        passwordChange.draw(window);
    }
    if (classesButtonSelect.isHover) hrztBarClass.draw(window);
    if (schoolyearsSelect.isHover) hrztBarYear.draw(window);
    classesButtonSelect.draw(window);
    schoolyearsSelect.draw(window);
    backButton.draw(window);

    avatarProfile.draw(window);
    seeProfileID.draw(window);
    seeProfileSocialID.draw(window);
    seeProfileFirstName.draw(window);
    seeProfileLastName.draw(window);
    seeProfileDOB.draw(window);
    seeProfileGender.draw(window);

    //seeProfile.draw(window);
    //profileText->drawStaff(window);
    return;
}

void handleStaffSchoolYearPage() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        
        schoolyearsSelect.isHovering(window);
        if (schoolyearsSelect.isClicked(window, event)) {
            page = 10;
            break;
        }
        
        classesButtonSelect.isHovering(window);
        if (classesButtonSelect.isClicked(window, event)) {
            page = 11;
            break;
        }

        if (userIcon.isClicked(window, event)) {}
        if (userIcon.isSelect) {
            profileStaff.isHovering(window);
            logOutButton.isHovering(window);
            passwordChange.isHovering(window);
            if (profileStaff.isClicked(window, event)) {
                prevPage = page;
                page = 15;
                break;
            }
            if (logOutButton.isClicked(window, event)) {
                user.isStaff = false;
                page = 0;
                user.staff = nullptr;
                clearInput();
                break;
            }
            if (passwordChange.isClicked(window, event)) {
                prevPage = 10;
                page = 14;
				break;
            }
        }
        
        inputYear.isHovering(window);
        inputYear.isClicked(event, window);
        if (addYearButton.isClicked(window, event)) {
            schoolyearArr = loadAddSchoolyear(schoolyearArr, numSchoolYear);
            schoolyearArr[numSchoolYear - 1].period = inputYear.text.getString();
            schoolyearButton = loadAddYearButton(schoolyearArr, schoolyearButton, numSchoolYear);
            inputYear.text.setString("");
        }

        inputSearchYear.isHovering(window);
        inputSearchYear.isClicked(event, window);
        if (searchYearButton.isClicked(window, event)) {
            searchYear();
            break;
        }

        lPageButton.isHovering(window);
        if (lPageButton.isClicked(window, event)) {
            if (yearPage > 0) yearPage--;
        }
        rPageButton.isHovering(window);
        if (rPageButton.isClicked(window, event)) {
            int tmp1;
            if (searchArrUI == nullptr) {
                if (numSchoolYear % 12 != 0) tmp1 = numSchoolYear / 12;
                else tmp1 = numSchoolYear / 12 - 1;
                if (yearPage < tmp1) yearPage++;
            }
            else {
                if (searchArrUI->curNumButton % 12 != 0) tmp1 = searchArrUI->curNumButton / 12;
                else tmp1 = searchArrUI->curNumButton / 12 - 1;
                if (yearPage < tmp1) yearPage++;
            }
        }

        if (searchArrUI == nullptr) {
            for (int i = yearPage * 12; i < (yearPage + 1) * 12 && i < numSchoolYear; ++i)
                schoolyearButton[i]->isHovering(window);
            for (int i = yearPage * 12; i < (yearPage + 1) * 12 && i < numSchoolYear; ++i)
                if (schoolyearButton[i]->isClicked(window, event)) {
                    user.indexSchoolyear = i;
                    break;
                }
        }
        else {
            for (int i = yearPage * 12; i < (yearPage + 1) * 12 && i < searchArrUI->curNumButton; ++i)
				schoolyearButton[i]->isHovering(window);
			for (int i = yearPage * 12; i < (yearPage + 1) * 12 && i < searchArrUI->curNumButton; ++i)
                if (schoolyearButton[i]->isClicked(window, event)) {
					user.indexSchoolyear = searchArrUI->idButton[i];
					break;
				}
        }
        
        if (user.indexSchoolyear != -1) {
            int size = schoolyearArr[user.indexSchoolyear].numSemester;
            for (int i = 0; i < size; ++i)
                schoolyearButton[user.indexSchoolyear]->linkedButton[i]->isHovering(window);
            for (int i = 0; i < size; ++i)
                if (schoolyearButton[user.indexSchoolyear]->linkedButton[i]->isClicked(window, event)) {
                    user.indexSemester = i;
                    prevPage = page;
                    page = 13;
                    break;
                }
        }
        // Check if numseme < 3 to display input seme 
        if (user.indexSemester != -1 && schoolyearArr[user.indexSchoolyear].numSemester < 3) {
            inputStartDateSem.isHovering(window);
            inputEndDateSem.isHovering(window);
            inputStartDateSem.isClicked(event, window);
            inputEndDateSem.isClicked(event, window);
            // Add seme to year
            if (addSemeButton.isClicked(window, event)) {
                // Create new list of semester with size + 1
                schoolyearArr[user.indexSchoolyear].listSemester = loadAddSemester(schoolyearArr[user.indexSchoolyear].listSemester, schoolyearArr[user.indexSchoolyear].numSemester);
                // Add data to new semester
                schoolyearArr[user.indexSchoolyear].listSemester[schoolyearArr[user.indexSchoolyear].numSemester - 1].startDate = inputEndDateSem.text.getString();
                schoolyearArr[user.indexSchoolyear].listSemester[schoolyearArr[user.indexSchoolyear].numSemester - 1].endDate = inputEndDateSem.text.getString();
                // Create new button for semester
                schoolyearButton[user.indexSchoolyear]->linkedButton = loadAddSemeButton(schoolyearArr[user.indexSchoolyear].listSemester, schoolyearButton[user.indexSchoolyear]->linkedButton, schoolyearArr[user.indexSchoolyear].numSemester);
                inputStartDateSem.text.setString("");
                inputEndDateSem.text.setString("");
            }
        }
    }
    return;
}
void drawStaffSchoolYearPage() {
    viewingPage.draw(window);
    userIcon.draw(window);
    if (userIcon.isSelect) {
        burgerMenu.draw(window);
        profileStaff.draw(window);
        logOutButton.draw(window);
        passwordChange.draw(window);
    }
    if (classesButtonSelect.isHover) hrztBarClass.draw(window);
    else hrztBarYear.draw(window);
    classesButtonSelect.draw(window);
    schoolyearsSelect.draw(window);
    viewLine.draw(window);
    lPageButton.draw(window);
    rPageButton.draw(window);
    inputYear.draw(window);
    inputSearchYear.draw(window);
    addYearButton.draw(window);
    searchYearButton.draw(window);

    if (searchArrUI == nullptr) {
        for (int i = yearPage * 12; i < (yearPage + 1) * 12 && i < numSchoolYear; ++i)
            schoolyearButton[i]->draw(window);
    }
    else {
		for (int i = yearPage * 12; i < (yearPage + 1) * 12 && i < searchArrUI->curNumButton; ++i)
            searchArrUI->linkedButton[i]->draw(window);
	}
    
    if (foundYearAlert.trigger) {
        if (myClock.getElapsedTime().asSeconds() > 3) {
			foundYearAlert.trigger = false;
			myClock.restart();
		}
		foundYearAlert.draw(window);
	}
    if (notFoundYearAlert.trigger) {
        if (myClock.getElapsedTime().asSeconds() > 3) {
            notFoundYearAlert.trigger = false;
            myClock.restart();
        }
        notFoundYearAlert.draw(window);
    }

    if (user.indexSchoolyear != -1) {
        semesterBox.text.setString(schoolyearArr[user.indexSchoolyear].period);
        semesterBox.draw(window);
        int size = schoolyearArr[user.indexSchoolyear].numSemester;
        for (int i = 0; i < size; ++i)
            schoolyearButton[user.indexSchoolyear]->linkedButton[i]->draw(window);
    }
    if (user.indexSemester != -1 && schoolyearArr[user.indexSchoolyear].numSemester < 3) {
        inputStartDateSem.draw(window);
        inputEndDateSem.draw(window);
        addSemeButton.draw(window);
    }
}

// Page 13
void handleEventCoursePage() {
    int size = schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].numCourses;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        schoolyearsSelect.isHovering(window);
        if (schoolyearsSelect.isClicked(window, event)) {
            page = 10;
            break;
        }

        classesButtonSelect.isHovering(window);
        if (classesButtonSelect.isClicked(window, event)) {
            page = 11;
            break;
        }

        if (userIcon.isClicked(window, event)) {}
        if (userIcon.isSelect) {
            profileStaff.isHovering(window);
            logOutButton.isHovering(window);
            passwordChange.isHovering(window);
            if (profileStaff.isClicked(window, event)) {
                prevPage = page;
                page = 15;
                break;
            }
            if (logOutButton.isClicked(window, event)) {
                user.isStaff = false;
                page = 0;
                user.staff = nullptr;
                clearInput();
                break;
            }
            if (passwordChange.isClicked(window, event)) {}
        }

        backButton.isHovering(window);
        if (backButton.isClicked(window, event)) {
            page = 10;
            break;
        }

        // Hovering control
        inputSearchCourse.isHovering(window);
        inputCourseID.isHovering(window);
        inputClassIDforCourse.isHovering(window);
        inputTeacherName.isHovering(window);
        inputCourseName.isHovering(window);
        inputCredit.isHovering(window);
        inputMaxStuInCourse.isHovering(window);
        inputTeacherName.isHovering(window);
        for (int i = 0; i < 6; ++i)
            doWCourseButtonArr[i]->isHovering(window);
        for (int i = 0; i < 4; ++i)
            sessionCourseButtonArr[i]->isHovering(window);

        // Back & subPage control
        rPageButton.isHovering(window);
        lPageButton.isHovering(window);
        if (rPageButton.isClicked(window, event)) {
            // If page is not the last page
            if (coursePage < size / 12) coursePage++;
        }
        if (lPageButton.isClicked(window, event)) {
            // If page is not the first page
            if (coursePage > 0) coursePage--;
        }

        // Input course control
        inputSearchCourse.isClicked(event, window);
        inputCourseID.isClicked(event, window);
        inputClassIDforCourse.isClicked(event, window);
        inputCourseName.isClicked(event, window);
        inputCredit.isClicked(event, window);
        inputMaxStuInCourse.isClicked(event, window);
        inputTeacherName.isClicked(event, window);

        // Input day of week control
        for (int i = 0; i < 6; ++i) {
            if (doWCourseButtonArr[i]->isClicked(window, event)) {
                for (int j = 0; j < 6; ++j) {
                    if (j != i) doWCourseButtonArr[j]->isSelect = false;
                }
            }
        }
        // Input session control
        for (int i = 0; i < 4; ++i) {
            if (sessionCourseButtonArr[i]->isClicked(window, event)) {
                for (int j = 0; j < 4; ++j) {
                    if (j != i) sessionCourseButtonArr[j]->isSelect = false;
                }
            }
        }

        // If search course 
        if (searchCourseButton.isClicked(window, event)) {
            int index = searchCourse();
            if (index != -1) {
                user.indexCourse = index;
                notFoundCourseAlert.trigger = false;
                page = 18;
            }
            else {
                notFoundCourseAlert.trigger = true;
                notFoundCourseAlert.setColor(sf::Color(255, 0, 0));
                myClock.restart();
            }
            inputSearchCourse.text.setString("");
            break;
        }

        // Add course control 
        if (addCourseButton.isClicked(window, event)) {
            // Load data into variable
            schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester = loadAddCourse();
            // Load data for UI
            schoolyearButton[user.indexSchoolyear]->linkedButton[user.indexSemester]->linkedButton = loadAddCourseButton();
        }

        // Course button control base on course page
        for (int i = coursePage * 12; i < (coursePage + 1) * 12 && i < size; ++i)
            schoolyearButton[user.indexSchoolyear]->linkedButton[user.indexSemester]->linkedButton[i]->isHovering(window);
        for (int i = coursePage * 12; i < (coursePage + 1) * 12 && i < size; ++i) {
            if (schoolyearButton[user.indexSchoolyear]->linkedButton[user.indexSemester]->linkedButton[i]->isClicked(window, event)) {
                page = 18;
                user.indexCourse = i;
                assignCourseForModify();
                break;
            }
        }
    }
}
void drawCoursePage() {
    int size = schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].numCourses;
    // Draw layout
    viewingPage.draw(window);
    userIcon.draw(window);
    if (userIcon.isSelect) {
        burgerMenu.draw(window);
        profileStaff.draw(window);
        logOutButton.draw(window);
        passwordChange.draw(window);
    }
    if (classesButtonSelect.isHover) hrztBarClass.draw(window);
    else hrztBarYear.draw(window);
    classesButtonSelect.draw(window);
    schoolyearsSelect.draw(window);
    viewLine.draw(window);
    lPageButton.draw(window);
    rPageButton.draw(window);
    backButton.draw(window);

    if (notFoundCourseAlert.trigger) {
        if (myClock.getElapsedTime().asSeconds() > 3) {
			notFoundCourseAlert.trigger = false;
			myClock.restart();
		}
		notFoundCourseAlert.draw(window);
    }

    // Draw input course
    inputSearchCourse.draw(window);
    inputCourseID.draw(window);
    inputClassIDforCourse.draw(window);
    inputTeacherName.draw(window);
    inputCourseName.draw(window);
    inputCredit.draw(window);
    inputMaxStuInCourse.draw(window);
    addCourseButton.draw(window);
    searchCourseButton.draw(window);
    for (int i = 0; i < 6; ++i)
		doWCourseButtonArr[i]->draw(window);
    for (int i = 0; i < 4; ++i)
        sessionCourseButtonArr[i]->draw(window);


    // Draw course button base on course page
    int i = coursePage * 12;
    for (i; i < (coursePage + 1) * 12 && i < size; ++i)
        schoolyearButton[user.indexSchoolyear]->linkedButton[user.indexSemester]->linkedButton[i]->draw(window);
}

// Page 18
void handleEventDetailCoursePage() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
        
        schoolyearsSelect.isHovering(window);
        if (schoolyearsSelect.isClicked(window, event)) {
            page = 10;
            break;
        }

        classesButtonSelect.isHovering(window);
        if (classesButtonSelect.isClicked(window, event)) {
            page = 11;
            break;
        }

        userIcon.isClicked(window, event);
        if (userIcon.isSelect) {
            profileStaff.isHovering(window);
            logOutButton.isHovering(window);
            passwordChange.isHovering(window);
            if (profileStaff.isClicked(window, event)) {
                prevPage = page;
                page = 15;
                break;
            }
            if (logOutButton.isClicked(window, event)) {
                user.isStaff = false;
                page = 0;
                user.staff = nullptr;
                clearInput();
                break;
            }
            if (passwordChange.isClicked(window, event)) {}
        }
        
        courseDetailSelect.isHovering(window);
        if (courseDetailSelect.isClicked(window, event)) {}

        studentDetailSelect.isHovering(window);
        if (studentDetailSelect.isClicked(window, event)) {
            page = 19;
            prevPage = page;
			break;
        }

        // Hovering control
        modifyCourseID.isHovering(window);
        modifyClassIDforCourse.isHovering(window);
        modifyTeacherName.isHovering(window);
        modifyCourseName.isHovering(window);
        modifyCredit.isHovering(window);
        modifyMaxStuInCourse.isHovering(window);
        backButton.isHovering(window);
        inputImportScore.isHovering(window);
        inputImportStuToCourse.isHovering(window);
        for (int i = 0; i < 6; ++i)
            modifyDoWCourseButtonArr[i]->isHovering(window);
        for (int i = 0; i < 4; ++i)
            modifySessionCourseButtonArr[i]->isHovering(window);

        if (backButton.isClicked(window, event)) {
            page = 13;
            break;
        }

        // Modify course control
        inputImportScore.isClicked(event, window);
        inputImportStuToCourse.isClicked(event, window);
        modifyCourseID.isClicked(event, window);
        modifyClassIDforCourse.isClicked(event, window);
        modifyTeacherName.isClicked(event, window);
        modifyCourseName.isClicked(event, window);
        modifyCredit.isClicked(event, window);
        modifyMaxStuInCourse.isClicked(event, window);
        for (int i = 0; i < 6; ++i) {
            if (modifyDoWCourseButtonArr[i]->isClicked(window, event)) {
                for (int j = 0; j < 6; ++j) {
                    if (j != i) modifyDoWCourseButtonArr[j]->isSelect = false;
                }
            }
        }
        for (int i = 0; i < 4; ++i) {
            if (modifySessionCourseButtonArr[i]->isClicked(window, event)) {
                for (int j = 0; j < 4; ++j) {
                    if (j != i) modifySessionCourseButtonArr[j]->isSelect = false;
                }
            }
        }
        if (saveModifyCourseButton.isClicked(window, event)) {
            // Save input into data
            schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[user.indexCourse].ID = modifyCourseID.text.getString().toAnsiString();
			schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[user.indexCourse].className = modifyClassIDforCourse.text.getString().toAnsiString();
			schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[user.indexCourse].teacher = modifyTeacherName.text.getString().toAnsiString();
			schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[user.indexCourse].courseName = modifyCourseName.text.getString().toAnsiString();
			schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[user.indexCourse].numCredits = stoi(modifyCredit.text.getString().toAnsiString());
			schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[user.indexCourse].maxStudents = stoi(modifyMaxStuInCourse.text.getString().toAnsiString());
			for (int i = 0; i < 6; ++i) {
				if (modifyDoWCourseButtonArr[i]->isSelect) {
					schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[user.indexCourse].dayOfWeek = modifyDoWCourseButtonArr[i]->text.getString().toAnsiString();
					break;
				}
			}
            for (int i = 0; i < 4; ++i) {
                if (modifySessionCourseButtonArr[i]->isSelect) {
                    schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[user.indexCourse].session = modifySessionCourseButtonArr[i]->text.getString().toAnsiString();
                    break;
                }
            }

            // Save input into UI
            assignCourseForModify();
            // Update UI for course ID outside
            schoolyearButton[user.indexSchoolyear]->linkedButton[user.indexSemester]->linkedButton[user.indexCourse]->text.setString(modifyCourseID.text.getString());
        }

	}
}
void drawDetailCoursePage() {
    viewingPage.draw(window);
    schoolyearsSelect.draw(window);
    classesButtonSelect.draw(window);
    userIcon.draw(window);
    if (userIcon.isSelect) {
        burgerMenu.draw(window);
        profileStaff.draw(window);
        logOutButton.draw(window);
        passwordChange.draw(window);
    }
    if (classesButtonSelect.isHover) hrztBarClass.draw(window);
    else if (schoolyearsSelect.isHover) hrztBarYear.draw(window);
    else if (studentDetailSelect.isHover) hrztBarStudentDetails.draw(window);
	else hrztBarCourseDetails.draw(window);
    backButton.draw(window);
    
    courseDetailSelect.draw(window);
    studentDetailSelect.draw(window);
    exportStuButton.draw(window);
    importScoreButton.draw(window);
    importStuButton.draw(window);
    deleteCourseButton.draw(window);
    inputImportScore.draw(window);
    inputImportStuToCourse.draw(window);

    modifyCourseID.draw(window);
    modifyClassIDforCourse.draw(window);
    modifyTeacherName.draw(window);
	modifyCourseName.draw(window);
    modifyCredit.draw(window);
	modifyMaxStuInCourse.draw(window);
    saveModifyCourseButton.draw(window);
    for (int i = 0; i < 6; ++i)
        modifyDoWCourseButtonArr[i]->draw(window);
    for (int i = 0; i < 4; ++i)
        modifySessionCourseButtonArr[i]->draw(window);

    return;
}

void handleStaffClassPage() {
    while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) window.close();
		
		schoolyearsSelect.isHovering(window);
        if (schoolyearsSelect.isClicked(window, event)) {
			page = 10;
			break;
		}

		classesButtonSelect.isHovering(window);
        if (classesButtonSelect.isClicked(window, event)) {
			page = 11;
			break;
		}

		userIcon.isClicked(window, event);
        if (userIcon.isSelect) {
			profileStaff.isHovering(window);
			logOutButton.isHovering(window);
			passwordChange.isHovering(window);
            if (profileStaff.isClicked(window, event)) {
                prevPage = page;
				page = 15;
				break;
			}
            if (logOutButton.isClicked(window, event)) {
				user.isStaff = false;
				page = 0;
				user.staff = nullptr;
				clearInput();
				break;
			}
			if (passwordChange.isClicked(window, event)) {}
		}

		lPageButton.isHovering(window);
		rPageButton.isHovering(window);
        if (rPageButton.isClicked(window, event)) {
            int tmp1;
            if (searchArrUI == nullptr) {
                if (numClass % 12 != 0) tmp1 = numClass / 12;
			    else tmp1 = numClass / 12 - 1;
                if (classPage < tmp1) classPage++;
            }
            else {
                if (searchArrUI->curNumButton % 12 != 0) tmp1 = searchArrUI->curNumButton / 12;
				else tmp1 = searchArrUI->curNumButton / 12 - 1;
				if (classPage < tmp1) classPage++;
            }
		}
        if (lPageButton.isClicked(window, event)) {
			// If page is not the first page
			if (classPage > 0) classPage--;
		}

        if (searchArrUI == nullptr) {
            for (int i = classPage * 12; i < (classPage + 1) * 12 && i < numClass; ++i) {
                classesButton[i]->isHovering(window);
            }
            for (int i = classPage * 12; i < (classPage + 1) * 12 && i < numClass; ++i) {
                if (classesButton[i]->isClicked(window, event)) {
                    user.indexClass = i;
                    prevPage = page;
                    page = 16;
                    stuPage = 0;
                    numStuBox.text.setString("Number students: " + to_string(classesArr[i].numStudent));
                    break;
                }
            }
        }
        else {
            for (int i = classPage * 12; (classPage + 1) * 12 && i < searchArrUI->curNumButton; ++i) {
                searchArrUI->linkedButton[i]->isHovering(window);
			}
            for (int i = classPage * 12; (classPage + 1) * 12 && i < searchArrUI->curNumButton; ++i) {
                if (searchArrUI->linkedButton[i]->isClicked(window, event)) {
					user.indexClass = searchArrUI->idButton[i];
					prevPage = page;
					page = 16;
					stuPage = 0;
					numStuBox.text.setString("Number students: " + to_string(classesArr[searchArrUI->idButton[i]].numStudent));
					break;
				}
			}
        }
        inputClass.isHovering(window);
        inputClass.isClicked(event, window);
        if (addClassButton.isClicked(window, event)) {
            classesArr = loadAddClass();
            classesArr[numClass - 1].classID = inputClass.text.getString();
            classesButton = loadAddClassButton();
            inputClass.text.setString("");
        }

        inputSearchClass.isHovering(window);
        inputSearchClass.isClicked(event, window);
        if (searchClassButton.isClicked(window, event)) {
            searchClass();
            break;
        }
    }
}
void drawStaffClassPage() {
    viewingPage.draw(window);
    viewLine.draw(window);
	schoolyearsSelect.draw(window);
	classesButtonSelect.draw(window);
	userIcon.draw(window);
    if (userIcon.isSelect) {
		burgerMenu.draw(window);
		profileStaff.draw(window);
		logOutButton.draw(window);
		passwordChange.draw(window);
	}
    if (schoolyearsSelect.isHover) hrztBarYear.draw(window);
    else hrztBarClass.draw(window);
    inputSearchClass.draw(window);
    searchClassButton.draw(window);
    inputClass.draw(window);
    addClassButton.draw(window);
	lPageButton.draw(window);
	rPageButton.draw(window);
    
    if (notFoundClassAlert.trigger) {
        if (myClock.getElapsedTime().asSeconds() > 3) {
            notFoundClassAlert.trigger = false;
            myClock.restart();
        }
        notFoundClassAlert.draw(window);
    }
    if (foundClassAlert.trigger) {
        if (myClock.getElapsedTime().asSeconds() > 3) {
			foundClassAlert.trigger = false;
			myClock.restart();
		}
		foundClassAlert.draw(window);
	}

	// Draw class button base on class page
    if (searchArrUI == nullptr) {
        for (int i = classPage * 12; i < (classPage + 1) * 12 && i < numClass; ++i)
            classesButton[i]->draw(window);
    }
    else {
        for (int i = classPage * 12; i < (classPage + 1) * 12 && i < searchArrUI->curNumButton; ++i)
            searchArrUI->linkedButton[i]->draw(window);
    }

}

// Page 16
void handleStaffClassDetailPage() { 
    int size = classesArr[user.indexClass].numStudent;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        backButton.isHovering(window);
        if (backButton.isClicked(window, event)) {
            page = 11;
            break;
        }

        schoolyearsSelect.isHovering(window);
        if (schoolyearsSelect.isClicked(window, event)) {
            page = 10;
            break;
        }

        classesButtonSelect.isHovering(window);
        if (classesButtonSelect.isClicked(window, event)) {
            page = 11;
            break;
        }

        userIcon.isClicked(window, event);
        if (userIcon.isSelect) {
            profileStaff.isHovering(window);
            logOutButton.isHovering(window);
            passwordChange.isHovering(window);
            if (profileStaff.isClicked(window, event)) {
                prevPage = 16;
                page = 15;
                break;
            }
            if (logOutButton.isClicked(window, event)) {
                user.isStaff = false;
                page = 0;
                user.staff = nullptr;
                clearInput();
                break;
            }
            if (passwordChange.isClicked(window, event)) {
                prevPage = 16;
                page = 14;
                break;
            }
        }

        rPageButton.isHovering(window);
        lPageButton.isHovering(window);
        if (rPageButton.isClicked(window, event)) {
            // If page is not the last page
            if (stuPage < classesArr[user.indexClass].numStudent / 12) stuPage++;
        }
        if (lPageButton.isClicked(window, event)) {
            // If page is not the first page
            if (stuPage > 0) stuPage--;
        }

        inputSearchStu.isHovering(window);
        inputSearchStu.isClicked(event, window);
        if (searchStuButton.isClicked(window, event)) { }
        
        inputClassFile.isHovering(window);
        inputClassFile.isClicked(event, window);
        if (importClassButton.isClicked(window, event)) {
            string path = inputClassFile.text.getString().toAnsiString();
            int numIc = 0;
            if (readCSVStuToClass(path, classesArr[user.indexClass], numIc)) {
                classesButton[user.indexClass]->linkedButton = loadAddCSVStuToClassButton(numIc);
                inputClassFile.text.setString("");
                numStuBox.text.setString("Number students: " + to_string(classesArr[user.indexClass].numStudent));
            }
            else {}
            break;
        }

        inputStuID.isHovering(window);
        inputStuID.isClicked(event, window);

        inputSocialID.isHovering(window);
        inputSocialID.isClicked(event, window);

        inputFirstName.isHovering(window);
        inputFirstName.isClicked(event, window);

        inputLastName.isHovering(window);
        inputLastName.isClicked(event, window);

        inputDOB.isHovering(window);
        inputDOB.isClicked(event, window);

        genderCheckBox.isHovering(window);
        genderCheckBox.isClicked(window, event);
        int i = stuPage * 12;
        for (i; i < (stuPage + 1) * 12 && i < size; ++i)  classesButton[user.indexClass]->linkedButton[i]->isHovering(window);
        i = stuPage * 12;
        for (i; i < (stuPage + 1) * 12 && i < size; ++i) {
            if (classesButton[user.indexClass]->linkedButton[i]->isClicked(window, event)) {
                user.indexStudentInClass = i;
                prevPage = page;
                page = 17;
                break;
            }
        }

        if (addStuButton.isClicked(window, event)) {
            // Load data into variable
            classesArr[user.indexClass].listStudent = loadAddStudent();
            int z = classesArr[user.indexClass].numStudent;
            classesArr[user.indexClass].listStudent[z - 1].studentID = inputStuID.text.getString();
            classesArr[user.indexClass].listStudent[z - 1].socialID = inputSocialID.text.getString();
            classesArr[user.indexClass].listStudent[z - 1].firstName = inputFirstName.text.getString();
            classesArr[user.indexClass].listStudent[z - 1].lastName = inputLastName.text.getString();
            classesArr[user.indexClass].listStudent[z - 1].dob = inputDOB.text.getString();
            classesArr[user.indexClass].listStudent[z - 1].femaleGender = genderCheckBox.female;

            // Load data for UI
            classesButton[user.indexClass]->linkedButton = loadAddStuButton();
            // Clear input
            inputStuID.text.setString("");
            inputSocialID.text.setString("");
            inputFirstName.text.setString("");
            inputLastName.text.setString("");
            inputDOB.text.setString("");
            genderCheckBox.female = false;
            numStuBox.text.setString("Number students: " + to_string(classesArr[user.indexClass].numStudent));
        }
    }
    return;

}
void drawStaffClassDetailPage() {
    int size = classesArr[user.indexClass].numStudent;
    viewingPage.draw(window);
    viewLine.draw(window);
    schoolyearsSelect.draw(window);
    classesButtonSelect.draw(window);
    userIcon.draw(window);
    if (userIcon.isSelect) {
        burgerMenu.draw(window);
        profileStaff.draw(window);
        logOutButton.draw(window);
        passwordChange.draw(window);
    }
    if (schoolyearsSelect.isHover) hrztBarYear.draw(window);
    if (classesButtonSelect.isHover) hrztBarClass.draw(window);
    backButton.draw(window);
    rPageButton.draw(window);
    lPageButton.draw(window);
    viewLine.draw(window);
    inputSearchStu.draw(window);
    searchStuButton.draw(window);
    inputClassFile.draw(window);
    importClassButton.draw(window);
    numStuBox.draw(window);
    inputStuID.draw(window);
    inputSocialID.draw(window);
    inputFirstName.draw(window);
    inputLastName.draw(window);
    inputDOB.draw(window);
    genderCheckBox.draw(window);
    addStuButton.draw(window);

    int i = stuPage * 12;
    for (i; i < (stuPage + 1) * 12 && i < size; ++i)
        classesButton[user.indexClass]->linkedButton[i]->draw(window);
    return;
}

// Page 17
void handleStuDetailPage() { 
    seeStuID.text.setString(classesArr[user.indexClass].listStudent[user.indexStudentInClass].studentID);
    seeStuSocialID.text.setString(classesArr[user.indexClass].listStudent[user.indexStudentInClass].socialID);
    seeStuFirstName.text.setString(classesArr[user.indexClass].listStudent[user.indexStudentInClass].firstName);
    seeStuLastName.text.setString(classesArr[user.indexClass].listStudent[user.indexStudentInClass].lastName);
    seeStuDOB.text.setString(classesArr[user.indexClass].listStudent[user.indexStudentInClass].dob);
    if (classesArr[user.indexClass].listStudent[user.indexStudentInClass].femaleGender) seeStuGender.female = true;
    else seeStuGender.female = false;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        backButton.isHovering(window);
        if (backButton.isClicked(window, event)) {
            page = 16;
            prevPage = page;
            break;
        }

        schoolyearsSelect.isHovering(window);
        if (schoolyearsSelect.isClicked(window, event)) {
            page = 10;
            prevPage = page;
            break;
        }

        classesButtonSelect.isHovering(window);
        if (classesButtonSelect.isClicked(window, event)) {
            page = 11;
            prevPage = page;
            break;
        }

        userIcon.isClicked(window, event);
        if (userIcon.isSelect) {
            profileStaff.isHovering(window);
            logOutButton.isHovering(window);
            passwordChange.isHovering(window);
            if (profileStaff.isClicked(window, event)) {
                prevPage = page;
                page = 15;
                break;
            }
            if (logOutButton.isClicked(window, event)) {
                user.isStaff = false;
                page = 0;
                user.staff = nullptr;
                clearInput();
                break;
            }
            if (passwordChange.isClicked(window, event)) {
                prevPage = page;
                page = 14;
                break;
            }
        }
    }
    return;
}
void drawStuDetailPage() {
    viewingPage.draw(window);
	schoolyearsSelect.draw(window);
	classesButtonSelect.draw(window);
	userIcon.draw(window);
    if (userIcon.isSelect) {
		burgerMenu.draw(window);
		profileStaff.draw(window);
		logOutButton.draw(window);
		passwordChange.draw(window);
	}
	if (schoolyearsSelect.isHover) hrztBarYear.draw(window);
	if (classesButtonSelect.isHover) hrztBarClass.draw(window);
	backButton.draw(window);
	
    avatarStu.draw(window);
    seeStuID.draw(window);
	seeStuSocialID.draw(window);
	seeStuFirstName.draw(window);
	seeStuLastName.draw(window);
	seeStuDOB.draw(window);
	seeStuGender.draw(window);
	return;
}

//Page 19
void handleEventScoreboardPage() {
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();

        backButton.isHovering(window);
        if (backButton.isClicked(window, event)) {
            page = 13;
            prevPage = page;
            break;
        }

        schoolyearsSelect.isHovering(window);
        if (schoolyearsSelect.isClicked(window, event)) {
            page = 10;
            prevPage = page;
            break;
        }

        classesButtonSelect.isHovering(window);
        if (classesButtonSelect.isClicked(window, event)) {
            page = 11;
            prevPage = page;
            break;
        }

        courseDetailSelect.isHovering(window);
        if (courseDetailSelect.isClicked(window, event)) {
            page = 18;
            prevPage = page;
            break;
        }

        studentDetailSelect.isHovering(window);
        if (courseDetailSelect.isClicked(window, event)) {}

        userIcon.isClicked(window, event);
        if (userIcon.isSelect) {
            profileStaff.isHovering(window);
            logOutButton.isHovering(window);
            passwordChange.isHovering(window);
            if (profileStaff.isClicked(window, event)) {
                prevPage = page;
                page = 15;
                break;
            }
            if (logOutButton.isClicked(window, event)) {
                user.isStaff = false;
                page = 0;
                user.staff = nullptr;
                clearInput();
                break;
            }
            if (passwordChange.isClicked(window, event)) {
                prevPage = page;
                page = 14;
                break;
            }
        }

        inputAddStuCourse.isHovering(window);
        inputAddStuCourse.isClicked(event, window);
        if (addStuCourseButton.isClicked(window, event)) {}

        inputSearchStuCourse.isHovering(window);
        inputSearchStuCourse.isClicked(event, window);
        if (searchStuCourseButton.isClicked(window, event)) {}
        
        rPageButton.isHovering(window);
        if (rPageButton.isClicked(window, event)) {}

        lPageButton.isHovering(window);
        if (lPageButton.isClicked(window, event)) {}

        if (scoreSaveButton.isClicked(window, event)) {}
    }
}
void drawScoreboardPage() {
    viewingPage.draw(window);
    schoolyearsSelect.draw(window);
    classesButtonSelect.draw(window);
    courseDetailSelect.draw(window);
    studentDetailSelect.draw(window);
    userIcon.draw(window);
    if (userIcon.isSelect) {
        burgerMenu.draw(window);
        profileStaff.draw(window);
        logOutButton.draw(window);
        passwordChange.draw(window);
    }
    if (schoolyearsSelect.isHover) hrztBarYear.draw(window);
    if (classesButtonSelect.isHover) hrztBarClass.draw(window);
    if (courseDetailSelect.isHover) hrztBarCourseDetails.draw(window);
    if (studentDetailSelect.isHover) hrztBarStudentDetails.draw(window);
    backButton.draw(window);

    inputAddStuCourse.draw(window);
    addStuCourseButton.draw(window);
    inputSearchStuCourse.draw(window);
    searchStuCourseButton.draw(window);
    scoreBar.draw(window);
    scoreSaveButton.draw(window);
    int size =  schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[user.indexCourse].currStudents;
    for (int i = scorePage * 6; i < (scorePage + 1) * 6 && i < size; ++i) {
        schoolyearButton[user.indexSchoolyear]->linkedButton[user.indexSemester]->linkedButton[user.indexCourse]->scoreList[i]->draw(window);
	}
}

// Update data and UI dynamically
SchoolYear* loadAddSchoolyear(SchoolYear* old, int& numSchoolYear) {
    numSchoolYear++;
    SchoolYear* schoolYearArr = new SchoolYear[numSchoolYear];
    for (int i = 0; i < numSchoolYear - 1; i++) {
		schoolYearArr[i] = old[i];
	}
    delete[] old; // Delete old array years
    return schoolYearArr;
}
LinkedButton** loadAddYearButton(SchoolYear* schoolYearArr, LinkedButton** old, int& numSchoolYear) {
    LinkedButton** schoolyearButton = new LinkedButton * [numSchoolYear];
    
    // Calculate the column and page that the button is on
    int column = (numSchoolYear - 1) / 6;
    int page = column / 2;

    // Calculate the row that the button is on within its column
    int row = (numSchoolYear - 1) % 6;

    // Calculate the x and y position of the button
    float x = 115 + 225.0f * (column % 2);
    float y = 210 + 65.0f * row;
    
    // Copy the pointers of UI array
    for (int i = 0; i < numSchoolYear - 1; ++i) 
        schoolyearButton[i] = old[i];
    schoolyearButton[numSchoolYear - 1] = new LinkedButton(x, y, "image/Button200x45.png", schoolYearArr[numSchoolYear - 1].period);
    
    // Delete old year ptr buttons
    delete[] old;
    return schoolyearButton;
}
Semester* loadAddSemester(Semester* old, int& numSemester) {
	numSemester++;
	Semester* semesterArr = new Semester[numSemester];
	for (int i = 0; i < numSemester - 1; i++) {
		semesterArr[i] = old[i];
	}
    semesterArr[numSemester - 1].numSemesterInSchoolYear = numSemester;
	delete[] old; // Delete old array years
	return semesterArr;
}
LinkedButton** loadAddSemeButton(Semester* semeArr, LinkedButton** old, int& numSeme) {
    LinkedButton** semeArrButton = new LinkedButton * [numSeme];
    
    // Calculate position of seme
    float x2 = 640;
    float y2 = 437;
    float x = x2;
    float y = y2 + (numSeme - 1) * 65.0f;

    // Copy the pointers of UI array
    for (int i = 0; i < numSeme - 1; ++i)
        semeArrButton[i] = old[i];
    semeArrButton[numSeme - 1] = new LinkedButton(x, y, "image/Button200x45.png", "Semester " + to_string(semeArr[numSeme - 1].numSemesterInSchoolYear));

    // Delete old year ptr buttons
    delete[] old;
    return semeArrButton;
}
Class* loadAddClass() {
	numClass++;
	Class* newClassArr = new Class[numClass];
    for (int i = 0; i < numClass - 1; i++) {
        newClassArr[i] = classesArr[i];
	}
	delete[] classesArr; // Delete old array class
	return newClassArr;
}   
LinkedButton** loadAddClassButton() {
    LinkedButton** newClassButton = new LinkedButton * [numClass];
    // Calculate the column and page that the button is on
    int column = (numClass - 1) / 6;
    int page = column / 2;
    // Calculate the row that the button is on within its column
    int row = (numClass - 1) % 6;
    // Calculate the x and y position of the button
    float x = 115 + 225.0f * (column % 2);
    float y = 210 + 65.0f * row;

    for (int i = 0; i < numClass - 1; ++i) {
        newClassButton[i] = classesButton[i];
    }
    newClassButton[numClass - 1] = new LinkedButton(x, y, "image/Button200x45.png", classesArr[numClass - 1].classID);
    delete[] classesButton;
	return newClassButton;
}
Student* loadAddStudent() {
	int n = classesArr[user.indexClass].numStudent++;
    Student* newStudentArr = new Student[classesArr[user.indexClass].numStudent];
    for (int i = 0; i < n - 1; ++i) {
        newStudentArr[i] = classesArr[user.indexClass].listStudent[i];
    }
    delete[] classesArr[user.indexClass].listStudent;
    return newStudentArr;   
}
LinkedButton** loadAddStuButton() {
    LinkedButton** newClassButton = new LinkedButton * [classesArr[user.indexClass].numStudent];
	
    // Calculate the column and page that the button is on
	int column = (classesArr[user.indexClass].numStudent - 1) / 6;
	int page = column / 2;
	// Calculate the row that the button is on within its column
	int row = (classesArr[user.indexClass].numStudent - 1) % 6;
	// Calculate the x and y position of the button
	float x = 115 + 225.0f * (column % 2);
	float y = 210 + 65.0f * row;

    for (int i = 0; i < classesArr[user.indexClass].numStudent - 1; ++i) {
		newClassButton[i] = classesButton[user.indexClass]->linkedButton[i];
	}
	newClassButton[classesArr[user.indexClass].numStudent - 1] = new LinkedButton(x, y, "image/Button200x45.png", classesArr[user.indexClass].listStudent[classesArr[user.indexClass].numStudent - 1].studentID);
    delete[] classesButton[user.indexClass]->linkedButton;
	return newClassButton;
}
Course* loadAddCourse() {
	int n = ++schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].numCourses;
	Course* newCourseArr = new Course[n];
    for (int i = 0; i < n - 1; ++i) {
		newCourseArr[i] = schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[i];
	}
	
    newCourseArr[n - 1].ID = inputCourseID.text.getString().toAnsiString();
    newCourseArr[n - 1].className = inputClassIDforCourse.text.getString().toAnsiString();
    newCourseArr[n - 1].courseName = inputCourseName.text.getString().toAnsiString();
    newCourseArr[n - 1].numCredits = stoi(inputCredit.text.getString().toAnsiString());
    newCourseArr[n - 1].maxStudents = stoi(inputMaxStuInCourse.text.getString().toAnsiString());
    newCourseArr[n - 1].teacher = inputTeacherName.text.getString().toAnsiString();
    for (int i = 0; i < 6; ++i) {
        if (doWCourseButtonArr[i]->isSelect) {
			newCourseArr[n - 1].dayOfWeek = doWCourseButtonArr[i]->text.getString().toAnsiString();
			break;
		}
	}
    for (int i = 0; i < 4; ++i) {
		if (sessionCourseButtonArr[i]->isSelect) {
            newCourseArr[n - 1].session = sessionCourseButtonArr[i]->text.getString().toAnsiString();
        }
    }
    
    // Clear input
    inputCourseID.text.setString("");
    inputClassIDforCourse.text.setString("");
    inputCourseName.text.setString("");
    inputCredit.text.setString("");
    inputMaxStuInCourse.text.setString("");
    inputTeacherName.text.setString("");
	for (int i = 0; i < 6; ++i) doWCourseButtonArr[i]->isSelect = false;
    for (int i = 0; i < 4; ++i) sessionCourseButtonArr[i]->isSelect = false;
    
    delete[] schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester;
    return newCourseArr;
}
LinkedButton** loadAddCourseButton() {
	LinkedButton** newCourseButton = new LinkedButton * [schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].numCourses];
    // Number of courses in the semester
    int n = schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].numCourses;
	
    // Calculate the column and page that the button is on
	int column = (n - 1) / 6;
	int page = column / 2;
	// Calculate the row that the button is on within its column
	int row = (n - 1) % 6;
	// Calculate the x and y position of the button
	float x = 115 + 225.0f * (column % 2);
	float y = 210 + 65.0f * row;

    for (int i = 0; i < n - 1; ++i) {
		newCourseButton[i] = schoolyearButton[user.indexSchoolyear]->linkedButton[user.indexSemester]->linkedButton[i];
	}
	newCourseButton[schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].numCourses - 1] = new LinkedButton(x, y, "image/Button200x45.png",
        schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].coursesListInSemester[n - 1].ID);
	delete[] schoolyearButton[user.indexSchoolyear]->linkedButton[user.indexSemester]->linkedButton;
	
    
    return newCourseButton;
}

LinkedButton** loadAddCSVStuToClassButton(int numIc) {
    LinkedButton** newStuButton = new LinkedButton * [classesArr[user.indexClass].numStudent];
    for (int i = 0; i < classesArr[user.indexClass].numStudent - numIc; ++i) {
        delete classesButton[user.indexClass]->linkedButton[i];
    }
    int x = 115, y = 210;
    for (int i = 0; i < classesArr[user.indexClass].numStudent; ++i) {
        if (i % 12 == 0 && i != 0) {
            x = 115;
			y = 210;
		}
        else if (i % 6 == 0 && i != 0) {
            x += 225;
            y = 210;
        }
        cout << classesArr[user.indexClass].listStudent[i].studentID << endl;
        newStuButton[i] = new LinkedButton(x, y, "image/Button200x45.png", classesArr[user.indexClass].listStudent[i].studentID);
		y += 65;
    }
    return newStuButton;
}

// Free memory
void freeButtons() {
    for (int i = 0; i < numClass; ++i) {
        for (int j = 0; j < classesArr[i].numStudent; j++)
            delete classesButton[i]->linkedButton[j];
        delete[] classesButton[i]->linkedButton;
        delete classesButton[i];
    }
    delete[] classesButton;

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < schoolyearArr[i].numSemester; j++) {
            for (int v = 0; v < schoolyearArr[i].listSemester[j].numCourses; v++)
                delete schoolyearButton[i]->linkedButton[j]->linkedButton[v];
            delete[] schoolyearButton[i]->linkedButton[j]->linkedButton;
            delete schoolyearButton[i]->linkedButton[j];
        }
        delete[] schoolyearButton[i]->linkedButton;
        delete schoolyearButton[i];
    }
    delete[] schoolyearButton;

    for (int i = 0; i < numClass; ++i)
        delete[] classesArr[i].listStudent;
    delete[] classesArr;

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < schoolyearArr[i].numSemester; j++)
            delete[] schoolyearArr[i].listSemester[j].coursesListInSemester;
        delete[] schoolyearArr[i].listSemester;
    }
    delete[] schoolyearArr;
    delete[] staffArr;
    //delete[] courseArr;
}
