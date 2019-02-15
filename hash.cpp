#include "hash.h"

using namespace std;

Hash::Hash() {}
Hash::~Hash() {}

// add_elem(id, elem_index) assigns elem_index to the index i = id
// requires: id >= 0
//           elem_index >= 0
// effects: mutates data
// efficiency: O(nlog(n))
void Hash::add_elem(int id, int elem_index) {
  int size = indeces.size();
  if (id < 0) return;
  if (id == size) {
    indeces.push_back(elem_index);
  }
  else if (id < size) {
    indeces[id] = elem_index;
  }
  else if (id > size) {
    for (int i = size-1; i<id+1; i++) {
      indeces.push_back(0);
    }
    indeces[id] = elem_index;
  }
}

// get_index(id) returns the appropriate index for id
// requires: id >= 0
// effects: none
// efficiency: O(1)
int Hash::get_index(int id) {
  return indeces[id];
}
