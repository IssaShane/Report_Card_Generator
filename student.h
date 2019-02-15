#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <vector>
#include "course.h"
#include "hash.h"

using namespace std;

class Student {
  private:
    string name;
    int id;
    float average;
    vector<Course> courses;
    Hash course_hash; // returns course index by course_id
    Hash course_test_hash; // returns course index by test_id

  public:
    Student();
    Student(string n, int id_);
    ~Student();
    void addCourse(Course);
    void addTest(int, int);
    void addMark(int, int, int);
    void setID(int);
    void setName(string);
    void calculateAverage();
    void removeEmptyCourses();
    void print();
    ostream& print(ostream &out);
    int getID();
    int number_of_courses();


};

ostream & operator << (ostream &out, Student &s);

#endif
