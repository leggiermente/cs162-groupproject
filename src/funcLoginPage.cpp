#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#include "funcLoginPage.h"
#include "run.h"

Student* readStudentCSV(string filename, int& numStu) {
    ifstream file(filename);
    string line;

    // Get the row of the csv file
    numStu = 0;
    while (getline(file, line))
        numStu++;

    //Reset file
    file.clear();
    file.seekg(0, ios::beg);

    //Create array for students
    Student* newStudent = new Student[numStu];

    //Store data to a array
    int indexStu = 0;
    while (getline(file, line)) {
        stringstream s(line);

        //Pass No data in CSV
        getline(s, line, ',');
        getline(s, line, ',');
        newStudent[indexStu].Student_ID = stoi(line);
        getline(s, line, ',');
        newStudent[indexStu].FirstName = line;
        getline(s, line, ',');
        newStudent[indexStu].LastName = line;
        getline(s, line, ',');
        newStudent[indexStu].FemaleGender = stoi(line);
        getline(s, line, ',');
        newStudent[indexStu].DD = stoi(line);
        getline(s, line, ',');
        newStudent[indexStu].MM = stoi(line);
        getline(s, line, ',');
        newStudent[indexStu].YY = stoi(line);
        getline(s, line, ',');
        newStudent[indexStu].Social_ID = stoi(line);

        //Auto generate password = 1
        newStudent[indexStu].Password = "1";
        indexStu++;
    }
    file.close();
    return newStudent;
}
Staff* readStaffCSV(string filename, int& numStaff) {
    ifstream file(filename);
    string line;

    // Get the row of the csv file
    numStaff = 0;
    while (getline(file, line))
        numStaff++;

    //Reset file
    file.clear();
    file.seekg(0, ios::beg);

    //Create array for students
    Staff* newStaff = new Staff[numStaff];

    //Store data to a array
    int indexStaff = 0;
    while (getline(file, line)) {
        stringstream s(line);

        //Pass No data in CSV
        getline(s, line, ',');
        getline(s, line, ',');
        newStaff[indexStaff].Staff_ID = stoi(line);
        getline(s, line, ',');
        newStaff[indexStaff].FirstName = line;
        getline(s, line, ',');
        newStaff[indexStaff].LastName = line;

        //Auto generate password = 1
        newStaff[indexStaff].Password = "1";
        indexStaff++;
    }
    file.close();
    return newStaff;
}
