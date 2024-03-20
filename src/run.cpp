#include <iostream>

#include "run.h"
#include "readCSV.h"
#include "UI.h"

sf::RenderWindow window(sf::VideoMode(1280, 720), "Course Management", sf::Style::Close);
sf::Event event;
const float xMid = window.getSize().x / 2.0f;
const float yMid = window.getSize().y / 2.0f;
int page = 0;

Background background(xMid, yMid, "image/Backgound.png");
UsernameBox inputUserBox(xMid, yMid - 50.0f);
PasswordBox inputPassBox(xMid, yMid + 51.0f);
LoginButton loginButton(xMid, yMid + 205.0f, "image/SignIn.png");
LoginBox loginBox(xMid, yMid, "image/LoginBox.png");
CheckStaffButton checkStaffButton(xMid - 285.0f, yMid + 110.0f, "image/CheckStaffButton.png", "image/CheckedStaffButton.png");

//Staff Account
HomePage homePage(xMid, yMid, "image/HomeStaff.png", "image/HomeStu.png");
ClassesButton classesButton(xMid, yMid, "image/ClassesButton.png");
SchoolyearsButton schoolyearsButton(xMid, yMid - 50.0f, "image/SchoolyearsButton.png");
ViewingPage viewingPage(xMid, yMid, "image/ViewingPage.png", "Viewing Schoolyears");
LogOutButton logOutButton(xMid, yMid + 200.0f, "image/LogOut.png");
LogOutButton backButton(118.0f, 106.5f, "image/BackButton.png");

std::string Sid = "";
std::string Spassword = "";

int numStu = 0,
    numStaff = 0,
    numCourse = 0;
Student* stuArr = readStudentCSV("student.csv", numStu);
Staff* staffArr = readStaffCSV("staff.csv", numStaff);
Course* courseArr = readDirectory("course", numCourse);

schoolYear* schoolyearArr = new schoolYear[2];
int indexSchoolyear;
Button200x45** schoolyearButton = new Button200x45 * [2];

CurrentUser user;

void RunApp() 
{
    schoolyearArr[0].period = "2021 - 2022";
    schoolyearArr[0].numSemester = 3;
    schoolyearArr[0].listSemester = new Semester[3];
    schoolyearArr[0].listSemester[0].numSemesterInSchoolYear = 1;
    schoolyearArr[0].listSemester[1].numSemesterInSchoolYear = 2;
    schoolyearArr[0].listSemester[2].numSemesterInSchoolYear = 3;
    
    schoolyearArr[1].period = "2022 - 2023";
    schoolyearArr[1].numSemester = 2;
    schoolyearArr[1].listSemester = new Semester[2];
    schoolyearArr[1].listSemester[0].numSemesterInSchoolYear = 1;
    schoolyearArr[1].listSemester[1].numSemesterInSchoolYear = 2;

    loadSchoolyears();

    for (int i = 0; i < 2; i++) {
        int numSeme = schoolyearArr[i].numSemester;
        schoolyearButton[i]->semesterButtons = new Button400x45 * [numSeme];
        float x = 350.0f, y = 190.0f;
        for (int j = 0; j < numSeme; ++j) {
            schoolyearButton[i]->semesterButtons[j] = new Button400x45(x, y, "image/Button400x45.png", "Semester " + to_string(j + 1));
            y += 65.0f;
        }
    }


    window.setFramerateLimit(60);
    while (window.isOpen()) 
    {
        switch (page) {
        case 0: // Login Page
        {
            // Read input from mouse and keyboard
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                inputUserBox.handleEvent(event, window);
                inputPassBox.handleEvent(event, window);
                checkStaffButton.isClick(window, user.isStaff);

                if (loginButton.isClicked(window, inputUserBox.text, inputPassBox.text, Sid, Spassword)) {
                    if (validateUser()) {
                        if (user.isStaff) page = 1;
                        else page = 2;
                    }
                    else 
                        clearInput();                   
                }
                // Draw Element 
                background.draw(window);
                loginBox.draw(window);
                loginButton.draw(window);
                inputUserBox.draw(window);
                inputPassBox.draw(window);
                checkStaffButton.draw(window, user.isStaff);                
                window.display();
            }
            break;
        }
        case 1: // Staff menu page
        {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (schoolyearsButton.isClicked(window)) page = 4;
                if (classesButton.isClicked(window)) page = 3;
                if (logOutButton.isClicked(window)) {
                    user.isStaff = false;
                    page = 0;
                    clearInput();
                    break;
                }
                // Draw
                background.draw(window);
                homePage.draw(window, user.isStaff);
                classesButton.draw(window);
                schoolyearsButton.draw(window);
                logOutButton.draw(window);
                window.display();
            }
            break;
        }
        case 2: // Student menu page
        {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                if (logOutButton.isClicked(window)) {
                    user.isStaff = false;
                    page = 0;
                    clearInput();
                    break;
                }
                
                // Draw
                background.draw(window);
                homePage.draw(window, user.isStaff);
                logOutButton.draw(window);
                window.display();
            }
            break;
        }
        case 3: // Classes Page
        {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            background.draw(window);
            window.display();
            break;
        }
        case 4: // Schoolyears Page
        {
            viewingPage.text.setString("Viewing Schoolyears");
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                if (backButton.isClicked(window)) {
                    page = 1;
                    break;
                }
                //Draw
                background.draw(window);
                viewingPage.draw(window);
                backButton.draw(window);
                for (int i = 0; i < 2; ++i) {
                    if (schoolyearButton[i]->isClicked(window)) {
                        page = 5;
                        indexSchoolyear = i;
                    }
                    schoolyearButton[i]->draw(window);
                }
                window.display();
            }
            break;
        }
        case 5: // Semester Page
        {
            viewingPage.text.setString("Viewing Schoolyears " + schoolyearArr[indexSchoolyear].period);
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                if (backButton.isClicked(window)) {
                    page = 4;
                    break;
                }

                // Draw
                background.draw(window);
                viewingPage.draw(window);
                backButton.draw(window);
                int size = schoolyearArr[indexSchoolyear].numSemester;
                for (int i = 0; i < size; ++i) {
                    if (schoolyearButton[indexSchoolyear]->semesterButtons[i]->isClicked(window));
                    schoolyearButton[indexSchoolyear]->semesterButtons[i]->draw(window);
                }
                window.display();
            }
            break;
            
        }
        default: 
        {
            break;
        }
        }
    }
    // Console check
    std::cout << "Username: " << Sid << std::endl;
    std::cout << "Password: " << Spassword << std::endl;
    return;
}
bool validateUser() {
    if (Sid.empty()) return false;
    if (!isNumber(Sid)) return false;
    int Iid = stoi(Sid);
    if (user.isStaff) {
        for (int i = 0; i < numStaff; ++i) {
            if (Iid == staffArr[i].staffID && Spassword == staffArr[i].password) {
                user.staff = staffArr[i];
                return 1;
            }
        }
    }
    else {
        for (int i = 0; i < numStu; ++i) {
            if (Iid == stuArr[i].studentID && Spassword == stuArr[i].password) {
                user.student = stuArr[i];
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
void loadSchoolyears() {
    float x = 200.0f, y = 190.0f;
    for (int i = 0; i < 2; ++i) {
        schoolyearButton[i] = new Button200x45(x, y, "image/Button200x45.png", schoolyearArr[i].period);
        y += 65.0f;
    }
}
void clearInput() {
    inputUserBox.text.setString("");
    inputPassBox.text.setString("");
    inputPassBox.star.setString("");
}