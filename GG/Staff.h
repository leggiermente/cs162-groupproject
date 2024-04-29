#include "Struct.h"
#ifndef STAFF_H_INCLUDED
#define STAFF_H_INCLUDED
struct Staff;
struct Staff {
    string staffID = "";
    string firstName = "";
    string lastName = "";
    string socialID = "";
    bool gender = false;
    string dob = "";
    string password = "";
};
#endif // STAFF_H_INCLU