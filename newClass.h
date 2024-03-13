
#ifndef newClass_h
#define newClass_h

#include "Student.h"
#include "Staff.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
using namespace std;

int countLine (string filename);
void createNewClass(string& filename);
void updateClassListOfSchoolYear ( string &filename, School_Year& targetSchoolYear);

#endif /* newClass_h */
