#include "Struct.h"
#ifndef STAFF_H_INCLUDED
#define STAFF_H_INCLUDED
struct Staff;
struct Staff {
    int staffID;
    string password;
    string firstName, lastName;
};
//schoolYear importSchoolYear();
//Class readClass(string fileName, string nameClass);
//Student* readStudentCSV(string filename, int& numStu);
//void updateStudentFromInput(Class& curClass);
//void addNewSchoolYear(int& sems, schoolYear schyrs, bool& createClassOption);
//void addStudentintoClass(schoolYear& schyrs, bool createClassOption);
//void outputClass(string fileName, Class curClass);
//void outputSchoolYear(schoolYear& schyrs);
#endif // STAFF_H_INCLU