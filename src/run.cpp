#include <iostream>

#include "run.h"
#include "funcLoginPage.h"
#include "UI.h"

sf::RenderWindow window(sf::VideoMode(1280, 720), "Course Management", sf::Style::Close);
sf::Event event;
const float xMid = window.getSize().x / 2.0f;
const float yMid = window.getSize().y / 2.0f;
int page = 0;

UsernameBox inputUserBox(xMid, yMid - 50.0f);
PasswordBox inputPassBox(xMid, yMid + 51.0f);
LoginButton loginButton(xMid, yMid + 205.0f, "image/SignIn.png");
DeleteButton deleteButton(xMid, yMid, "image/delete.png");
LoginBox loginBox(xMid, yMid, "image/LoginBox.png");
CheckStaffButton checkStaffButton(xMid - 285.0f, yMid + 110.0f, "image/CheckStaffButton.png", "image/CheckedStaffButton.png");
LeftHome lefthome(152.0f, yMid, "image/LeftHome.png");

std::string Sid = "";
std::string Spassword = "";

int numStu = 0;
int numStaff = 0;
Student* stuArr = readStudentCSV("student.csv", numStu);
Staff* staffArr = readStaffCSV("staff.csv", numStaff);

CurrentUser user;

void RunApp() 
{
    window.setFramerateLimit(60);
    while (window.isOpen()) 
    {
        switch (page)
        {
        case 0: // Login Page
        {
            // Read input from mouse and keyboard
            while (window.pollEvent(event))
            {

                if (event.type == sf::Event::Closed)
                    window.close();
                inputUserBox.handleEvent(event, window);
                inputPassBox.handleEvent(event, window);
                deleteButton.isClicked(window, inputUserBox.text, inputPassBox.text, inputPassBox.star);
                if (checkStaffButton.isClick(window, user.isStaff));

                if (loginButton.isClicked(window, inputUserBox.text, inputPassBox.text, Sid, Spassword)) {
                    if (validateUser())
                        page = 1;
                    else {
                        inputUserBox.text.setString("");
                        inputPassBox.text.setString("");
                        inputPassBox.star.setString("");
                    }

                }
                // Draw Element 
                window.clear(sf::Color(221, 230, 237)); // Light Blue Grey
                loginBox.draw(window);
                loginButton.draw(window);
                inputUserBox.draw(window);
                inputPassBox.draw(window);
                checkStaffButton.draw(window, user.isStaff);
                deleteButton.draw(window);                   
                window.display();
            }
            
            break;
        }
        case 1: // Account menu page
        {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear(sf::Color(221, 230, 237)); // Light Blue Grey
            lefthome.draw(window);
            window.display();
            break;
        }
        default:
            break;
        }
    }
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
            if (Iid == staffArr[i].Staff_ID && Spassword == staffArr[i].Password) {
                user.isLogin = 1;
                user.staff = staffArr[i];
                return 1;
            }
        }
    }
    else {
        for (int i = 0; i < numStu; ++i) {
            if (Iid == stuArr[i].Student_ID && Spassword == stuArr[i].Password) {
                user.isLogin = 1;
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