#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include "Student.h"
#include "Staff.h"
#include "functions.h"

Student *readStudentCSV(string filename, int& numStu) {
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

        //Auto generate password
        string id = to_string(newStudent[indexStu].Student_ID);
        string social = to_string(newStudent[indexStu].Social_ID);
        
        newStudent[indexStu].Password = id.substr(0, 4) + social.substr(social.length() - 4, 4);
        
        indexStu++;
    }
    file.close();
    return newStudent;
}
