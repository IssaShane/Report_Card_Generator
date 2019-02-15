#include "csv.h"

using namespace std;

CSV::CSV(string filename) {
  ifstream file(filename);
  string line;
  while (file.good()) {
    line = "";
    getline(file, line);
    contents.push_back(line);
  }
  file.close();

  separateElements();
  createMatrix();
  removeEmpty();
}

CSV::~CSV() {}

void CSV::separateElements() {
  string line = "";
  for (int i = 0; i < contents.size(); i++) {
    for (int j = 0; j < contents[i].size(); j++) {
      line += contents[i][j];
      if (line[line.size() - 1] == ',') {
        line.erase(line.size()-1, 1); // drop the comma
        elements.push_back(line); // add the line to the elements vector
        line = ""; // clear line for the next element
      }
      // catch last element (because there's no comma after it)
      else if (j == contents[i].size()-1) {
        elements.push_back(line);
        line = "";
      }
    }
  }
}

void CSV::printLines() {
  for (int i = 0; i < contents.size(); i++) {
    cout << contents[i] << endl;
  }
  cout << endl;
}

void CSV::printElements() {
  for (int i = 0; i < elements.size(); i++) {
    cout << elements[i] << " ";
  }
  cout << endl;
  //if (elements.size() > 0) cout << elements[elements.size() - 1] << endl;
}

void CSV::printMatrix() {
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

int CSV::elementsPerLine() {
  int commas = 0;
  for (int i = 0; i < contents[0].size(); i++) {
    if (contents[0][i] == ',') commas++;
  }
  return commas+1;
}

void CSV::createMatrix() {
  int elements_per_line = elementsPerLine();
  int size = elements.size();
  for (int t = 0; t < size; t++) {
    vector<string> row;
    matrix.push_back(row);
  }
  for (int i = 0, j = 0; i < size; i++) {
    matrix[j].push_back(elements[i]);
    if (((i+1) % elements_per_line) == 0) j++;
  }
}

void CSV::removeEmpty() {
  for (int i = 0; i < contents.size(); i++) {
    if (contents[i].size() == 0) {
      contents.erase(contents.begin()-1+i);
    }
  }
}
