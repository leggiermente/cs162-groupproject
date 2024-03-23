#include <windows.h>
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#include "Staff.h"
#include "Struct.h"
#include "Student.h"
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
Student *readStudentCSV(string fileName, int& numStu){ //merge from the work of izahai

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
void ImportStudentsToCoursesInSemester(Student *students, int numStu, Course thisCourse){ //merge from the work of lehoangan02

}
void addNewSchoolYear(int &sems, schoolYear schyrs, bool &createClassOption){
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
void importSemesterandCourse(Semester &sems){ //not done delete pointer yet
    ifstream inp;
    inp.open("../database/semester.txt");
    inp >> sems.numSemesterInSchoolYear;
    inp >> sems.startDate >> sems.startMonth >> sems.startYear;
    inp >> sems.endDate >> sems.endMonth >> sems.endYear;
    inp >> sems.numCourses;
    inp.get();
    sems.coursesListInSemester=new Course[sems.numCourses];
    for (int i=0;i<sems.numCourses;i++){
        getline(inp,sems.coursesListInSemester[i].ID);
    }
    inp.close();
    for (int i=0;i<sems.numCourses;i++){
        inp.open("../database/course/"+sems.coursesListInSemester[i].ID+".txt");
        getline(inp,sems.coursesListInSemester[i].ID);
        getline(inp,sems.coursesListInSemester[i].courseName);
        getline(inp,sems.coursesListInSemester[i].className);
        getline(inp,sems.coursesListInSemester[i].teacher);
        inp >> sems.coursesListInSemester[i].numCredits;
        inp >> sems.coursesListInSemester[i].maxStudents;
        inp.get();
        getline(inp,sems.coursesListInSemester[i].dayoftheWeek);
        getline(inp,sems.coursesListInSemester[i].sessionTime);
        inp >> sems.coursesListInSemester[i].numStudents;
        inp.get();
        for (int j=0;j<sems.coursesListInSemester[i].numStudents;j++){
            inp >> sems.coursesListInSemester[i].listStudentInCourse[j].studentID;
        }
        inp.close();
    }
}
void addCourse(Semester &sems){
    Course* tmp=sems.coursesListInSemester;
    sems.numCourses++;
    sems.coursesListInSemester=new Course[sems.numCourses]; //update the size of dynamic allocated array to add a new course
    for (int i=0;i<sems.numCourses-1;i++){
        sems.coursesListInSemester[i]=tmp[i];
    }
    int curPos=sems.numCourses-1;
    cout << "Please input the course id: "; //input information of a course
    getline(cin,sems.coursesListInSemester[curPos].ID);
    cout << "Please input the course name: ";
    getline(cin,sems.coursesListInSemester[curPos].courseName);
    cout << "Please input the class name: ";
    getline(cin,sems.coursesListInSemester[curPos].className);
    cout << "Please input the teacher name: ";
    getline(cin,sems.coursesListInSemester[curPos].teacher);
    cout << "Please input the number of credits in this course: ";
    cin >> sems.coursesListInSemester[curPos].numCredits;
    cout << "Please input the maximum of students in the class (default is 50): ";
    cin >> sems.coursesListInSemester[curPos].maxStudents;
    cin.get();
    cout << "Please input day of the week, following format (can be uppercase and lowercase): " << endl; //day of the week process
    cout << "MON | TUE | WED | THU | FRI | SAT" << endl;
    while (getline(cin,sems.coursesListInSemester[curPos].dayoftheWeek) &&
           !checkFormatDayOfTheWeek(sems.coursesListInSemester[curPos].dayoftheWeek)){
        cout << "Invalid input! Please try again in this line: ";
    }
    for (int i=0;i<sems.coursesListInSemester[curPos].dayoftheWeek.size();i++){
        sems.coursesListInSemester[curPos].dayoftheWeek[i]=toupper(sems.coursesListInSemester[curPos].dayoftheWeek[i]);
    }
    cout << "Please input the session, follows the following format (must be uppercase): "; //session process
    cout << "S1 | S2 | S3 | S4" << endl;
    cout << "Note: S1 (7:30), S2(9:30), S3(13:30), S4(15:30)" << endl;
    while (getline(cin,sems.coursesListInSemester[curPos].sessionTime) &&
           !checkFormatSession(sems.coursesListInSemester[curPos].sessionTime)){
        cout << "Invalid input! Please try again in this line: ";
    }
    ImportStudentsToCoursesInSemester(sems.coursesListInSemester[curPos].listStudentInCourse,sems.coursesListInSemester[curPos].numStudents,
                                      sems.coursesListInSemester[curPos]); //import student.csv, merge later from the work of lehoangan02
    outputSemester(sems);
    outputCourse("../database/course/"+sems.coursesListInSemester[curPos].ID+".txt",sems.coursesListInSemester[curPos]);
}
void removeCourse(Semester &sems){
    if (sems.numCourses==0){
        cout << "You don't have any classes to remove." << endl;
        Sleep(3000);
        return;
    }
    cout << "Please choose a course to remove: " << endl;
    for (int i=0;i<sems.numCourses;i++){
        cout << i+1 << ": " << sems.coursesListInSemester[i].ID << endl;
    }
    cout << "Please input a number to delete at this line: ";
    int command=0;
    while (cin >> command && (command<=0 || command>sems.numCourses)){
        cout << "Invalid input! Please try again at this line: ";
    }
    command--;
    //this line is left for the delete of information at the file that which student learns the course at this semester.
    string tmpdir="../database/course/"+sems.coursesListInSemester[command].ID+".txt";
    int dirsize=tmpdir.size()+1;
    char dir[dirsize]="";
    for (int i=0;i<dirsize-1;i++) dir[i]=tmpdir[i];
    dir[dirsize-1]=0;
    remove(dir);
    sems.numCourses--;
    if (sems.numCourses==0){
        sems.coursesListInSemester=nullptr;
    }
    else{
        Course *tmp=new Course[sems.numCourses];
        int add=0;
        for (int i=0;i<sems.numCourses+1;i++){
            if (i!=command){
                tmp[add++]=sems.coursesListInSemester[i];
            }
        }
        //this line is left for the delete of old course list.
        sems.coursesListInSemester=tmp;
    }
    outputSemester(sems);
}
void outputSemester(Semester sems){
    ofstream out;
    out.open("../database/semester.txt");
    out << sems.numSemesterInSchoolYear << endl;
    out << sems.startDate << " " << sems.startMonth << " " << sems.startYear << endl;
    out << sems.endDate << " " << sems.endMonth << " " << sems.endYear << endl;
    out << sems.numCourses << endl;
    for (int i=0;i<sems.numCourses;i++){
        out << sems.coursesListInSemester[i].ID << endl;
    }
    out.close();
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
void outputCourse(string fileName,Course curCourse){
    ofstream out;
    string str;
    out.open(fileName); //output the information of courses, and student ID involved in course.
    out << curCourse.ID << endl;
    out << curCourse.courseName << endl;
    out << curCourse.className << endl;
    out << curCourse.teacher << endl;
    out << curCourse.numCredits << endl;
    out << curCourse.maxStudents << endl;
    out << curCourse.dayoftheWeek << endl;
    out << curCourse.sessionTime << endl;
    out << curCourse.numStudents << endl;
    for (int i=0;i<curCourse.numStudents;i++){
        out << curCourse.listStudentInCourse[i].studentID << endl;
    }
    out.close();
}
bool checkFormatDayOfTheWeek(string format){ //return true if it's in the right format of day of the week
    for (unsigned int i=0;i<format.size();i++){
        format[i]=toupper(format[i]);
    }
    return (format=="MON" || format=="TUE" || format=="WED" || format=="THU" || format=="FRI" || format=="SAT");
}
bool checkFormatSession(string format){ //return true if it's in the right format of session
    return (format=="S1" || format=="S2" || format=="S3" || format=="S4");
}
