#pragma once

#include <vector>
#include <Eigen/Dense>

enum FisherDatType { TYPE_MINUS_1 = -1, TYPE_A, TYPE_B, TYPE_ALL, TYPE_ALL_PLUS_1};

// minimum number of discriminant function
const int n_df{(TYPE_ALL - 1) * TYPE_ALL / 2};

FisherDatType& operator++ (FisherDatType& t);
FisherDatType operator+ (const FisherDatType& t1, const int i);

class FisherDat {
 public:
  // two-dimensional data of the objects
  double x_;
  double y_;
  // objects are divided into two types
  FisherDatType type_;

  FisherDat();
  FisherDat(const FisherDat& d);
  FisherDat(double x, double y, FisherDatType type);
  FisherDat(double x, double y, int type);
  ~FisherDat();
  FisherDat& operator= (const FisherDat& d);
  FisherDat& operator+= (const FisherDat& d);
  FisherDat& operator/= (const int n);
  friend FisherDat operator+ (const FisherDat& d1, const FisherDat& d2);
  friend FisherDat operator- (const FisherDat& d1, const FisherDat& d2);
  operator Eigen::Vector2d();
};

void ReadFisherDat(std::vector <FisherDat>& d_vec, const char* f_name);
static double char2double(char* s);