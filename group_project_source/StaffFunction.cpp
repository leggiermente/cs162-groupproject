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
        getline(inp,str,',');
        getline(inp,str,','); //in each line
        tmpClass->listStudent[i].studentID=stoi(str); //student id, first name, last name, sexuality, dob, social id, password
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
        getline(inp,str,',');
        tmpClass->listStudent[i].socialID=stoi(str);
        getline(inp,str,',');
        tmpClass->listStudent[i].password=str;
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
void outputClass(string fileName,Class curClass){
    ofstream out;
    string str;
    out.open(fileName);
    out << curClass.yearStudied << endl;
    out << curClass.numStudent << endl;
    for (int i=0;i<curClass.numStudent;i++){
        Student curStudent=curClass.listStudent[i];
        out << curStudent.studentID << "," << curStudent.firstName << "," << curStudent.lastName << "," << ((curStudent.femaleGender)? 1: 0);
        out << "," << curStudent.DD << "," << curStudent.MM << "," << curStudent.YY << "," << curStudent.socialID << "," << curStudent.password;
        out << endl;
    }
    out.close();
}
void outputSchoolYear(schoolYear &schyrs){
    ofstream out;
    string str;
    out.open("../database/schoolyear.txt");
    out << schyrs.period << endl;
    out << schyrs.classCount << endl;
    for (int i=0;i<schyrs.classCount;i++){
        out << schyrs.classList[i].classID << endl;
    }
    out.close();
}
