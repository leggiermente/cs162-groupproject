#ifndef STAFF_H_INCLUDED
#define STAFF_H_INCLUDED
#include <string>
using namespace std;
struct Staff;
struct Staff {
    int Staff_ID;
    string Password;
    string FirstName, LastName;
};
#endif // STAFF_H_INCLUDED