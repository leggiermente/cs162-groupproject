

#ifndef login_and__logout_hpp
#define login_and__logout_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

#include "Staff.h"
#include "Student.h"
using namespace std;
bool login(Student *student[], int numStu, Staff *staff[], int numStaf, int &rank, int &ID);
#endif /* login_and__logout_hpp */
