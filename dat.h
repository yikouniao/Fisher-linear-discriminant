#pragma once
#include <vector>

using namespace std;

enum DatType { TYPE_A, TYPE_B};

class Dat {
 private:
  // two-dimensional data of the objects
  int x_;
  int y_;
  // objects are divided into two types
  DatType type_;
 public:
   Dat(int x, int y, DatType type);
   ~Dat();
};

void ReadDat(vector <Dat>& d_vec, const char* f_name);
static int char2int(char* s);