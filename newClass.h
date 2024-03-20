
#ifndef newClass_h
#define newClass_h

#include "Student.h"
#include "Staff.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int countLine (string filename);
void loadClassFromFile(string &filename, schoolYear &targetSchoolYear);
void createNewClassToFile(string &filename);
void updateFileSchoolYear ( string &filename, schoolYear& targetSchoolYear);

#endif /* newClass_h */
