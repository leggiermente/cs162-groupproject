//
//  login_and_ logout.cpp
//  login_system_CS162
//
//  Created by Le Hoang An on 11/3/24.
//

#include "login_and_ logout.hpp"
bool login_and_logout(student[], int numStu, staff[) //student.student_ID student.Password
{
    bool logged_in = false;
    string username, password, usr, pwd;
    while (!logged_in)
    {
        cout << "input username and password" << endl;
        cout << "username: "; cin >> username;
        cout << "password: "; cin >> password;
        int i = 0;
        while (student[i].studentID != username && i < numStu)
        {
            ++i;
        }
        if (student[i].Password != password)
        {
            cout << "failed login" << endl;
        }
        else
        {
            cout << "logged in" << endl;
        }
    }
}
