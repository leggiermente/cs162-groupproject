
#ifndef newClass_h
#define newClass_h

#include "Student.h"
#include "Staff.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
using namespace std;

void createNewClass(School_Year& targetSchoolYear, int &numClass);
void updateSchoolYearCSV ( string &filename, School_Year& targetSchoolYear, int &numClass);

#endif /* newClass_h */
