#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <vector>

using namespace std;

class Hash {
  public:
    Hash();
    ~Hash();
    void add_elem(int id, int elem_index);
    int get_index(int id);

  private:
    vector<int> indeces;
};

#endif
