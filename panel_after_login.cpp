//
//  panel_after_login.cpp
//  login_system_CS162
//
//  Created by Le Hoang An on 12/3/24.
//

#include "panel_after_login.hpp"
void idle_login_panel(int rank, bool &exit, Student *student[], Staff *staff[], int ID)
{
    bool logout = false;
    while (logout == false)
    {
        int command;
        cout << "1. profile\n2. logout\n3.exit\n" << "input command: "; cin >> command;
        if (command == 1)
        {
            logout = true;
            return;
        }
        if (command == 2)
        {
            if (rank == 1)
            {
                
                cout << student[ID] -> Student_ID << endl;
                cout << student[ID] -> Year_Studied << endl;
                cout << student[ID] -> Password << endl;
                cout << student[ID] -> LastName << endl;
                cout << student[ID] -> FirstName << endl;
                cout << student[ID] -> FemaleGender << endl;
                cout << student[ID] -> DD << endl;
                cout << student[ID] -> MM << endl;
                cout << student[ID] -> YY << endl;
                cout << student[ID] -> Social_ID << endl;
                cout << student[ID] -> Class_ID << endl;
                
            }
            else if (rank == 2)
            {
                cout << staff[ID] -> Staff_ID << endl;
                cout << student[ID] -> Password << endl;
                cout << student[ID] -> LastName << endl;
                cout << student[ID] -> FirstName << endl;
            }
        }
        else if (command == 3)
        {
            exit = true;
            return;
        }
    }
    
}
