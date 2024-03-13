#include <windows.h>
#include <iostream>
#include <fstream>
using namespace std;
#include "Staff.h"
#include "Student.h"
Class ReadClass(string filename){
    return {};
}
bool ImportSchoolYear(School_Year &schyrs){
    ifstream inp;
    inp.open("../database/schoolyear.txt"); //open the data of the class in the school year.
    if (!inp.is_open()){
        inp.close();
        return false; //there's no data of the current school year that needs to make new school year.
    }
    string str; //string for getting the input file, needs to also implement schoolyear.txt, involving name of the class of the last school year.
    getline(inp,str); // getting the period of the school year
    schyrs.Period=str;
    inp >> schyrs.ClassCount;
    inp.get();
    schyrs.ClassList=new Class[schyrs.ClassCount]; //make a dynamic allocated array for class in a school year.
    for (int i=0;i<schyrs.ClassCount;i++){
        getline(inp,str);
        schyrs.ClassList[i].Class_ID=str; //getting the class ID.
    }
    inp.close();
    for (int i=0;i<schyrs.ClassCount;i++){
        Class curClass=schyrs.ClassList[i];
        string directory="../database/class/"+curClass.Class_ID+".txt";
        curClass=ReadClass(directory); //Read Class function, merge from the work of izahai after everything's done.
        inp.close();
    }
    return true;
}
void AddNewSchoolYear(int &sems, School_Year &schyrs, bool &CreateClassOption){
    if (sems!=3){ //Check if it's the last semester of last year.
        system("CLS");
        cout << "You cannot add a new school year, as this time is not the last semester of the last year." << endl;
        Sleep(3000);
        system("CLS");
        return; //if not, don't add new school year.
    }
    ofstream out;
    for (int i=0;i<schyrs.ClassCount;i++){
        Class curClass=schyrs.ClassList[i];
        curClass.Year_Studied++; //increase year studied of a class.
        OutputClass("../database/class/"+curClass.Class_ID+".txt"); //Output class to the database, merge from izahai after everything's done.
    }
    system("CLS");
    cout << "Please input the period of the new school year below: " << endl;
    getline(cin,schyrs.Period);
    sems=1;
    CreateClassOption=true; //allow staff to create class option in the menu.
    system("CLS");
}
void OutputClass(string filename){
}
