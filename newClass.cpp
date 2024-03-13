#include "newClass.h"

int countLine (string filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        int lineCount = 0;
        string line;

        while (getline(file, line)) lineCount++;

        file.close();
        return lineCount;
    }
    else
    {
        cerr << "Can not open file: " << filename <<"\n";
        return 0;
    }
}
//this function to create new Class and add this Class to file  School Year
void createNewClass(string& filename)
{
    Class newClass;
    cout << "Enter Class ID: ";
    cin >> newClass.Class_ID;
    cout << "Enter Year Studied: ";
    cin >> newClass.Year_Studied;
    
    ofstream file(filename, ios::app);
    if (file.is_open())
    {
        file << newClass.Class_ID <<","<< newClass.Year_Studied <<"\n";
        file.close();
        cout << "School year information updated in "<< filename << " succcessfully\n";
    }
    else
    {
        cerr << "Can not open file: "<< filename <<"\n";
    }
}

//this function to update ClassList of School Year after create new Class
void updateClassListOfSchoolYear(string &filename, School_Year &targetSchoolYear)
{
    ifstream file(filename);
    if (file.is_open())
    {
        int numClass = 0;
        string line;
        while (getline(file, line))
            numClass++;

        if (targetSchoolYear.ClassList != nullptr)
        {
            delete[] targetSchoolYear.ClassList;
            targetSchoolYear.ClassList = nullptr;
        }

        targetSchoolYear.ClassList = new Class[numClass];

        file.clear();
        file.seekg(0, ios::beg);

        for (int i = 0; i < numClass; i++)
        {
            getline(file, line);
            stringstream ss(line);
            char comma;
            ss >> targetSchoolYear.ClassList[i].Class_ID >> comma >> targetSchoolYear.ClassList[i].Year_Studied;
        }

        file.close();
        cout << "Update ClassList successfully\n";
    }
    else
        cerr << "Can not open file: " << filename << "\n";
}
