#include "newClass.h"

//this function to create new Class and add this Class to ClassList
void createNewClass(School_Year& targetSchoolYear, int &numClass)
{
    Class* newClassList = new Class[numClass + 1];
    
    for (int i=0; i<numClass; i++)
    {
        newClassList[i] = targetSchoolYear.ClassList[i];
    }
   
    cout << "Enter Class ID: ";
    cin >> newClassList[numClass].Class_ID;
    cout << "Enter Year Studied: ";
    cin >> newClassList[numClass].Year_Studied;
    
    if (numClass > 0) delete [] targetSchoolYear.ClassList;
    
    targetSchoolYear.ClassList = newClassList;
    numClass++;
}

//this function to update SchoolYearCSV
void updateSchoolYearCSV ( string &filename, School_Year& targetSchoolYear, int &numClass)
{
    ofstream file(filename);
    
    if (!file.is_open()) cout <<"Can not open file: "<< filename << "\n";
    else
    {
        for (int i=0; i < numClass; i++)
        {
            file << targetSchoolYear.ClassList[i].Class_ID << ",";
            file << targetSchoolYear.ClassList[i].Year_Studied << "\n";
        }
        
        if (file.good()) cout << "School year information updated in "<< filename << " successfully\n";
        else cout << "Error writing to file: " << filename << "\n";
        
        file.close();
    }
}
