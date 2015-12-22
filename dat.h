#pragma once

#include <vector>

using namespace std;

enum DatType { TYPE_ALL = 0, TYPE_A, TYPE_B, TYPE_CNT};

DatType& operator++ (DatType& t);
DatType operator+ (const DatType& t1, const int i);

class Dat {
 public:
  // two-dimensional data of the objects
  double x_;
  double y_;
  // objects are divided into two types
  DatType type_;

  Dat();
  Dat(const Dat& d);
  Dat(double x, double y, DatType type);
  ~Dat();
  Dat& operator= (const Dat& d);
  Dat& operator+= (const Dat& d);
  Dat& operator/= (const int n);
  friend Dat operator- (const Dat& d1, const Dat& d2);
};

void ReadDat(vector <Dat>& d_vec, const char* f_name);
static double char2double(char* s);