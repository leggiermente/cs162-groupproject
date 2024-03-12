#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include "functions.h"
#include "Student.h"
#include "Staff.h"

int main()
{
    //Demo
    int numStu = 0; //If it is allocated array I can't use sizeof(array)/sizeof(array[0])
    Student* tmp = readStudentCSV("students.csv", numStu);

    //cout << size;
    for (int i = 0; i < numStu; i++) {
        cout << tmp[i].Student_ID << endl;
        cout << tmp[i].FirstName << " "<< tmp[i].LastName << endl;
        cout << tmp[i].FemaleGender << endl;
        cout << tmp[i].DD << "-" << tmp[i].MM << "-" << tmp[i].YY << endl;
        cout << tmp[i].Social_ID << endl;
        cout << tmp[i].Password << endl;
        cout << endl;
    }
    return 0;
}

