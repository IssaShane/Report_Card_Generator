#include "student.h"

using namespace std;

Student::Student() {
  name = "DEFAULT_NAME";
  id = 0;
}

Student::Student(string n, int id_) {
  name = n;
  id = id_;
}

Student::~Student() {}

// addCourse(new_course) enrolls this student in this new_course by adding
//  new_course to the courses vector
// requires:
// effects: mutates data
// efficiency: O(nlog(n))
void Student::addCourse(Course new_course) {
  courses.push_back(new_course);
  course_hash.add_elem(new_course.getID(), courses.size()-1);
}

// addTest(course_id, test_id) adds test_id to the tests vector of the course
//  corresponding to course_id
// requires:
// effects: mutates data
// efficiency: O(log(n))
void Student::addTest(int course_id, int test_id) {
  int size = courses.size();
  /*
  for (int i = 0; i < size; i++) {
    if (courses[i].getID() == course_id) {
      courses[i].addTest(test_id);
    }
  }*/
  int i = course_hash.get_index(course_id);
  courses[i].addTest(test_id);
  course_test_hash.add_elem(test_id, i);
}

// addMark(test_id, mark, weight) adds mark and weight to the course containing
//  the corresponding to test_id
// requires: 0 < mark < 100
//           0 < weight < 100
// effects: mutates data
// efficiency: O(log(n))
void Student::addMark(int test_id, int mark, int weight) {
  int size = courses.size();
  /*
  for (int i = 0; i < size; i++) {
    if (courses[i].containsTest(test_id)) {
      courses[i].addMark(mark);
      courses[i].addWeight(weight);
    }
  }*/
  int i = course_test_hash.get_index(test_id);
  courses[i].addMark(mark);
  courses[i].addWeight(weight);
}

void Student::setID(int new_ID) {id = new_ID;}

void Student::setName(string new_name) {name = new_name;}

int Student::getID() {return id;}

int Student::number_of_courses() {return courses.size();}

// calculateAverage() calculates the final grade average for this student
//  requires:
//  effects: mutates data
//  efficiency: O(n²)
void Student::calculateAverage() {
  float running_total = 0;
  int size = courses.size();
  for (int i = 0; i < size; i++) {
    courses[i].calculateFinalMark();
    running_total += courses[i].getMark();
  }
  average = running_total;
  average /= size;
}

// removeEmptyCourses() clears this student of any course deemed empty, defined
//  by any course containing no marks being defined as empty
// requires:
// effects: mutates data
// efficiency: O(nlog(n))
void Student::removeEmptyCourses() {
  int size = courses.size();
  for (int i = 0; i < size; i++) {
    if (courses[i].empty()) {
      courses.erase(courses.begin()+i);
    }
  }
}

void Student::print() {
  removeEmptyCourses();
  calculateAverage();
  cout << fixed;
  cout << setprecision(2);
  cout << "Student Id: " << id << ", " << "name: " << name << endl;
  cout << "Total Average:\t" << average << "%" << endl << endl;
  for (int i = 0; i < courses.size(); i++) {
    cout << courses[i];
    cout << endl << endl;
  }
}

ostream& Student::print(ostream &out) {
  removeEmptyCourses();
  calculateAverage();
  out << fixed;
  out << setprecision(2);
  out << "Student Id: " << id << ", " << "name: " << name << endl;
  out << "Total Average:\t" << average << "%" << endl << endl;
  for (int i = 0; i < courses.size(); i++) {
    out << courses[i];
    out << endl << endl;
  }
  return out;
}

ostream & operator << (ostream &out, Student & s) {
  s.print(out);
  return out;
}
