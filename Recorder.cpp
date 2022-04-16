#include "Recorder.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

int Student::student_number = 0;
int Student::count = 0;
vector<string> Student::registered_names;

int getIndex(const vector<string> &source, string target)
// Finds an item in an array (of strings) and return its index, -1 if not found
// Precondition: source is the vector where to be searched,
// target is the value to be searced
{
    for (int i = 0; i < source.size(); i++)
    {
        if (source[i] == target)
            return i;
    }
    return -1;
}

/* ********** STUDENT ********** */

Student::Student()
// Creates a Student with the default name
{
    this->id = student_number;
    string temp = "Student";
    temp += to_string(count);
    this->name = temp;
    student_number++;
    count++;
    registered_names.push_back(this->name);
}

Student::Student(string name)
{
    this->id = student_number;

    // Check if the name is already registered
    if (getIndex(registered_names, name) != -1)
    {
        this->name = "Student" + to_string(count);
        count++;
        cout << "Error: The name " << name << " exists. Use default name: " << this->name << "." << endl;
    }
    else
    {
        this->name = name;

        string begin = name.substr(0, 7);

        if (begin == "Student")
        {
            this->name = "Student" + to_string(count);
            count++;
            cout << "Error: The name Student is reserved word. Use default name: " << this->name << "." << endl;
        }
    }

    registered_names.push_back(this->name);
    student_number++;
}

void Student::addGrade(string subject, int point)
{
    int i = getIndex(this->my_subjects, subject);

    if (i != -1)
        // The subject already exists, override the point
        subject_points[i] = point;
    else
    // Add the new grade
    {
        this->my_subjects.push_back(subject);
        this->subject_points.push_back(point);
    }
}

void Student::deleteGrade(string subject)
// Delete one single subject
{
    int i = getIndex(this->my_subjects, subject);

    if (i == -1)
        cout << "Error: Subject " << subject << " could not be found." << endl;
    else
    {
        this->my_subjects.erase(this->my_subjects.begin() + i);
        this->subject_points.erase(this->subject_points.begin() + i);
    }
}

void Student::deleteGrade()
// Deletes all subjects
{
    for (int i = 0; i < this->my_subjects.size(); i++)
    {
        this->my_subjects.erase(this->my_subjects.begin() + i);
        this->subject_points.erase(this->subject_points.begin() + i);
    }
}

void Student::printGrade()
{
    // Check if there are subjects registered
    if (this->my_subjects.size() == 0)
        cout << "Error: Grade could not be found." << endl;
    else
    {
        // Print all grades
        cout << "ID: " << this->id << " Name: " << this->name << endl;
        for (int i = 0; i < this->my_subjects.size(); i++)
            cout << this->my_subjects[i] << " " << this->subject_points[i] << endl;
    }
}

string Student::getName()
{
    return this->name;
}

int Student::getId()
{
    return this->id;
}

void Student::printData()
{
    cout << "Name: " << this->name << "\tID: " << this->id << endl;
}

bool Student::operator==(Student &std)
{
    return (this->name == std.name) && (this->id == std.id);
}

int Student::getGrade(string subjectName)
// Returns the grade of a subject
{
    // This function assumes that the subjec does exsit
    int i = getIndex(this->my_subjects, subjectName);
    return this->subject_points[i];
}

vector<string> Student::getSubjects()
{
    vector<string> temp = this->my_subjects;
    return temp;
}

/* ********** CLASS ********** */

void Class::addStudent(Student &student)
{
    // Check if the student already exsits
    for (int i = 0; i < this->student_list.size(); i++)
    {
        if (*(this->student_list[i]) == student)
        {
            cout << "Error: The student " << student.getName() << " is already in the class." << endl;
            return;
        }
    }

    // Add the student to the list
    this->student_list.push_back(&student);

    vector<string> s = student.getSubjects();
    for (int i = 0; i < s.size(); i++)
    {
        // Add the subject if it does not exist yet
        if (getIndex(this->subjects, s[i]) == -1)
            this->subjects.push_back(s[i]);
    }
}

void Class::deleteStudent(Student &student)
// Delete Student by instance
{
    for (int i = 0; i < this->student_list.size(); i++)
    {
        if (*(this->student_list[i]) == student)
        {
            this->student_list.erase(this->student_list.begin() + i);
            return;
        }
    }
    cout << "Error: Student " << student.getName() << " could not be found." << endl;
}

void Class::deleteStudent(string studentName)
// Delete Student by name
{
    for (int i = 0; i < this->student_list.size(); i++)
    {
        if (this->student_list[i]->getName() == studentName)
        {
            this->student_list.erase(this->student_list.begin() + i);
            return;
        }
    }
    cout << "Error: Student " << studentName << " could not be found." << endl;
}

int Class::getNumOfStudents(string subjectName)
// Get the number of Students that has a subject
// Helper function for printNumOfStudent
{
    // This function supposes that the subject does exist
    int stds = 0;
    for (int i = 0; i < this->student_list.size(); i++)
        if (getIndex(this->student_list[i]->getSubjects(), subjectName) != -1)
            stds++;

    return stds;
}

void Class::printNumOfStudent(string subjectName)
{
    int i = getIndex(this->subjects, subjectName);

    if (i == -1)
    {
        cout << "Error: Subject " << subjectName << " could not be found." << endl;
        return;
    }

    int stds = this->getNumOfStudents(subjectName);

    if (stds == 0)
        cout << "Error: Subject " << subjectName << " could not be found." << endl;
    else
        cout << subjectName << " " << stds << endl;
}

void Class::printNumOfStudent()
{
    for (int i = 0; i < this->subjects.size(); i++)
    {
        string subjectName = this->subjects[i];
        int stds = this->getNumOfStudents(subjectName);
        if (stds > 0)
            cout << subjectName << " " << stds << endl;
    }
}

double Class::getSubjectAvg(string subjectName)
// Get the average grade of a subject, -1 if there are not Students
// Helper function for printAvgScore
{
    // This function supposes that the subject does exist
    int stds = 0;
    int grades = 0;
    for (int i = 0; i < this->student_list.size(); i++)
        if (getIndex(this->student_list[i]->getSubjects(), subjectName) != -1)
        {
            grades += this->student_list[i]->getGrade(subjectName);
            stds++;
        }

    if (stds == 0)
        return -1;

    return grades / static_cast<double>(stds);
}

void Class::printAvgScore(string subjectName)
{
    if (getIndex(this->subjects, subjectName) == -1)
    {
        cout << "Error: Subject " << subjectName << " could not be found." << endl;
        return;
    }

    double avg = getSubjectAvg(subjectName);

    if (avg == -1)
        cout << "Error: Subject " << subjectName << " could not be found." << endl;
    else
        cout << subjectName << " " << avg << endl;
}

void Class::printAvgScore()
{
    for (int i = 0; i < this->subjects.size(); i++)
    {
        string subjectName = this->subjects[i];
        double avg = this->getSubjectAvg(subjectName);
        if (avg != -1)
            cout << subjectName << " " << avg << endl;
    }
}

void Class::printSubjectInformation(string subjectName)
{
    int stds = getNumOfStudents(subjectName);
    if (getIndex(this->subjects, subjectName) == -1 || stds == 0)
    {
        cout << "Error: Subject " << subjectName << " could not be found." << endl;
        return;
    }

    cout << "Subject name: " << subjectName << endl;
    cout << "Num of students: " << stds << endl;

    for (int i = 0; i < this->student_list.size(); i++)
    {
        Student temp = *(this->student_list[i]);
        vector<string> subjs = temp.getSubjects();
        // Check if the Student has the subject
        if (getIndex(subjs, subjectName) != -1)
            cout << temp.getName() << " " << temp.getGrade(subjectName) << endl;
    }
}

void Class::printSubjectInformation()
{
    for (int i = 0; i < this->subjects.size(); i++)
    {
        string subjectName = this->subjects[i];
        int stds = getNumOfStudents(subjectName);

        if (stds > 0)
            this->printSubjectInformation(subjectName);
    }
}