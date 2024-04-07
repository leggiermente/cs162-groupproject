#include <iostream>

#include <SFML/Graphics.hpp>

#include "run.h"
#include "HandleData.h"
#include "UI.h"

sf::RenderWindow window(sf::VideoMode(1280, 720), "Course Management", sf::Style::Close);
sf::Event event;
const float xMid = window.getSize().x / 2.0f;
const float yMid = window.getSize().y / 2.0f;

//General UI
Button background(xMid, yMid, "image/Backgound.png");
InputBox inputUserBox(xMid, yMid - 50.0f, "image/TextBox.png");
PasswordBox inputPassBox(xMid, yMid + 51.0f, "image/TextBox.png");
LoginButton loginButton(xMid, yMid + 205.0f, "image/SignIn.png");
Button loginBox(xMid, yMid, "image/LoginBox.png");
CheckStaffButton checkStaffButton(xMid - 285.0f, yMid + 110.0f, "image/CheckStaffButton.png", "image/CheckedStaffButton.png");
Button menu(xMid, yMid, "image/MenuBackground.png");
Button seeProfile(xMid - 190.0f, yMid, "image/SeeProfile.png");
Button passwordChange(xMid, yMid + 80.0f, "image/Password.png");
Button logOutButton(xMid, yMid + 140.0f, "image/LogOut.png");




//Staff UI
Button profileStaff(207.0f, 185.0f, "image/ProfileStaff.png");
Button classesButtonSelect(xMid, yMid + 20.0f, "image/ClassesButton.png");
Button schoolyearsSelect(xMid, yMid - 40.0f, "image/SchoolyearsButton.png");
ViewingPage viewingPage(xMid, yMid, "image/ViewingPage.png", "");
Button backButton(118.0f, 106.5f, "image/BackButton.png");
Button rPageButton(502.5f, 625.0f, "image/RightPageButton.png");
Button lPageButton(122.5f, 625.0f, "image/LeftPageButton.png");

// Button in Schoolyear && semesterpage
InputWithHead inputYear(837.5f, 205.0f, "image/Input425x45.png", "School year:");
Line viewLine(575.0f, 157.5f, 1.0f, 435.0f);
TextBox semesterBox(725.0f, 305.0f, "image/ViewSeme.png", "");
Button addYearButton(1125.0f, 205.0f, "image/AddButton.png");
InputWithHead inputStartDateSem(950.0f, 325.0f, "image/InputDataSeme.png", "Start Date:");
InputWithHead inputEndDateSem(950.0f, 395.0f, "image/InputDataSeme.png", "End Date:");
Button addSemeButton(1125.0f, 395.0f, "image/AddButton.png");

// Button in class page
InputWithHead inputClass(837.5f, 205.0f, "image/Input425x45.png", "Class:");
Button addClassButton(1125.0f, 205.0f, "image/AddButton.png");

// Button in student page
TextBox numStuBox(750.0f, 340.0f, "image/NumStuBox.png", "Number students: ", "");
InputWithHead inputStuID(750.0f, 430.0f, "image/Input250x45.png", "Student ID");
InputWithHead inputSocialID(1025.0f, 430.0f, "image/Input250x45.png", "Social ID");
InputWithHead inputFirstName(750.0f, 500.0f, "image/Input250x45.png", "First name");
InputWithHead inputLastName(1025.0f, 500.0f, "image/Input250x45.png", "Last name");
InputWithHead inputDOB(750.0f, 570.0f, "image/Input250x45.png", "Date of Birth");
TextChangeBox genderCheckBox(962.5f, 570.0f, "image/Input125x45.png", "Gender", "Male", "Female");
Button addStuButton(1100.0f, 570.0f, "image/AddButton.png");

// lehoangan02 scoreboard button
Button scoreboardButton(xMid, yMid + 20.0f, "image/Scoreboard.png");
// lehoangan02 inside view Scoreboard
InputWithHead inputYearforScoreboard(225.0f, 180.0f, "image/Input250x45.png", "Input Year");
InputWithHead inputSemesterforScoreboard(225.0f, 180 + 90, "image/Input250x45.png", "Input Semester");
InputWithHead inputCourseforScoreboard(225.0f, 180 + 180, "image/Input250x45.png", "Input Course");
Button viewScoreboard(145.0f, 360 + 90, "image/View.png");
//Text to view scoreboard
BareboneText CourseText(600, 155, "Course");
BareboneText TotalMarkText(700, 155, "Total");
BareboneText FinalMarkText(800, 155, "Final");
BareboneText MidtermMarkText(900, 155, "Midterm");
BareboneText OtherMarkText(1025, 155, "Other");
//Midterm Mark, and Other Mark
//Stu account
Button profileStu(207.0f, 185.0f, "image/ProfileStu.png");


// Page control
int page = 0,
    yearPage = 0,
    classPage = 0,
    stuPage = 0;

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
ProfileText* profileText = nullptr;

//Currect user
CurrentUser user;


void RunApp() 
{
    classesArr = readClass("database/class", numClass);
    staffArr = readStaffCSV("staff.csv", numStaff);
    schoolyearArr = readSchoolYear("database/schoolyear", numSchoolYear);
    readCourseInSemester("database/course", schoolyearArr, numSchoolYear, classesArr, numClass);
    
    schoolyearButton = new LinkedButton * [numSchoolYear];
    classesButton = new LinkedButton * [numClass];
    loadSchoolyears();
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
                if (event.type == sf::Event::Closed)
                    window.close();
                inputUserBox.isClicked(event, window);
                inputPassBox.isClicked(event, window);
                //checkStaffButton.isClick(window, event, user.isStaff);

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
            inputUserBox.draw(window);
            inputPassBox.draw(window);
            //checkStaffButton.draw(window, user.isStaff);                        
            break;
        }
        case 10: // Staff menu page (Page 10 - 29 / Staff)
        {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (schoolyearsSelect.isClicked(window, event)) {
                    page = 12;
                    break;
                }
                if (classesButtonSelect.isClicked(window, event)) {
                    page = 11;
                    break;
                }
                if (profileStaff.isClicked(window, event)) {
                    profileText = new ProfileText(user.staff->firstName, user.staff->lastName, user.staff->staffID);
                    page = 15;
                    break;
                }
                if (logOutButton.isClicked(window, event)) {
                    user.isStaff = false;
                    page = 0;
                    delete profileText;
                    profileText = nullptr;
                    user.staff = nullptr;
                    clearInput();
                    break;
                }
                passwordChange.isClicked(window, event);
            }
            // Draw
            menu.draw(window);
            profileStaff.draw(window);
            classesButtonSelect.draw(window);
            schoolyearsSelect.draw(window);
            logOutButton.draw(window);
            passwordChange.draw(window);    
            break;
        }
        case 11: // Classes Page
        {
            viewingPage.text.setString("Viewing classes");
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (backButton.isClicked(window,event)) {
                    page = 10;
                    break;
                }
                
                int i = classPage * 14;
                for (; i < (classPage + 1) * 14 && i < numClass; ++i)
                    if (classesButton[i]->isClicked(window,event)) {
                        user.indexClass = i;
                        page = 16;
                        stuPage = 0;
                        numStuBox.text.setString("Number students: " + to_string(classesArr[i].numStudent));
                        break;
                    }   
                
                inputClass.isClicked(event, window);
                if (addClassButton.isClicked(window, event)) {
                    classesArr = loadAddClass();
					classesArr[numClass - 1].classID = inputClass.text.getString();
					classesButton = loadAddClassButton();
					inputClass.text.setString("");
                }
                if (rPageButton.isClicked(window, event)) {
                    // If page is not the last page
                    if (classPage < numClass / 14) classPage++;
                }
                if (lPageButton.isClicked(window, event)) {
                    // If page is not the first page
                    if (classPage > 0) classPage--;
                }
            }
            
            // Draw
            viewingPage.draw(window);
            backButton.draw(window);
            rPageButton.draw(window);
            lPageButton.draw(window);
            viewLine.draw(window);
            inputClass.draw(window);
            addClassButton.draw(window);
            int i = classPage * 14;
            for (; i < (classPage + 1) * 14 && i < numClass; ++i)
                classesButton[i]->draw(window);
            break;
        }
        case 12: // Schoolyears Page
        {
            viewingPage.text.setString("Viewing school years");
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                inputYear.isClicked(event, window); // Input school year
                // Add school year
                if (addYearButton.isClicked(window, event)) {
                    string txt = inputYear.text.getString(); //checking input
                    if (validateSchoolYear(txt, schoolyearArr, numSchoolYear)) {
                        schoolyearArr = loadAddSchoolyear(schoolyearArr, numSchoolYear);
                        schoolyearArr[numSchoolYear - 1].period = txt;
                        schoolyearButton = loadAddYearButton(schoolyearArr, schoolyearButton, numSchoolYear);
                    }
                    inputYear.text.setString("");
                }
                if (backButton.isClicked(window,event)) {
                    page = 10;
                    break;
                }
                if (rPageButton.isClicked(window, event)) {
                    // If page is not the last page
                    if (yearPage < numSchoolYear / 14) yearPage++;
                }
                if (lPageButton.isClicked(window, event)) {
					// If page is not the first page
                    if (yearPage > 0) yearPage--;
				}
                // Check if user click on a schoolyear button
                int i = yearPage * 14;
                for (i ; i < (yearPage + 1) * 14 && i < numSchoolYear; ++i)
                    if (schoolyearButton[i]->isClicked(window,event)) {
                        user.indexSchoolyear = i;
                        break;
                    } 
                if (user.indexSchoolyear != -1) {
                    int size = schoolyearArr[user.indexSchoolyear].numSemester;
					for (int i = 0; i < size; ++i) 
                        if (schoolyearButton[user.indexSchoolyear]->linkedButton[i]->isClicked(window, event)) {
							user.indexSemester = i;
							page = 13;
							break;
						}
				}
                // Check if numseme < 3 to display input seme 
                if (user.indexSemester != -1 && schoolyearArr[user.indexSchoolyear].numSemester < 3) {
                    inputStartDateSem.isClicked(event,window);
                    inputEndDateSem.isClicked(event, window);
                    // Add seme to year
                    if (addSemeButton.isClicked(window, event)) {
                        string startDate = inputStartDateSem.text.getString();
                        string endDate = inputEndDateSem.text.getString();
                        if (validateSemester(startDate, endDate, schoolyearArr[user.indexSchoolyear].period)) {
                            // Create new list of semester with size + 1
                            schoolyearArr[user.indexSchoolyear].listSemester = loadAddSemester(schoolyearArr[user.indexSchoolyear].listSemester, schoolyearArr[user.indexSchoolyear].numSemester);
                            // Add data to new semester
                            schoolyearArr[user.indexSchoolyear].listSemester[schoolyearArr[user.indexSchoolyear].numSemester - 1].startDate = startDate;
                            schoolyearArr[user.indexSchoolyear].listSemester[schoolyearArr[user.indexSchoolyear].numSemester - 1].endDate = endDate;
                            // Create new button for semester
                            schoolyearButton[user.indexSchoolyear]->linkedButton = loadAddSemeButton(schoolyearArr[user.indexSchoolyear].listSemester, schoolyearButton[user.indexSchoolyear]->linkedButton, schoolyearArr[user.indexSchoolyear].numSemester);
                        }
                        inputStartDateSem.text.setString("");
						inputEndDateSem.text.setString("");
                    }
                }
            }

            //Draw
            viewingPage.draw(window);
            backButton.draw(window);
            rPageButton.draw(window);
            lPageButton.draw(window);
            int i = yearPage * 14;
            for (i ; i < (yearPage + 1) * 14 && i < numSchoolYear; ++i)
                schoolyearButton[i]->draw(window);
            inputYear.draw(window);
            addYearButton.draw(window);
            viewLine.draw(window);
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
            break;
        }
        case 13: // Course Page
        {
            viewingPage.text.setString(
            "Viewing Schoolyears " + schoolyearArr[user.indexSchoolyear].period + 
            " Semester " + to_string(user.indexSemester + 1));
            int size = schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].numCourses;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                if (backButton.isClicked(window, event)) {
                    page = 12;
                    break;
                }
                for (int i = 0; i < size; ++i) 
                    if (schoolyearButton[user.indexSchoolyear]->linkedButton[user.indexSemester]->linkedButton[i]->isClicked(window,event));
            }
            // Draw
            viewingPage.draw(window);
            backButton.draw(window);
            for (int i = 0; i < size; ++i) 
                schoolyearButton[user.indexSchoolyear]->linkedButton[user.indexSemester]->linkedButton[i]->draw(window);
            break;
        }
        case 15: // Staff profile
        {
            viewingPage.text.setString("Viewing profile");
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                if (backButton.isClicked(window,event)) {
                    page = 10;
                    break;
                }
            }
            // Draw
            viewingPage.draw(window);
            backButton.draw(window);
            seeProfile.draw(window);
            profileText->drawStaff(window);
            break;
        }
        case 16: // Student in class page
        {
            viewingPage.text.setString("Viewing students in class " + classesArr[user.indexClass].classID);
            int size = classesArr[user.indexClass].numStudent;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                if (backButton.isClicked(window, event)) {
                    page = 11;
                    break;
                }
                int i = stuPage * 14;
                for (; i < (stuPage + 1) * 14 && i < size; ++i) {
                    if (classesButton[user.indexClass]->linkedButton[i]->isClicked(window, event)) {
                        user.indexStudentInClass = i;
                        page = 17;
                        break;
                    }
                }
                if (rPageButton.isClicked(window, event)) {
                    // If page is not the last page
                    if (stuPage < classesArr[user.indexClass].numStudent / 14) stuPage++;
                }
                if (lPageButton.isClicked(window, event)) {
                    // If page is not the first page
                    if (stuPage > 0) stuPage--;
                }

                // Add student control
                inputStuID.isClicked(event, window);
                inputSocialID.isClicked(event, window);
                inputFirstName.isClicked(event, window);
                inputLastName.isClicked(event, window);
                inputDOB.isClicked(event, window);
                genderCheckBox.isClicked(window, event);
                if (addStuButton.isClicked(window, event)) {
                    // Load data into variable
                    classesArr[user.indexClass].listStudent = loadAddStudent();
                    int z = classesArr[user.indexClass].numStudent;
                    classesArr[user.indexClass].listStudent[z - 1].studentID = inputStuID.text.getString();
                    classesArr[user.indexClass].listStudent[z - 1].socialID = inputSocialID.text.getString();
                    classesArr[user.indexClass].listStudent[z - 1].firstName = inputFirstName.text.getString();
                    classesArr[user.indexClass].listStudent[z - 1].lastName = inputLastName.text.getString();
                    classesArr[user.indexClass].listStudent[z - 1].dob = inputDOB.text.getString();
                    classesArr[user.indexClass].listStudent[z - 1].femaleGender = genderCheckBox.active;

                    // Load data for UI
                    classesButton[user.indexClass]->linkedButton = loadAddStuButton();
                    // Clear input
                    inputStuID.text.setString("");
                    inputSocialID.text.setString("");
                    inputFirstName.text.setString("");
                    inputLastName.text.setString("");
                    inputDOB.text.setString("");
                    genderCheckBox.active = false;  
                    numStuBox.text.setString("Number students: " + to_string(classesArr[user.indexClass].numStudent));
                }
            }
            //Draw
            viewingPage.draw(window);
            backButton.draw(window);
            rPageButton.draw(window);
            lPageButton.draw(window);
            viewLine.draw(window);
            numStuBox.draw(window);
            
            inputStuID.draw(window);
            inputSocialID.draw(window);
            inputFirstName.draw(window);
            inputLastName.draw(window);
            inputDOB.draw(window);
            genderCheckBox.draw(window);
            addStuButton.draw(window);
            
            int i = stuPage * 14;
            for (; i < (stuPage + 1) * 14 && i < size; ++i)
                classesButton[user.indexClass]->linkedButton[i]->draw(window);
            break;
        }
        case 17: // See detail of stu
        {
            viewingPage.text.setString("Viewing student profile");
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                if (backButton.isClicked(window,event)) {
                    page = 16;
                    break;
                }
            }
            // Draw
            viewingPage.draw(window);
            backButton.draw(window);
            break;
        }
        case 30: // Student menu page (Page 30 -> Student)
        {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                if (logOutButton.isClicked(window,event)) {
                    user.isStaff = false;
                    page = 0;
                    delete profileText;
                    profileText = nullptr;
                    user.student = nullptr;
                    clearInput();
                    break;
                }
                if (profileStu.isClicked(window,event)) {
                    string gender;
                    if (user.student->femaleGender) gender = "Female";
                    else gender = "Male";
                    profileText = new ProfileText(user.student->firstName, user.student->lastName,
                        user.student->studentID, user.student->dob, gender, user.student->socialID);
                    page = 31;
                    break;
                }
                if (scoreboardButton.isClicked(window, event))
                {
                    page = 32;
                    cout << "viewing courses" << endl; // note for terminal lehoangan02
                    break;
                }
                passwordChange.isClicked(window, event);
            }
            // Draw
            menu.draw(window);
            profileStu.draw(window);
            passwordChange.draw(window);
            logOutButton.draw(window);
            scoreboardButton.draw(window);
            break;
        }
        case 31: // Stu profile
        {
            viewingPage.text.setString("Viewing profile");
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                if (backButton.isClicked(window,event)) {
                    page = 30;
                    break;
                }
            }
            // Draw
            viewingPage.draw(window);
            backButton.draw(window);
            seeProfile.draw(window);
            profileText->drawStu(window);
            break;
        }
        case 32: // Courses Page
            {
                //cout << "viewing page 32" << endl; lehoangan02 testing output
                viewingPage.text.setString("Scoreboard");
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                    if (backButton.isClicked(window,event)) {
                        page = 30; // comback to StuMenuPage
                        break;
                    }
                    inputYearforScoreboard.isClicked(event, window);
                    inputSemesterforScoreboard.isClicked(event, window);
                    inputCourseforScoreboard.isClicked(event, window);
                    cout << user.id << endl;
                }
                
                // Draw
                viewingPage.draw(window);
                backButton.draw(window);
                viewLine.draw(window);
                inputYearforScoreboard.draw(window);
                inputSemesterforScoreboard.draw(window);
                inputCourseforScoreboard.draw(window);
                viewScoreboard.draw(window);
                CourseText.draw(window);
                TotalMarkText.draw(window);
                FinalMarkText.draw(window);
                MidtermMarkText.draw(window);
                OtherMarkText.draw(window);
                int i = classPage * 14;
                break;
            }
        default:
        {
            break;
        }
        }
        window.display();
    }
    saveSchoolYear("database/schoolyear", schoolyearArr, numSchoolYear);
    // Console check
    std::cout << "Username: " << user.id << std::endl;
    std::cout << "Password: " << user.password << std::endl;
    return;
}
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
bool validateSchoolYear(string& txt, SchoolYear* schoolyearArr, int numSchoolYear) {
    string tmp = "";
    for (int i = 0;i < txt.size();i++) {
        if (txt[i] != ' ') {
            tmp += txt[i];
        }
    } //removes space in string
    swap(txt, tmp);
    if (txt.size() != 9) return false; //check the format of the input must be "xxxx-xxxx"
    for (int i = 0;i < txt.size();i++) {
        if (i != 4) {
            if (txt[i] < '0' || txt[i]>'9') return false;
        }
        else if (txt[i] != '-') return false;
    }
    for (int i = 0;i < numSchoolYear;i++) {
        if (txt == schoolyearArr[i].period) {
            return false;
        }
    }
    int s1 = 0, s2 = 0; //check two years of the period
    for (int i = 0;i < 4;i++) {
        s1 = s1 * 10 + txt[i] - '0';
        s2 = s2 * 10 + txt[5 + i] - '0';
    }
    return (s1==s2-1); //return if the period is exactly 1 year.
}
bool validateSemester(string &startDate, string &endDate, string period) {
    string tmp = "";
    for (int i = 0;i < startDate.size();i++) {
        if (startDate[i] != ' ') {
            tmp += startDate[i];
        }
    }
    startDate = tmp;
    tmp = "";
    for (int i = 0;i < endDate.size();i++) {
        if (endDate[i] != ' ') {
            tmp += endDate[i];
        }
    }
    endDate = tmp;
    //removes space in string
    if (startDate.size() != 10 || endDate.size() != 10) return false; 
    for (int i = 0;i < 10;i++) {
        if (i == 2 || i == 5) {
            if (startDate[i] != '-' || endDate[i] != '-') return false;
        }
        else {
            if (startDate[i] < '0' || startDate[i]>'9' || endDate[i] < '0' || endDate[i]>'9') return false;
        }
    }   //check if start date and end date format to be dd-mm-yyyy, validate length
    if (!validateTimeFormat(startDate,endDate,period)) return false; //validate format of time, the end date must be latter than the start date
    return true;
}
bool validateTimeFormat(string startDate, string endDate, string period) {
    int startDay = 0, startMonth = 0, startYear = 0;
    int endDay = 0, endMonth = 0, endYear = 0;
    int startSchoolYear = 0, endSchoolYear = 0;
    for (int i = 0;i < 2;i++) {
        startDay = startDay * 10 + (startDate[i] - '0');
        endDay = endDay * 10 + (endDate[i] - '0');
        startMonth = startMonth * 10 + (startDate[i + 3] - '0');
        endMonth = endMonth * 10 + (endDate[i + 3] - '0');
    }
    for (int i = 6;i < 10;i++) {
        startYear = startYear * 10 + (startDate[i] - '0');
        endYear = endYear * 10 + (endDate[i] - '0');
        startSchoolYear = startSchoolYear * 10 + (period[i - 6] - '0');
        endSchoolYear = endSchoolYear * 10 + (period[i - 1] - '0');
    }
    if (startYear > endYear || (startYear != startSchoolYear && startYear != endSchoolYear) || (endYear != startSchoolYear && endYear != endSchoolYear))
        return false; //check valid format of year
    if ((startMonth > endMonth && startYear == endYear) || startMonth > 12 || startMonth <= 0 || endMonth > 12 || endMonth <= 0)
        return false;
    int maxDayOfTheMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31 };
    if ((startDay>maxDayOfTheMonth[startMonth-1]+((startMonth==2 && (startYear%400==0 || (startYear%4==0 && startYear%100!=0)))? 1: 0)) || 
        (endDay > maxDayOfTheMonth[endMonth - 1] + ((endMonth == 2 && (endYear % 400 == 0 || (endYear % 4 == 0 && endYear % 100 != 0))) ? 1 : 0))
            || (startDay>endDay && startMonth==endMonth && startYear==endYear))
            return false;
    return true;
}
bool isNumber(const std::string& str) {
    for (char const& c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}
void loadSchoolyears() {
    // Create year & semester & course buttons
    float x = 200.0f, y = 180.0f;
    for (int i = 0; i < numSchoolYear; ++i) {
        if (i % 14 == 0 && i != 0) { // Return origin when need new page
            x = 200.0f;
			y = 180.0f;
		}
        else if (i % 7 == 0 && i != 0) { // x,y coordinate of button for each page
            x += 225.0f;
            y = 180.0f;
        }
        schoolyearButton[i] = new LinkedButton(x, y, "image/Button200x45.png", schoolyearArr[i].period);
        y += 65.0f;

        // Create semester button in year
        if (schoolyearArr[i].numSemester != 0) {
            schoolyearButton[i]->linkedButton = new LinkedButton * [schoolyearArr[i].numSemester];
            schoolyearButton[i]->linkedButton = new LinkedButton * [schoolyearArr[i].numSemester];
            float x2 = 725.0f, y2 = 370.0f;
            for (int j = 0; j < schoolyearArr[i].numSemester; j++) {
                schoolyearButton[i]->linkedButton[j] = new LinkedButton(x2, y2, "image/Button200x45.png", "Semester " + to_string(j + 1));
                y2 += 65.0f;

                // Create course buttons in semester
                if (schoolyearArr[i].listSemester[j].numCourses != 0) {
                    schoolyearButton[i]->linkedButton[j]->linkedButton = new LinkedButton * [schoolyearArr[i].listSemester[j].numCourses];
                    float x3 = 200.0f, y3 = 190.0f;
                    for (int k = 0; k < schoolyearArr[i].listSemester[j].numCourses; k++) {
                        schoolyearButton[i]->linkedButton[j]->linkedButton[k]
                            = new LinkedButton(x3, y3, "image/Button200x45.png",
                                schoolyearArr[i].listSemester[j].coursesListInSemester[k].ID);
                        y3 += 65.0f;
                    }
                }
            }
        }
    }
    
    // Create button for all classes have existed
    x = 200.0f; y = 180.0f;
    for (int i = 0; i < numClass; ++i) {
        if (i % 14 == 0 && i != 0) { // Return origin when need new page
            x = 200.0f;
            y = 180.0f;
        }
        else if (i % 7 == 0 && i != 0) { // x,y coordinate of button for each page
            x += 225.0f;
            y = 180.0f;
        }
        classesButton[i] = new LinkedButton(x, y, "image/Button200x45.png", classesArr[i].classID);
        y += 65.0f;
	}

    // Create button for all students of all classes
    for (int i = 0; i < numClass; i++) {
        x = 200.0f; y = 180.0f;
        int numStuClass = classesArr[i].numStudent;
        if (numStuClass != 0) {
            classesButton[i]->linkedButton = new LinkedButton * [numStuClass];
            for (int j = 0; j < numStuClass; j++) {
                if (j % 14 == 0 && j != 0) { // Return origin when need new page
                    x = 200.0f;
                    y = 180.0f;
                }
                else if (j % 7 == 0 && j != 0) { // x,y coordinate of button for each page
                    x += 225.0f;
                    y = 180.0f;
                }
                classesButton[i]->linkedButton[j] = new LinkedButton(x, y, "image/Button200x45.png", classesArr[i].listStudent[j].studentID);
                y += 65.0f;
            }
        }
    }
}
void clearInput() {
    inputUserBox.text.setString("");
    inputPassBox.text.setString("");
    inputPassBox.star.setString("");
}
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

    if (profileText) delete profileText;
}
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
    int column = (numSchoolYear - 1) / 7;
    int page = column / 2;

    // Calculate the row that the button is on within its column
    int row = (numSchoolYear - 1) % 7;

    // Calculate the x and y position of the button
    float x = 200.0f + 225.0f * (column % 2);
    float y = 180.0f + 65.0f * row;
    
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
    float x2 = 725.0f;
    float y2 = 370.0f;
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
    int column = (numClass - 1) / 7;
    int page = column / 2;
    // Calculate the row that the button is on within its column
    int row = (numClass - 1) % 7;
    // Calculate the x and y position of the button
    float x = 200.0f + 225.0f * (column % 2);
    float y = 180.0f + 65.0f * row;

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
	int column = (classesArr[user.indexClass].numStudent - 1) / 7;
	int page = column / 2;
	// Calculate the row that the button is on within its column
	int row = (classesArr[user.indexClass].numStudent - 1) % 7;
	// Calculate the x and y position of the button
	float x = 200.0f + 225.0f * (column % 2);
	float y = 180.0f + 65.0f * row;

    for (int i = 0; i < classesArr[user.indexClass].numStudent - 1; ++i) {
		newClassButton[i] = classesButton[user.indexClass]->linkedButton[i];
	}
	newClassButton[classesArr[user.indexClass].numStudent - 1] = new LinkedButton(x, y, "image/Button200x45.png", classesArr[user.indexClass].listStudent[classesArr[user.indexClass].numStudent - 1].studentID);
    delete[] classesButton[user.indexClass]->linkedButton;
	return newClassButton;
}
