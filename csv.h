#ifndef CSV_H
#define CSV_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class CSV {
  public:
    vector<string> contents; //lines
    vector<string> elements; // comma-separated elements
    vector<vector<string>> matrix; // table of elements

  public:
    CSV(string filename);
    ~CSV();
    void separateElements();
    void printLines();
    void printElements();
    void printMatrix();
    int elementsPerLine();
    void createMatrix();
    void removeEmpty();
};

#endif
