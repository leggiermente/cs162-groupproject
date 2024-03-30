#include <iostream>

#include "run.h"
#include "readCSV.h"
#include "UI.h"

sf::RenderWindow window(sf::VideoMode(1280, 720), "Course Management", sf::Style::Close);
sf::Event event;
const float xMid = window.getSize().x / 2.0f;
const float yMid = window.getSize().y / 2.0f;
int page = 0;
int yearPage = 0;

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
// Button in Schoolyear page
Button rYearPageButton(502.5f, 625.0f, "image/RightPageButton.png");
Button lYearPageButton(122.5f, 625.0f, "image/LeftPageButton.png");
Button addYearButton(1100.0f, 205.0f, "image/AddYear.png");
InputYear inputYear(825.0f, 205.0f, "image/InputYear.png", "School year:");
Line yearLine(575.0f, 157.5f, 1.0f, 435.0f);
TextBox semesterBox(775.0f, 305.0f, "image/ViewSeme.png", "");

//Stu account
Button profileStu(207.0f, 185.0f, "image/ProfileStu.png");

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
            viewingPage.text.setString("Viewing school years");
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                inputYear.isClicked(event, window); // Input school year
                // Add school year
                if (addYearButton.isClicked(window, event)) {
                    schoolyearArr = loadAddSchoolyear(schoolyearArr, numSchoolYear);
                    schoolyearArr[numSchoolYear - 1].period = inputYear.text.getString();
                    schoolyearButton = loadAddYearButton(schoolyearArr, schoolyearButton, numSchoolYear);
                    inputYear.text.setString("");
                }
                if (backButton.isClicked(window,event)) {
                    page = 10;
                    break;
                }
                if (rYearPageButton.isClicked(window, event)) {
                    // If page is not the last page
                    if (yearPage < numSchoolYear / 14) yearPage++;
                }
                if (lYearPageButton.isClicked(window, event)) {
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
            }

            //Draw
            viewingPage.draw(window);
            backButton.draw(window);
            rYearPageButton.draw(window);
            lYearPageButton.draw(window);
            int i = yearPage * 14;
            for (i ; i < (yearPage + 1) * 14 && i < numSchoolYear; ++i)
                schoolyearButton[i]->draw(window);
            inputYear.draw(window);
            addYearButton.draw(window);
            yearLine.draw(window);
            if (user.indexSchoolyear != -1) {
                semesterBox.text.setString(schoolyearArr[user.indexSchoolyear].period);
                semesterBox.draw(window);
                int size = schoolyearArr[user.indexSchoolyear].numSemester;
                for (int i = 0; i < size; ++i)
                    schoolyearButton[user.indexSchoolyear]->linkedButton[i]->draw(window);
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
            float x2 = 875.0f, y2 = 370.0f;
            for (int j = 0; j < schoolyearArr[i].numSemester; j++) {
                schoolyearButton[i]->linkedButton[j] = new LinkedButton(x2, y2, "image/Button400x45.png", "Semester " + to_string(j + 1));
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