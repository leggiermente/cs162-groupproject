#include <windows.h>
#include <iostream>
#include <fstream>
using namespace std;
#include "Staff.h"
#include "Student.h"
Class readClass(string fileName,string nameClass){
    ifstream inp;
    string str;
    inp.open(fileName);
    Class *tmpClass=new Class; //class file format
    tmpClass->classID=nameClass;
    inp >> tmpClass->yearStudied; //year studied in this class
    inp >> tmpClass->numStudent; //number of students in this class
    if (tmpClass->numStudent>0) tmpClass->listStudent=new Student[tmpClass->numStudent];
    else tmpClass->listStudent=nullptr;
    inp.get();
    for (int i=0;i<tmpClass->numStudent;i++){
        getline(inp,str,','); //in each line
        tmpClass->listStudent[i].studentID=stoi(str); //student id, first name, last name, sexuality, dob, social id
        getline(inp,str,',');
        tmpClass->listStudent[i].firstName=str;
        getline(inp,str,',');
        tmpClass->listStudent[i].lastName=str;
        getline(inp,str,',');
        tmpClass->listStudent[i].femaleGender=stoi(str);
        getline(inp,str,',');
        tmpClass->listStudent[i].DD=stoi(str);
        getline(inp,str,',');
        tmpClass->listStudent[i].MM=stoi(str);
        getline(inp,str,',');
        tmpClass->listStudent[i].YY=stoi(str);
        getline(inp,str,'\n');
        tmpClass->listStudent[i].socialID=stoi(str);
    }
    inp.close();
    return *tmpClass;
}
schoolYear importSchoolYear(){
    schoolYear schyrs;
    ifstream inp;
    inp.open("../database/schoolyear.txt"); //open the data of the class in the school year.
    if (!inp.is_open()){
        inp.close();
        return {}; //there's no data of the current school year that needs to make new school year.
    }
    string str; //string for getting the input file, needs to also implement schoolyear.txt, involving name of the class of the last school year.
    getline(inp,str); // getting the period of the school year
    schyrs.period=str;
    inp >> schyrs.classCount;
    getline(inp,str);
    schyrs.classList=new Class[schyrs.classCount]; //make a dynamic allocated array for class in a school year.
    for (int i=0;i<schyrs.classCount;i++){
        getline(inp,str);
        schyrs.classList[i].classID=str; //getting the class ID.
    }
    inp.close();
    for (int i=0;i<schyrs.classCount;i++){
        Class curClass=schyrs.classList[i];
        string directory="../database/class/"+curClass.classID+".txt";
        schyrs.classList[i]=readClass(directory,curClass.classID); //read class from the database.
    }
    return schyrs;
}
void updateStudentFromInput(Class &curClass){
    system("CLS");
    string str;
    cout << "Please input number of students: ";
    cin >> curClass.numStudent;
    cin.get();
    curClass.listStudent=new Student[curClass.numStudent];
    for (int i=0;i<curClass.numStudent;i++){ //in each line
        system("CLS");
        cout << "Please input student ID of student " << i+1 << ": ";
        getline(cin,str);
        curClass.listStudent[i].studentID=stoi(str); //student id, first name, last name, sexuality, dob, social id
        cout << "Please input first name of student " << i+1 << ": ";
        getline(cin,str);
        curClass.listStudent[i].firstName=str;
        cout << "Please input last name of student " << i+1 << ": ";
        getline(cin,str);
        curClass.listStudent[i].lastName=str;
        cout << "Please input state of gender of student " << i+1 << " (1 for female, 0 for male): ";
        getline(cin,str);
        curClass.listStudent[i].femaleGender=stoi(str);
        cout << "Please input day of birth of student " << i+1 << ": ";
        getline(cin,str);
        curClass.listStudent[i].DD=stoi(str);
        cout << "Please input month of birth of student " << i+1 << ": ";
        getline(cin,str);
        curClass.listStudent[i].MM=stoi(str);
        cout << "Please input year of birth of student " << i+1 << ": ";
        getline(cin,str);
        curClass.listStudent[i].YY=stoi(str);
        cout << "Please input social ID of student " << i+1 << ": ";
        getline(cin,str);
        curClass.listStudent[i].socialID=stoi(str);
    }
}
void addNewSchoolYear(int &sems, schoolYear schyrs, bool &createClassOption){
    if (sems!=3){ //Check if it's the last semester of last year.
        system("CLS");
        cout << "You cannot add a new school year, as this time is not the last semester of the last year." << endl;
        Sleep(3000);
        system("CLS");
        return; //if not, don't add new school year.
    }
    for (int i=0;i<schyrs.classCount;i++){
        Class curClass=schyrs.classList[i];
        curClass.yearStudied++; //increase year studied of a class.
        outputClass("../database/class/"+curClass.classID+".txt",curClass); //Output class to the database.
    }
    system("CLS");
    cout << "Please input the period of the new school year below: " << endl;
    getline(cin,schyrs.period);
    sems=1;
    outputSchoolYear(schyrs);
    createClassOption=true; //allow staff to create class in the menu.
    system("CLS");
}
Student *readStudentCSV(string filename, int& numStu){
}
void addStudentintoClass(schoolYear &schyrs, bool createClassOption){
    system("CLS");
    if (!createClassOption){ //check if already new school year
        cout << "You must create a new school year to add a new student into class." << endl;
        Sleep(3000);
        return;
    }
    int numEligibleClass=0;
    for (int i=0;i<schyrs.classCount;i++){
        if (schyrs.classList[i].yearStudied==1){
            numEligibleClass++;
        }
    }
    if (numEligibleClass==0){ //check if there are 1-st year classes to add
        cout << "There are no 1-st year classes to add new student." << endl;
        Sleep(3000);
        return;
    }
    cout << "Please choose following list of class below by inputting from keyboard: " << endl;
    int* lst=new int[numEligibleClass],cnt=0; //lst for ID list of class of 1-st year classes.
    for (int i=0;i<schyrs.classCount;i++){
        if (schyrs.classList[i].yearStudied==1){
            cout << cnt+1 << ": " << schyrs.classList[i].classID << "." << endl;
            lst[cnt++]=i;
        }
    }
    int id=0; //return the position of the class you want to update
    do{
        cin >> id;
        if (id<=0 || id>numEligibleClass){
            cout << "Please input again in this line: ";
        }
    }
    while (id<=0 || id>numEligibleClass);
    id=lst[id-1];
    system("CLS");
    cout << "Please choose an option for updating new student to the class." << endl;
    int options=0; //variable to check for the option
    cout << "1: Input students directly." << endl;
    cout << "2: Input students from file student.csv (import from /import/student.csv)" << endl;
    do{
        cin >> options;
        if (options!=1 && options!=2){
            cout << "Please input again in this line: ";
        }
    }
    while (options!=1 && options!=2);
    if (options==1){
        updateStudentFromInput(schyrs.classList[id]); //implement from above function
    }
    else{
        schyrs.classList[id].listStudent=readStudentCSV("../import/student.csv", schyrs.classList[id].numStudent); //work of izahai
    }
    outputClass("../database/class/"+schyrs.classList[id].classID+".txt",schyrs.classList[id]);
    delete []lst;
}
void outputClass(string fileName,Class curClass){
    ofstream out;
    string str;
    out.open(fileName);
    out << curClass.yearStudied << endl;
    out << curClass.numStudent << endl;
    for (int i=0;i<curClass.numStudent;i++){
        Student curStudent=curClass.listStudent[i];
        out << curStudent.studentID << "," << curStudent.firstName << "," << curStudent.lastName << "," << ((curStudent.femaleGender)? 1: 0);
        out << "," << curStudent.DD << "," << curStudent.MM << "," << curStudent.YY << "," << curStudent.socialID;
        out << endl;
    }
    out.close();
    system("CLS");
    cout << curClass.yearStudied << endl;
    cout << curClass.numStudent << endl;
    for (int i=0;i<curClass.numStudent;i++){
        Student curStudent=curClass.listStudent[i];
        cout << curStudent.studentID << "," << curStudent.firstName << "," << curStudent.lastName << "," << ((curStudent.femaleGender)? 1: 0);
        cout << "," << curStudent.DD << "," << curStudent.MM << "," << curStudent.YY << "," << curStudent.socialID;
        cout << endl;
    }
}
void outputSchoolYear(schoolYear &schyrs){
    ofstream out;
    string str;
    out.open("../database/schoolyear.txt"); //output the period, number of classes, and list of classes.
    out << schyrs.period << endl;
    out << schyrs.classCount << endl;
    for (int i=0;i<schyrs.classCount;i++){
        out << schyrs.classList[i].classID << endl;
    }
    out.close();
}
