#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Course {
  private:
    string name; // name of a course
    float final_mark; // final mark in a course
    vector<float> marks; // mark on each test
    vector<float> weight; // weight of each test
    vector<int> tests; // ID number for each test
    string teacher; // teacher's name
    int id; // class ID number as represented in CSV
    bool empty_; // true iff this courses has no marks

  public:
    Course();
    Course(string, int, string);
    ~Course();
    void calculateFinalMark();
    void print();
    ostream& print(ostream& out);
    void addMark(int);
    void addWeight(int);
    void addTest(int);
    bool containsTest(int);
    float getMark();
    int getID();
    void printTests();
    bool empty();

};
ostream & operator << (ostream &out, Course &c);
#endif
