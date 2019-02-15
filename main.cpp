#include <iostream>
#include <sstream>
#include "csv.h"
#include "course.h"
#include "student.h"
#include "hash.h"

using namespace std;

// string_to_int(s) returns the value of the integer held within s
// requires: s is a string composed of an integer
// effects: none
// efficiency: O(1)
int string_to_int(string s) {
  int i = 0;
  stringstream str(s);
  str >> i;
  return i;
}

// init_students(students, stu_file) fills the members of the students vector
//  with the data contained within stu_file
// requires: none
// effects: mutates data
// efficiency: O(nlog(n))
void init_students(vector<Student> &students, CSV &stu_file) {
  int size = stu_file.contents.size();
  for (int i = 1; i < size; i++) {
    Student s;
    s.setName(stu_file.matrix[i][1]);
    string id_s = stu_file.matrix[i][0];
    int id_i = string_to_int(id_s);
    s.setID(id_i);
    students.push_back(s);
  }
}

// init_courses(students, courses, course_file) enrolls each student in
//  each course
// requires: none
// effects: mutates data
// efficiency: O(n²)
void init_courses(vector<Student> &students, vector<Course> &courses,
                  CSV &course_file) {
  int course_size = course_file.contents.size();
  for (int i = 1; i < course_size; i++) {
    int id_i = string_to_int(course_file.matrix[i][0]);
    Course c(course_file.matrix[i][1],
             id_i,
             course_file.matrix[i][2]);
    int stu_size = students.size();
    for (int j = 0; j < stu_size; j++) {
      students[j].addCourse(c);
    }
    courses.push_back(c);
  }
}

// init_weights(weights, students, test_file) fills the weights matrix with
//  the grading weight of each test contained in test_file
// requires: none
// effects: mutates data
// efficiency: O(n²log(n))
void init_weights(vector<vector <int>> &weights, vector<Student> &students,
                  Hash &weight_hash, CSV &test_file) {
  int size = test_file.contents.size();
  for (int i = 1; i < size; i++) {
    int w_i = string_to_int(test_file.matrix[i][2]);
    int course_id = string_to_int(test_file.matrix[i][1]);
    int test_id = string_to_int(test_file.matrix[i][0]);
    vector<int> w;
    w.push_back(test_id);
    w.push_back(w_i);
    weights.push_back(w);
    weight_hash.add_elem(test_id, weights.size()-1);

    int stu_size = students.size();
    for (int j = 0; j < stu_size; j++) {
      students[j].addTest(course_id, test_id);
    }
  }
}

// init_marks(students, weights, mark_file) assigns the correct weight and mark
//  to each test for each student
// requires: none
// effects: mutates data
// efficiency: O(n²log(n))
void init_marks(vector<Student> &students, vector<vector<int>> &weights,
                Hash & weight_hash, CSV &mark_file) {
  int size = mark_file.contents.size();
  for (int i = 1; i < size; i++) {
    int test_id = string_to_int(mark_file.matrix[i][0]);
    int stu_id = string_to_int(mark_file.matrix[i][1]);
    int mark = string_to_int(mark_file.matrix[i][2]);

    int stu_size = students.size();
    for (int j = 0; j < stu_size; j++) {
      if (students[j].getID() == stu_id) {
        //find the appropriate weight for the mark
        int weight = 0;
        weight = weights[weight_hash.get_index(test_id)][1];

        students[j].addMark(test_id, mark, weight);
      }
    }
  }
}

// load_data() loads all student data from the students, courses, marks, and
//  tests CSV files, and outputs and writes them to report_card.txt as designed
// requires: students.csv, courses.csv, marks.csv, and tests.csv are all in the
//  same directory as the executable file
// effects: Outputs and writes to local files
// efficiency: O(n²log(n))
void load_data() {
  CSV stu_file("students.csv");
  CSV course_file("courses.csv");
  CSV mark_file("marks.csv");
  CSV test_file("tests.csv");
  Hash weight_hash;

  vector<Student> students;
  vector<Course> courses;
  //intialize student name and ID numbers
  init_students(students, stu_file);
  //enroll each student in every course
  init_courses(students, courses, course_file);

  // store test weights in a vector of 2-dim vectors
  vector<vector<int>> weights; // (test_id, weight)
  init_weights(weights, students, weight_hash, test_file);

  // add marks
  init_marks(students, weights, weight_hash, mark_file);

  ofstream outfile ("report_card.txt");

  int stu_size = students.size();
  for (int i = 0; i < stu_size; i++) {
    cout << students[i] << endl;
    outfile << students[i] << endl;
  }

  outfile.close();
}

int main() {
  load_data();
  return 0;
}
