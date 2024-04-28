#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

#include "HandleData.h"
#include "Struct.h"
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
        getline(s, line, ','); newStudent[indexStu].studentID = line;
        getline(s, line, ','); newStudent[indexStu].firstName = line;
        getline(s, line, ','); newStudent[indexStu].lastName = line;
        getline(s, line, ','); newStudent[indexStu].femaleGender = stoi(line);
        getline(s, line, ','); newStudent[indexStu].dob = line;
        getline(s, line, ','); newStudent[indexStu].socialID = line;

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
        getline(s, line, ','); newStaff[indexStaff].staffID = line;
        getline(s, line, ','); newStaff[indexStaff].firstName = line;
        getline(s, line, ','); newStaff[indexStaff].lastName = line;

        //Auto generate password = 1
        newStaff[indexStaff].password = "1";
        indexStaff++;
    }
    file.close();
    return newStaff;
}

SchoolYear* readSchoolYear(string path, int& numSchoolYear) {
    string line;
	ifstream file(path + "/schoolyear.txt");
    if (!file) {
        cout << "Can't open school year file\n";
        return nullptr;
    }
	getline(file, line); numSchoolYear = stoi(line);
    SchoolYear* schoolYearArr = new SchoolYear[numSchoolYear];
    for (int i = 0; i < numSchoolYear; i++) {
        std::getline(file, line, ','); schoolYearArr[i].period = line;
        std::getline(file, line); schoolYearArr[i].numSemester = stoi(line);
        schoolYearArr[i].listSemester = new Semester[schoolYearArr[i].numSemester];
        for (int j = 0; j < schoolYearArr[i].numSemester; ++j) {
            schoolYearArr[i].listSemester[j].numSemesterInSchoolYear = j + 1;
        }
    }
    file.close();
    
    for (int i = 0; i < numSchoolYear; ++i) {
        for (int j = 0; j < schoolYearArr[i].numSemester; ++j) {
            string path = "database/semester/" + schoolYearArr[i].period + "_" + to_string(j + 1) + ".txt";
            replace(path.begin(), path.end(), '-', '_');
            readSemesterInSchoolYear(path, schoolYearArr[i].listSemester[j]);
        }
    }
	return schoolYearArr;
}
void readSemesterInSchoolYear(string path, Semester& semester) {
    string line;
    ifstream file(path);
    if (!file) {
		cout << "Can't open semester file\n";
		return;
	}
    getline(file,line, ','); semester.startDate = line;
    getline(file,line); semester.endDate = line;
    getline(file,line); semester.numCourses = stoi(line);
    if (semester.numCourses == 0) {
		semester.coursesListInSemester = nullptr;
		return;
	}
    semester.coursesListInSemester = new Course[semester.numCourses];
    for (int i = 0; i < semester.numCourses; ++i) {
		getline(file, line); semester.coursesListInSemester[i].ID = line;
	}
    return;
}
void readCourseInSemester(string path, SchoolYear* schoolYearArr, int numSchoolYear, Class* classArr, int numClass) {
    for (int i = 0; i < numSchoolYear; ++i) {
        for (int j = 0; j < schoolYearArr[i].numSemester; ++j) {
            for (int v = 0; v < schoolYearArr[i].listSemester[j].numCourses; ++v) {
                ifstream file(path + "/" + schoolYearArr[i].listSemester[j].coursesListInSemester[v].ID + ".txt");
                if (!file) {
					cout << "Can't open course file\n";
                    file.close();
                    continue;
				}
                string line;
                getline(file, line); schoolYearArr[i].listSemester[j].coursesListInSemester[v].year = line;
                getline(file, line); schoolYearArr[i].listSemester[j].coursesListInSemester[v].semester = line;
                getline(file, line); // Pass ID
                getline(file, line); schoolYearArr[i].listSemester[j].coursesListInSemester[v].courseName = line;
                getline(file, line); schoolYearArr[i].listSemester[j].coursesListInSemester[v].teacher = line;
                getline(file, line); schoolYearArr[i].listSemester[j].coursesListInSemester[v].numCredits = stoi(line);
                getline(file, line); schoolYearArr[i].listSemester[j].coursesListInSemester[v].session = line;
                getline(file, line); schoolYearArr[i].listSemester[j].coursesListInSemester[v].dayOfWeek = line;
                getline(file, line); int mxStu = stoi(line);
                getline(file, line); int curStu = stoi(line); 
                schoolYearArr[i].listSemester[j].coursesListInSemester[v].currStudents = curStu;
                schoolYearArr[i].listSemester[j].coursesListInSemester[v].maxStudents = mxStu;
                if (mxStu != 0)
                    schoolYearArr[i].listSemester[j].coursesListInSemester[v].listStudentInCourse = new Student * [mxStu];
                
                // Read and store address of student in course 
                for (int k = 0; k < curStu; ++k) {
                    getline(file, line); // Get student ID
                    bool foundStu = false; // Check if student is found
                    
                    // Brute force search for student && store addresss of student in course
                    for (int u = 0; u < numClass && !foundStu; u++) {
                        for (int o = 0; o < classArr[u].numStudent && !foundStu; o++) {
                            if (classArr[u].listStudent[o].studentID == line) {
								schoolYearArr[i].listSemester[j].coursesListInSemester[v].listStudentInCourse[k] = &classArr[u].listStudent[o];
                                foundStu = true;
							}
						}   
                    }
                }
                file.close();
            }
        }
    }
    return;
}
Class* readClass(string path, int& numClass) {
    string line;
	ifstream file(path + "/class.txt");
    if (!file) {
        cout << "Can't open class file\n";
    	return nullptr;
    }
	getline(file, line);
    numClass = stoi(line);
    Class* classArr = new Class[numClass];
    for (int i = 0; i < numClass; i++) {
		getline(file, line); 
        classArr[i].classID = line;
	}
    file.close();
    for (int i = 0; i < numClass; i++) {
        file.open(path + "/" + classArr[i].classID + ".txt");
        if (!file) {
			cout << "Can't open class id file\n";
			//return nullptr;
		}
        else {
            getline(file, line);
            classArr[i].numStudent = stoi(line);
            classArr[i].listStudent = new Student[classArr[i].numStudent];
            for (int j = 0; j < classArr[i].numStudent; j++) {
                getline(file, line);
                classArr[i].listStudent[j].studentID = line;
            }
            readStudentTXT("database/student", classArr[i]);
            file.close();
        }
	}
    return classArr;
}
void readStudentTXT(string path, Class& classStu) {
    for (int i = 0; i < classStu.numStudent; ++i) {
        ifstream file(path + "/" + classStu.listStudent[i].studentID + ".txt");
        if (!file) {
            cout << "Can't open student id file\n";
        }
        else {
            string line;
            getline(file, line);
            getline(file, line); classStu.listStudent[i].firstName = line;
            getline(file, line); classStu.listStudent[i].lastName = line;
            getline(file, line); classStu.listStudent[i].femaleGender = (line == "0") ? false : true;
            getline(file, line); classStu.listStudent[i].dob = line;
            getline(file, line); classStu.listStudent[i].socialID = line;
            getline(file, line); classStu.listStudent[i].password = line;
            
            for (int h = 0; h < 4; h++) {
                getline(file, line); 
                classStu.listStudent[i].gpaList[h].year = line;
            }
            for (int h = 0; h < 4; h++) {
                getline(file, line, ','); classStu.listStudent[i].gpaList[h].gpaS[0] = stoi(line);
                getline(file, line, ','); classStu.listStudent[i].gpaList[h].gpaS[1] = stoi(line);
                getline(file, line, ','); classStu.listStudent[i].gpaList[h].gpaS[2] = stoi(line);
                getline(file, line); classStu.listStudent[i].gpaList[h].gpaS[3] = stoi(line);
            }

            getline(file, line); classStu.listStudent[i].numCourse = stoi(line);
            int numC = classStu.listStudent[i].numCourse;
            if (numC != 0) classStu.listStudent[i].scoreList = new ScoreStu[numC];
            for (int t = 0; t < numC; ++t) {
                getline(file, line, ','); classStu.listStudent[i].scoreList[t].year = line;
                getline(file, line, ','); classStu.listStudent[i].scoreList[t].semester = line;
                getline(file, line, ','); classStu.listStudent[i].scoreList[t].courseID = line;
				getline(file, line, ','); classStu.listStudent[i].scoreList[t].totalSc = stoi(line);
                getline(file, line, ','); classStu.listStudent[i].scoreList[t].finalSc = stoi(line);
                getline(file, line, ','); classStu.listStudent[i].scoreList[t].midSc = stoi(line);
                getline(file, line); classStu.listStudent[i].scoreList[t].otherSc = stoi(line);
            }
            file.close();
        }
    }
    return;
}
bool readCSVStuToClass(string path, Class& thatClass, int& numIc) {
    ifstream file(path);
    if (!file) {
        cout << "Can't open student file" << path << endl;
        return false;
    }
	string line;
    int count = 0;
    while (getline(file, line)) {
		count++;
	}
    file.close();
    file.open(path);
    Student* newStudent = new Student[thatClass.numStudent + count];
    for (int i = 0; i < thatClass.numStudent; i++) {
		newStudent[i] = thatClass.listStudent[i];
	}
    for (int i = thatClass.numStudent; i < thatClass.numStudent + count; ++i) {
        getline(file,line, ','); // Pass No data in CSV
        getline(file,line, ','); newStudent[i].studentID = line;
        getline(file,line, ','); newStudent[i].firstName = line;
        getline(file,line, ','); newStudent[i].lastName = line;
        getline(file,line, ','); (line == "Male") ? newStudent[i].femaleGender = false : newStudent[i].femaleGender = true;
        getline(file,line, ','); newStudent[i].dob = line;
        getline(file,line); newStudent[i].socialID = line;
    }
    delete[] thatClass.listStudent;
    thatClass.listStudent = newStudent;
    thatClass.numStudent += count;
    numIc = count;
    return true;
}

void printTest(Class* classArr, int numClass, SchoolYear* schoolYearArr, int numSchoolYear) {
    for (int i = 0; i < numClass; i++) {
		cout << classArr[i].classID << endl;
        for (int j = 0; j < classArr[i].numStudent; j++) {
			cout << classArr[i].listStudent[j].studentID << endl;
            for (int k = 0; k < classArr[i].listStudent[j].numCourse; k++) {
                cout << classArr[i].listStudent[j].scoreList[k].courseID << endl;
                cout << classArr[i].listStudent[j].scoreList[k].year << endl;
                cout << classArr[i].listStudent[j].scoreList[k].otherSc << endl;
            }
            cout << endl;
		}
	}
    cout << endl;
    return;
}