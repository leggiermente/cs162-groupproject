#include "Struct.h"
#ifndef STAFF_H_INCLUDED
#define STAFF_H_INCLUDED
struct Staff;
struct Staff{
    int Staff_ID;
    string Password;
    string FirstName,LastName;
};
bool ImportSchoolYear(School_Year &schyrs);
void AddNewSchoolYear(int &sems, School_Year &schyrs, bool &CreateClassOption);
Class ReadClass(string filename);
void OutputClass(string filename);
#endif // STAFF_H_INCLUDED
