#pragma once

#include <vector>
#include <Eigen/Dense>

enum DatType { TYPE_MINUS_1 = -1, TYPE_A, TYPE_B, TYPE_ALL, TYPE_ALL_PLUS_1};

// minimum number of discriminant function
const int n_df{(TYPE_ALL - 1) * TYPE_ALL / 2};

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
  Dat(double x, double y, int type);
  ~Dat();
  Dat& operator= (const Dat& d);
  Dat& operator+= (const Dat& d);
  Dat& operator/= (const int n);
  friend Dat operator+ (const Dat& d1, const Dat& d2);
  friend Dat operator- (const Dat& d1, const Dat& d2);
  operator Eigen::Vector2d();
};

void ReadDat(std::vector <Dat>& d_vec, const char* f_name);
static double char2double(char* s);