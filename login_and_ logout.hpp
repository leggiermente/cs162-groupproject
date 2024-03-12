//
//  login_and_ logout.hpp
//  login_system_CS162
//
//  Created by Le Hoang An on 11/3/24.
//

#ifndef login_and__logout_hpp
#define login_and__logout_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

#include "Staff.h"
#include "Student.h"
using namespace std;
bool login_and_logout(Student *student[], int numStu, Staff *staff[], int numStaf, int &rank, int &ID);
#endif /* login_and__logout_hpp */
