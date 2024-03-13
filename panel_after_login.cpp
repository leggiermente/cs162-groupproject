#include "panel_after_login.hpp"
void idle_login_panel(int rank, bool &exit, Student *student, Staff *staff, int ID)
{
    bool logout = false;
    while (logout == false)
    {
        int command;
        cout << "1. profile\n2. logout\n3.exit\n" << "input command: "; cin >> command;
        while (command)
        {
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
                    
                    cout << "ID: " << student[ID] . Student_ID << endl;
                    cout << "Year Studied" << student[ID] . Year_Studied << endl;
                    cout << "Password: " << student[ID] . Password << endl;
                    cout << "LastName: " << student[ID] . LastName << endl;
                    cout << "FirstName" << student[ID] . FirstName << endl;
                    cout << "Female: " << student[ID] . FemaleGender << endl;
                    cout << "DD: " << student[ID] . DD << endl;
                    cout << "MM: " << student[ID] . MM << endl;
                    cout << "YY: " << student[ID] . YY << endl;
                    cout << "Social ID: " << student[ID] . Social_ID << endl;
                    cout << "Class: " << student[ID] . Class_ID << endl;
                    
                }
                else if (rank == 2)
                {
                    cout << "ID: " << staff[ID] . Staff_ID << endl;
                    cout << "Password: " << staff[ID] . Password << endl;
                    cout << "LastName: " << staff[ID] . LastName << endl;
                    cout << "FirstName: " << staff[ID] . FirstName << endl;
                }
            }
            else if (command == 3)
            {
                exit = true;
                return;
            }
        }
    }
    
}
