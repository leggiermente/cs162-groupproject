#include <iostream>

#include "run.h"
#include "readCSV.h"
#include "UI.h"

sf::RenderWindow window(sf::VideoMode(1280, 720), "Course Management", sf::Style::Close);
sf::Event event;
const float xMid = window.getSize().x / 2.0f;
const float yMid = window.getSize().y / 2.0f;
int page = 0;

//General
Button background(xMid, yMid, "image/Backgound.png");
UsernameBox inputUserBox(xMid, yMid - 50.0f);
PasswordBox inputPassBox(xMid, yMid + 51.0f);
LoginButton loginButton(xMid, yMid + 205.0f, "image/SignIn.png");
Button loginBox(xMid, yMid, "image/LoginBox.png");
CheckStaffButton checkStaffButton(xMid - 285.0f, yMid + 110.0f, "image/CheckStaffButton.png", "image/CheckedStaffButton.png");
Button menu(xMid, yMid, "image/MenuBackground.png");
Button seeProfile(xMid - 190.0f, yMid, "image/SeeProfile.png");
Button passwordChange(xMid, yMid + 80.0f, "image/Password.png");
Button logOutButton(xMid, yMid + 140.0f, "image/LogOut.png");
//Staff account
Button profileStaff(207.0f, 185.0f, "image/ProfileStaff.png");
Button classesButtonSelect(xMid, yMid + 20.0f, "image/ClassesButton.png");
Button schoolyearsSelect(xMid, yMid - 40.0f, "image/SchoolyearsButton.png");
ViewingPage viewingPage(xMid, yMid, "image/ViewingPage.png", "Viewing Schoolyears");
Button backButton(118.0f, 106.5f, "image/BackButton.png");

//Stu account
Button profileStu(207.0f, 185.0f, "image/ProfileStu.png");

//Currect user
CurrentUser user;

//Initial data from database
int numStu = 0,
    numStaff = 0,
    numCourse = 0,
    numClass = 0,
    numSchoolYear = 0;
//Student* stuArr = readStudentCSV("student.csv", numStu);
Student* stuArr = nullptr;
//Course* courseArr = readDirectory("database/course", numCourse);
//Class* classesArr = new Class[4];
//schoolYear* schoolyearArr = new schoolYear[2];

schoolYear* schoolyearArr = nullptr;
Class* classesArr = nullptr;
Staff* staffArr = nullptr;

// UI arrays
LinkedButton** schoolyearButton = nullptr;
LinkedButton** classesButton = nullptr;
ProfileText* profileText = nullptr;


void RunApp() 
{
    stuArr = readStudentText("database/student", numStu);
    schoolyearArr = readSchoolYear("database/schoolyear", numSchoolYear);
    classesArr = readClass("database/class", numClass);
    staffArr = readStaffCSV("staff.csv", numStaff);
    readCourseInSemester("database/course", schoolyearArr, numSchoolYear);
    
    schoolyearButton = new LinkedButton * [numSchoolYear];
    classesButton = new LinkedButton * [numClass];
    loadSchoolyears();
    
    //init();
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
                inputUserBox.handleEvent(event, window);
                inputPassBox.handleEvent(event, window);
                checkStaffButton.isClick(window, event, user.isStaff);

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
            checkStaffButton.draw(window, user.isStaff);                        
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
                if (passwordChange.isClicked(window, event));
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
                for (int i = 0; i < numClass; ++i) 
                    if (classesButton[i]->isClicked(window,event)) {
                        user.indexClass = i;
                        page = 16;
                        break;
                    }              
            }
            viewingPage.draw(window);
            backButton.draw(window);
            for (int i = 0; i < numClass; ++i) classesButton[i]->draw(window);
            break;
        }
        case 12: // Schoolyears Page
        {
            viewingPage.text.setString("Viewing Schoolyears");
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                if (backButton.isClicked(window,event)) {
                    page = 10;
                    break;
                }
                for (int i = 0; i < numSchoolYear; ++i) 
                    if (schoolyearButton[i]->isClicked(window,event)) {
                        page = 13;
                        user.indexSchoolyear = i;
                        break;
                    }               
            }
            //Draw
            viewingPage.draw(window);
            backButton.draw(window);
            for (int i = 0; i < 2; ++i) schoolyearButton[i]->draw(window);
            break;
        }
        case 13: // Semester Page
        {
            viewingPage.text.setString("Viewing Schoolyears " + schoolyearArr[user.indexSchoolyear].period);
            int size = schoolyearArr[user.indexSchoolyear].numSemester;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                if (backButton.isClicked(window,event)) {
                    page = 12;
                    break;
                }
                for (int i = 0; i < size; ++i) 
                    if (schoolyearButton[user.indexSchoolyear]->linkedButton[i]->isClicked(window,event)) {
                        user.indexSemester = i;
                        page = 14;
                        break;
                    }               
            }
            // Draw
            viewingPage.draw(window);
            backButton.draw(window);
            for (int i = 0; i < size; ++i) 
                schoolyearButton[user.indexSchoolyear]->linkedButton[i]->draw(window);
            break;
        }
        case 14: // Course Page
        {
            viewingPage.text.setString(
            "Viewing Schoolyears " + schoolyearArr[user.indexSchoolyear].period + 
            " Semester " + to_string(user.indexSemester + 1));
            int size = schoolyearArr[user.indexSchoolyear].listSemester[user.indexSemester].numCourses;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                if (backButton.isClicked(window, event)) {
                    page = 13;
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
        case 16: // See list stu in class
        {
            viewingPage.text.setString("Viewing students in class " + classesArr[user.indexClass].classID);
            int size = classesArr[user.indexClass].numStudent;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                if (backButton.isClicked(window,event)) {
                    page = 11;
                    break;
                }
                for (int i = 0; i < size; ++i) {
                    if (classesButton[user.indexClass]->linkedButton[i]->isClicked(window,event)) {
                        user.indexStudentInClass = i;
                        page = 17;
                        break;
                    }
                }
                
            }
            //Draw
            viewingPage.draw(window);
            backButton.draw(window);
            for (int i = 0; i < size; ++i) 
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
                if (passwordChange.isClicked(window, event));
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
bool validateUser() {
    if (user.id.empty()) return false;
    if (!isNumber(user.id)) return false;
    if (user.isStaff) {
        for (int i = 0; i < numStaff; ++i) {
            if (user.id == staffArr[i].staffID && user.password == staffArr[i].password) {
                user.staff = &staffArr[i];
                return 1;
            }
        }
    }
    else {
        for (int i = 0; i < numStu; ++i) {
            if (user.id == stuArr[i].studentID && user.password == stuArr[i].password) {
                user.student = &stuArr[i];
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
    // Create button for school years & semesters & courses 
    float x = 200.0f, y = 190.0f;
    for (int i = 0; i < numSchoolYear; ++i) {
        schoolyearButton[i] = new LinkedButton(x, y, "image/Button200x45.png", schoolyearArr[i].period);
        y += 65.0f;
        
        // Semester in school year
        if (schoolyearArr[i].numSemester != 0) {
            schoolyearButton[i]->linkedButton = new LinkedButton * [schoolyearArr[i].numSemester];
            schoolyearButton[i]->linkedButton = new LinkedButton * [schoolyearArr[i].numSemester];
            float x2 = 350.0f, y2 = 190.0f;
            for (int j = 0; j < schoolyearArr[i].numSemester; j++) {
                schoolyearButton[i]->linkedButton[j] = new LinkedButton(x2, y2, "image/Button400x45.png", "Semester " + to_string(j + 1));
                y2 += 65.0f;

                // Course in semester
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
    x = 200.0f; y = 190.0f;
    for (int i = 0; i < numClass; i++) {
        classesButton[i] = new LinkedButton(x, y, "image/Button200x45.png", classesArr[i].classID);
        y += 65.0f;
    }

    // Create button for all students of all classes
    for (int i = 0; i < numClass; i++) {
        x = 200.0f; y = 190.0f;
        int numStuClass = classesArr[i].numStudent;
        if (numStuClass != 0) {
            classesButton[i]->linkedButton = new LinkedButton * [numStuClass];
            for (int j = 0; j < numStuClass; j++) {
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
//void init() {
//    schoolyearArr[0].period = "2021 - 2022";
//    schoolyearArr[0].numSemester = 3;
//    schoolyearArr[0].listSemester = new Semester[3];
//    schoolyearArr[0].listSemester[0].numSemesterInSchoolYear = 1;
//    schoolyearArr[0].listSemester[1].numSemesterInSchoolYear = 2;
//    schoolyearArr[0].listSemester[2].numSemesterInSchoolYear = 3;
//
//    // Course in semester 1 2021 - 2022
//    schoolyearArr[0].listSemester[0].numCourses = 3;
//    schoolyearArr[0].listSemester[0].coursesListInSemester = new Course[3];
//    schoolyearArr[0].listSemester[0].coursesListInSemester[0].ID = "CS162";
//    schoolyearArr[0].listSemester[0].coursesListInSemester[0].className = "23APCS1";
//    schoolyearArr[0].listSemester[0].coursesListInSemester[1].ID = "MTH121";
//    schoolyearArr[0].listSemester[0].coursesListInSemester[1].className = "23APCS2";
//    schoolyearArr[0].listSemester[0].coursesListInSemester[2].ID = "CS162";
//    schoolyearArr[0].listSemester[0].coursesListInSemester[2].className = "23APCS2";
//
//    schoolyearArr[1].period = "2022 - 2023";
//    schoolyearArr[1].numSemester = 2;
//    schoolyearArr[1].listSemester = new Semester[2];
//    schoolyearArr[1].listSemester[0].numSemesterInSchoolYear = 1;
//    schoolyearArr[1].listSemester[1].numSemesterInSchoolYear = 2;
//
//    // Course in semester 2 2022 - 2023
//    schoolyearArr[1].listSemester[1].numCourses = 3;
//    schoolyearArr[1].listSemester[1].coursesListInSemester = new Course[3];
//    schoolyearArr[1].listSemester[1].coursesListInSemester[0].ID = "CS163";
//    schoolyearArr[1].listSemester[1].coursesListInSemester[0].className = "22APCS1";
//    schoolyearArr[1].listSemester[1].coursesListInSemester[1].ID = "MTH221";
//    schoolyearArr[1].listSemester[1].coursesListInSemester[1].className = "22APCS2";
//    schoolyearArr[1].listSemester[1].coursesListInSemester[2].ID = "CS163";
//    schoolyearArr[1].listSemester[1].coursesListInSemester[2].className = "22APCS2";
//
//    // Classes
//    classesArr[0].classID = "23APCS1";
//    classesArr[0].listStudent = stuArr;
//    classesArr[0].numStudent = numStu;
//
//    classesArr[1].classID = "23CLC08";
//    classesArr[2].classID = "22CLC01";
//    classesArr[3].classID = "21CTC03";
//    return;
//}
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