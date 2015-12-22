#pragma once

#include "dat.h"
#include <Eigen/Dense>
#include <array>

using namespace std;
using namespace Eigen;

class DatSet {
 public:
  vector <Dat> datset_;
  // n[TYPE_ALL] is quantity of all data
  // n[TYPE_A, TYPE_B...] are quantities of each type
  array <int, TYPE_CNT> n;
  // m[...] are mean vectors
  // the format of the array m is the same as n
  array <Dat, TYPE_CNT> m;
  void DatSetInit();  // initializes n and m
  DatSet(const char* f_name);
  ~DatSet();
  // Calculate the within-class scatter matrix of type i
  void CalSwi(Matrix2d& Sw_i, DatType t);
  // Calculate the within-class scatter matrix Sw
  void CalSwSum(Matrix2d& Sw);
  // Calculate inverse matrix of Sw
  void CalSwSumInv(Matrix2d& Sw_inv);
};