#include <iostream>
#include <vector>

using namespace std;

class Student
{
private:
    static int student_number;
    static int count;
    static vector<string> registered_names;

    int id;
    string name;

    // Grades recording
    vector<int> subject_points;
    vector<string> my_subjects;

public:
    Student();
    Student(string name);

    void addGrade(string subject, int point);
    void deleteGrade(string subject);
    void deleteGrade();
    void printGrade();

    bool operator==(Student &std);

    string getName();
    int getId();
    void printData();
    int getGrade(string subjectName);
    vector<string> getSubjects();
};

class Class
{
private:
    vector<Student *> student_list;
    vector<string> subjects;
    vector<int> stds_in_subject;

    int getNumOfStudents(string subjectName);
    double getSubjectAvg(string subjectName);

public:
    Class(){};

    void addStudent(Student &student);
    void deleteStudent(Student &student);
    void deleteStudent(string studentName);
    void printNumOfStudent(string subjectName);
    void printNumOfStudent();
    void printAvgScore(string subjectName);
    void printAvgScore();
    void printSubjectInformation(string subjectName);
    void printSubjectInformation();
};