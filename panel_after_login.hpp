#ifndef panel_after_login_hpp
#define panel_after_login_hpp

#include <stdio.h>
#include <iostream>
#include "Student.h"
#include "Staff.h"

using namespace std;
void idle_login_panel(int rank, bool &exit, Student *student, Staff *staff, int ID);
#endif /* panel_after_login_hpp */