#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#include "readCSV.h"
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
        newStudent[indexStu].studentID = stoi(line);
        getline(s, line, ',');
        newStudent[indexStu].firstName = line;
        getline(s, line, ',');
        newStudent[indexStu].lastName = line;
        getline(s, line, ',');
        newStudent[indexStu].femaleGender = stoi(line);
        getline(s, line, ',');
        newStudent[indexStu].DD = stoi(line);
        getline(s, line, ',');
        newStudent[indexStu].MM = stoi(line);
        getline(s, line, ',');
        newStudent[indexStu].YY = stoi(line);
        getline(s, line, ',');
        newStudent[indexStu].socialID = stoi(line);

        //Auto generate password = 1
        newStudent[indexStu].password = "1";
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
        newStaff[indexStaff].staffID = stoi(line);
        getline(s, line, ',');
        newStaff[indexStaff].firstName = line;
        getline(s, line, ',');
        newStaff[indexStaff].lastName = line;

        //Auto generate password = 1
        newStaff[indexStaff].password = "1";
        indexStaff++;
    }
    file.close();
    return newStaff;
}
Course* readDirectory(string path, int& numCourse) {
    string line;
    ifstream file(path + "/course.txt");
    if (!file) cout << "Can't open file\n";

    getline(file, line);
    numCourse = stoi(line);

    Course* course = new Course[numCourse];
    for (int i = 0; i < numCourse; i++) {
        getline(file, line);
        course[i].ID = line;
    }
    file.close();

    for (int i = 0; i < numCourse; ++i) {
        ifstream file(path + "/" + course[i].ID + ".csv");
        if (!file) cout << "Can't open file\n";
        
        file.seekg(0, ios::beg);
        getline(file, line);
        stringstream s(line);
        getline(s, line, ',');
        getline(s, line, ','); course[i].courseName = line;
        getline(s, line, ','); course[i].className = line;
        getline(s, line, ','); course[i].teacher = line;
        getline(s, line, ','); course[i].numCredits = stoi(line);
        getline(s, line, ','); course[i].maxStudents = stoi(line);
    }
    return course;
}