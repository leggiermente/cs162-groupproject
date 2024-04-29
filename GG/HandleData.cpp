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
    if (!file) {
		cout << "Can't open staff file\n";
		return nullptr;
	}
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
        getline(s, line, ','); newStaff[indexStaff].socialID = line;
        getline(s, line, ','); (line == "1") ? newStaff[indexStaff].gender = false : newStaff[indexStaff].gender = true;
        getline(s, line, ','); newStaff[indexStaff].dob = line;
        getline(s, line); newStaff[indexStaff].password = line;
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
                    Student* thatStu = nullptr;
                    for (int u = 0; u < numClass && !foundStu; u++) {
                        for (int o = 0; o < classArr[u].numStudent && !foundStu; o++) {
                            if (classArr[u].listStudent[o].studentID == line) {
								schoolYearArr[i].listSemester[j].coursesListInSemester[v].listStudentInCourse[k] = &classArr[u].listStudent[o];
                                thatStu = &classArr[u].listStudent[o];
                                foundStu = true;
							}
						}   
                    }

                    bool addYear = true;
                    for (int u = 0; u < 4; u++) {
                        if (schoolYearArr[i].listSemester[j].coursesListInSemester[v].year == thatStu->gpaList[u].year) {
                            addYear = false;
							break;
                        }
                            
                    }
                    if (addYear) {
                        for (int u = 0; u < 4; u++) {
                            if (thatStu->gpaList[u].year.empty())
                            {
                                thatStu->gpaList[u].year = schoolYearArr[i].listSemester[j].coursesListInSemester[v].year;
								break;
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
                if (line != "\n") classStu.listStudent[i].gpaList[h].year = line;
            }
            for (int h = 0; h < 4; h++) {
                getline(file, line, ','); classStu.listStudent[i].gpaList[h].gpaS[3] = stoi(line);
                getline(file, line, ','); classStu.listStudent[i].gpaList[h].gpaS[0] = stoi(line);
                getline(file, line, ','); classStu.listStudent[i].gpaList[h].gpaS[1] = stoi(line);
                getline(file, line); classStu.listStudent[i].gpaList[h].gpaS[2] = stoi(line);
            }

            getline(file, line); classStu.listStudent[i].numCourse = stoi(line);
            int numC = classStu.listStudent[i].numCourse;
            if (numC != 0) classStu.listStudent[i].scoreList = new ScoreStu[numC];
            for (int t = 0; t < numC; ++t) {
                getline(file, line, ','); classStu.listStudent[i].scoreList[t].year = line;
                getline(file, line, ','); classStu.listStudent[i].scoreList[t].semester = line;
                getline(file, line, ','); classStu.listStudent[i].scoreList[t].courseID = line;
				getline(file, line, ','); classStu.listStudent[i].scoreList[t].totalSc = stof(line);
                getline(file, line, ','); classStu.listStudent[i].scoreList[t].finalSc = stof(line);
                getline(file, line, ','); classStu.listStudent[i].scoreList[t].midSc = stof(line);
                getline(file, line); classStu.listStudent[i].scoreList[t].otherSc = stof(line);
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
bool readCSVStuToCourse(string path, Class* allClass, Course& thatCourse, int& numStuAdd, int numClass) {
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
    if (count + thatCourse.currStudents > thatCourse.maxStudents) return false;
    
    file.open(path);
	Student** newStudent = new Student * [thatCourse.maxStudents + count];
	for (int i = 0; i < thatCourse.currStudents; i++) {
		newStudent[i] = thatCourse.listStudentInCourse[i];
	}
	for (int i = thatCourse.currStudents; i < thatCourse.currStudents + count; ++i) {
		getline(file,line, ','); // Pass No data in CSV
		getline(file,line, ','); // Get student ID
        bool found = false;
        Student* tmpStu = nullptr;
        for (int v = 0; v < numClass && !found; ++v) {
            for (int j = 0; j < allClass[v].numStudent && !found; ++j) {
                if (allClass[v].listStudent[j].studentID == line) {
                    tmpStu = &allClass[v].listStudent[j];
                    found = true;
				}
			}
        }
        if (found) {
            for (int k = 0; k < thatCourse.currStudents; ++k) {
                if (line == newStudent[k]->studentID) {
					found = false;
					break;
				}
			}
        }
        if (!found) {
            i--;
            count--;
        }
        if (found) {
            newStudent[i] = tmpStu;
        }
        getline(file, line); // Pass remain data in CSV
	}
	delete[] thatCourse.listStudentInCourse;
	thatCourse.listStudentInCourse = newStudent;
    thatCourse.currStudents += count;
    numStuAdd = count;
	return true;
}
bool readScoreCSV(string path, Course &thatCourse) {
    ifstream file(path);
    if (!file) {
		cout << "Can't open score file" << path << endl;
		return false;
	}
    string line;
    for (int i = 0; i < thatCourse.currStudents; ++i) {
		getline(file, line, ',');
        bool found = false;
        for (int j = 0; j < thatCourse.currStudents && !found; ++j) {
            if (line == thatCourse.listStudentInCourse[j]->studentID) {
                found = true;
                ScoreStu* stuSc = nullptr;
                Student* curStu = thatCourse.listStudentInCourse[j];
                for (int v = 0; v < curStu->numCourse; ++v) {
                    if (curStu->scoreList[v].courseID == thatCourse.ID) {
						stuSc = &curStu->scoreList[v];
						break;
					}
                }
                getline(file, line, ','); stuSc->totalSc = stof(line);
                getline(file, line, ','); stuSc->finalSc = stof(line);
                getline(file, line, ','); stuSc->midSc = stof(line);
				getline(file, line); stuSc->otherSc = stof(line);
            }
        }
	}
}
bool exportFileIdStu(string path, Course& thatCourse) {
    ofstream file(path);
	if (!file) {
		cout << "Can't open file to export\n";
		return false;
	}
	for (int i = 0; i < thatCourse.currStudents; ++i) {
		file << thatCourse.listStudentInCourse[i]->studentID << endl;
	}
	file.close();
	return true;
}

bool saveSchoolyear(SchoolYear* yearArr, int numYear) {
    // schoolyear.txt
    ofstream file("database/schoolyear/schoolyear.txt");
    if (!file) {
		cout << "Can't open school year file\n";
		return false;
	}
    file << numYear << endl;
    for (int i = 0; i < numYear; ++i) {
		file << yearArr[i].period << "," << yearArr[i].numSemester << endl;
	}
    file.close();

    // year_seme.txt
    for (int i = 0; i < numYear; ++i) {
        for (int j = 0; j < yearArr[i].numSemester; ++j) {
            string path = "database/semester/" + yearArr[i].period + "_" + to_string(j + 1) + ".txt";
            replace(path.begin(), path.end(), '-', '_');
            saveSeme(path, &yearArr[i].listSemester[j]);
        }
    }
    return true;
}
bool saveSeme(string path, Semester* thisSeme) {
    ofstream file(path);
    if (!file) {
        cout << "Can't open semester file\n";
        return false;
    }
    file << thisSeme->startDate << "," << thisSeme->endDate << endl;
    file << thisSeme->numCourses << endl;
    for (int i = 0; i < thisSeme->numCourses; ++i) {
		file << thisSeme->coursesListInSemester[i].ID << endl;
        string path2 = "database/course/" + thisSeme->coursesListInSemester[i].ID + ".txt";
        saveCourse(path2, &thisSeme->coursesListInSemester[i]);
	}
	file.close();
	return true;
}
bool saveCourse(string path, Course* thisCourse) {
    ofstream file(path);
    if (!file) {
        cout << "Can't open course file\n";
        return false;
    }
    file << thisCourse->year << endl;
    file << thisCourse->semester << endl;
    file << thisCourse->ID << endl;
    file << thisCourse->courseName << endl;
    file << thisCourse->teacher << endl;
    file << thisCourse->numCredits << endl;
    file << thisCourse->session << endl;
    file << thisCourse->dayOfWeek << endl;
    file << thisCourse->maxStudents << endl;
    file << thisCourse->currStudents << endl;
    for (int i = 0; i < thisCourse->currStudents; ++i) {
        file << thisCourse->listStudentInCourse[i]->studentID << endl;
    }
    file.close();
    return true;
}
bool saveClass(Class* classArr, int numClass) {
    ofstream file("database/class/class.txt");
    if (!file) {
		cout << "Can't open class file\n";
		return false;
	}
    file << numClass << endl;
    for (int i = 0; i < numClass; ++i) {
        file << classArr[i].classID << endl;
    }
    file.close();
    
    for (int i = 0; i < numClass; ++i) {
		string path = "database/class/" + classArr[i].classID + ".txt";
		ofstream file(path);
		if (!file) {
            cout << "Can't open class id file\n";
            return false;
        }
        file << classArr[i].numStudent << endl;
        for (int j = 0; j < classArr[i].numStudent; ++j) {
			file << classArr[i].listStudent[j].studentID << endl;
            string path2 = "database/student/" + classArr[i].listStudent[j].studentID + ".txt";
            saveStudent(path2, &classArr[i].listStudent[j]);
		}
        file.close();
    }
    return true;
}
bool saveStudent(string path, Student* currStu) {
    ofstream file(path);
    if (!file) {
		cout << "Can't open student id file\n";
		return false;
	}
	file << currStu->studentID << endl;
	file << currStu->firstName << endl;
	file << currStu->lastName << endl;
    file << currStu->femaleGender << endl;
    file << currStu->dob << endl;
    file << currStu->socialID << endl;
    file << currStu->password << endl;
    for (int i = 0; i < 4; i++) {
        if (currStu->gpaList[i].year.empty()) file << endl;
        else file << currStu->gpaList[i].year << endl;
	}
    for (int i = 0; i < 4; i++) {
        file << currStu->gpaList[i].gpaS[3] << "," << currStu->gpaList[i].gpaS[0] << "," << currStu->gpaList[i].gpaS[1] << "," << currStu->gpaList[i].gpaS[2] << endl;
    }
    file << currStu->numCourse << endl;
    for (int i = 0; i < currStu->numCourse; i++) {
		file << currStu->scoreList[i].year << "," << currStu->scoreList[i].semester << "," << currStu->scoreList[i].courseID << "," << currStu->scoreList[i].totalSc << "," << currStu->scoreList[i].finalSc << "," << currStu->scoreList[i].midSc << "," << currStu->scoreList[i].otherSc << endl;
	}
    file.close();
    return true;
}
bool saveStaff(Staff* staffArr, int numStaff) {
    ofstream file("database/staff/staff.csv");
    if (!file) {
        cout << "Can't open staff file\n";
        return false;
    }
    for (int i = 0; i < numStaff; i++) {
		file << i + 1<< "," << staffArr[i].staffID << "," << staffArr[i].firstName << "," << staffArr[i].lastName << ","
            << staffArr[i].socialID << "," << staffArr[i].gender << "," << staffArr[i].dob << "," << staffArr[i].password << endl;
    }
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