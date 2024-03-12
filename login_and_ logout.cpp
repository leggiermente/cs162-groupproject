//
//  login_and_ logout.cpp
//  login_system_CS162
//
//  Created by Le Hoang An on 11/3/24.
//

#include "login_and_ logout.hpp"
bool login(Student *student, int numStu, Staff *staff, int numStaf, int &rank, int &ID) //student.student_ID student.Password
{
    bool logged_in = false;
    int username; string password;
    while (!logged_in)
    {
        cout << "1. student\n2. staff\ninput here: "; cin >> rank;
        cout << "input username and password" << endl;
        cout << "username: "; cin >> username;
        cout << "password: "; cin >> password;
        int i = 0;
        if (rank)
        {
            while (i < numStu)
            {
                if (student[i].Student_ID == username)
                {
                    break;
                }
                ++i;
            }
            if (i == numStu)
                cout << "incorrect username" << endl;
            else
            {
                if (student[i].Password == password)
                {
                    student[i] . Student_ID = ID;
                    logged_in = true;
                    break;
                }
                else
                {
                    cout << "incorrect password" << endl;
                }
            }
        }
        else
        {
            while (i < numStaf)
            {
                if (staff[i] . Staff_ID == username)
                {
                    staff[i] . Staff_ID = ID;
                    logged_in = true;
                    break;
                }
                ++i;
            }
            if (i == numStaf)
                cout << "incorrect username" << endl;
            else
            {
                if (staff[i] . Password == password)
                {
                    logged_in = true;
                    break;
                }
                else
                {
                    cout << "incorrect password" << endl;
                }
            }
        }
    }
    cout << "logged in" << endl;
    return logged_in;
}
