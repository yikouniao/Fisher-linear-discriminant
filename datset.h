#pragma once

#include "dat.h"
#include <Eigen/Dense>
#include <array>
#include <vector>
#include <string>

class DatSet {
 public:
   std::vector <Dat> datset_;
  // n[TYPE_A, TYPE_B...] are quantities of each type
  // n[TYPE_ALL] is quantity of all data
  std::array <int, TYPE_ALL_PLUS_1> n;
  // m[...] are mean vectors
  // the format of the array m is the same as n
  std::array <Dat, TYPE_ALL_PLUS_1> m;
  void DatSetInit();  // initializes n and m
  DatSet(const char* f_name);
  ~DatSet();
  // Calculate the within-class scatter matrix of type i
  void CalSwi(Eigen::Matrix2d& Sw_i, DatType t);
  void CalSwi(Eigen::Matrix2d& Sw_i, int t);
  // Calculate the within-class scatter matrix Sw
  void CalSwSum(Eigen::Matrix2d& Sw);
  // Calculate inverse matrix of Sw
  void CalSwSumInv(Eigen::Matrix2d& Sw_inv);
};