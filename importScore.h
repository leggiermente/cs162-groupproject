#ifndef importScore_h
#define importScore_h

#include "Struct.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>
using namespace std;

void readScoreBoardCSV(string filename, Course &course);
void updateStudentResult(Student* scoreboard,int numStu ,float otherMark, float midMark, float finalMark, float totalMark, string studentID);

#endif
