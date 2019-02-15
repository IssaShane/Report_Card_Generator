#include "course.h"

using namespace std;

Course::Course() {
  name = "DEFAULT_COURSE_NAME";
  final_mark = 0;
  teacher = "DEFAULT_TEACHER_NAME";
  empty_ = true;
}

Course::Course(string n, int i, string t) {
  name = n;
  id = i;
  teacher = t;
  empty_ = true;
}

Course::~Course() {}

// calculateFinalMark() calculates the final mark
//  for this course based on test marks and weights
//  and stores the final value in final_mark
// requires: none
// effects: mutates data
// efficiency: O(n)
void Course::calculateFinalMark() {
  float running_fm = 0;
  for (int i = 0; i < marks.size(); i++) {
    running_fm += (marks[i] * weight[i])/10000;
  }
  final_mark = running_fm*100;
}

// addMark (m) adds m to the end of the marks vector
// requires: m is a valid int
// effects: mutates data
// efficiency: O(n)
void Course::addMark(int m) {
  marks.push_back(m);
  empty_ = false;
}

// addMark (w) adds w to the end of the weights vector
// requires: w is a valid int
// effects: mutates data (weights)
// efficiency: O(log(n))
void Course::addWeight(int w) {weight.push_back(w);}

// addMark (t) adds t to the end of the tests vector
// requires: t is a valid int
// effects: mutates data (tests)
// efficiency: O(log(n))
void Course::addTest(int t) {tests.push_back(t);}

// containsTest(t) returns true iff the test of ID
//  t is contained within the tests for this course
// requires: t is a valid int
// effects: none
// efficiency: O(n)
bool Course::containsTest(int t) {
  for (int i = 0; i < tests.size(); i++) {
    if (tests[i] == t) return true;
  }
  return false;
}

// print() outputs the data of the course to
//  standard output
// requires: none
// effects: output
// efficiency: O(1)
void Course::print() {
  cout << fixed;
  cout << setprecision(2);
  cout << "\tCourse: " << name << ", Teacher: " << teacher << endl;
  cout << "\tFinal Grade:\t" << final_mark << "%";
}

// print(out) outputs the data of the course to
//  the ostream out
// requires: none
// effects: output
// efficiency: O(1)
ostream& Course::print(ostream &out) {
  out << fixed;
  out << setprecision(2);
  out << "\tCourse: " << name << ", Teacher: " << teacher << endl;
  out << "\tFinal Grade:\t" << final_mark << "%";
  return out;
}

float Course::getMark() {return final_mark;}
int Course::getID() {return id;}

// printTests() outputs all test ID numbers for
//  this course. This function is primarily
//  intended for debugging.
// requires: none
// effects: output
// efficiency: O(n)
void Course::printTests() {
  for (int i = 0; i < tests.size(); i++) {
    cout << tests[i] << " ";
  }
}

// empty() returns true iff there are no marks
//  recorded for this course
// requires: none
// effects: none
// efficiency: O(1)
bool Course::empty() {
  if (empty_) return true;
  return false;
}

// <<(out) outputs the data of the course to
//  the ostream out
// requires: none
// effects: output
// efficiency: O(1)
ostream& operator << (ostream &out, Course &c) {
  c.print(out);
  return out;
}
