#pragma once
#include <vector>

using namespace std;

enum dat_type { a, b};

class Dat {
 private:
  // two-dimensional data of the objects
  int x;
  int y;
  // objects are divided into two types
  dat_type type;
 public:
};

void ReadDat(vector <Dat>& d_vec, char* f_name);