//
//  panel_after_login.cpp
//  login_system_CS162
//
//  Created by Le Hoang An on 12/3/24.
//

#include "panel_after_login.hpp"
void idle_login_panel()
{
    bool logout = false;
    while (logout == false)
    {
        int command;
        cout << "1. profile\n" << "2. logout\n" << "input command: "; cin >> command;
        if (command == 1)
        {
            logout = true;
            return;
        }
    }
}
