//
//  login.h
//  login_system_CS162
//
//  Created by Le Hoang An on 12/3/24.
//

#ifndef login_h
#define login_h

#include "login_and_ logout.hpp"
#include "panel_after_login.hpp"
#include "Student.h"
#include "Staff.h"
struct login_logout
{
    int rank; int ID;
    void login_stuff(Student *student[], int numStu, Staff *staff[], int numStaf, int rank);
};
void login_logout::login_stuff(Student *student[], int numStu, Staff *staff[], int numStaf, int rank)
{
    bool exit = false;
    while (exit != true)
    {
        bool logged_in = login(student, numStu, staff, numStaf, rank, ID);
        if (logged_in)
        {
            idle_login_panel(rank, exit, student, staff, ID);
        }
    }
}
#endif /* login_h */
