#pragma once

#include "dat.h"
#include <vector>
#include <Eigen/Dense>
#include <array>

using namespace std;
using namespace Eigen;

class DatSet {
 private:
  vector <Dat> datset_;
  // n[TYPE_ALL] is quantity of all data
  // n[TYPE_A, TYPE_B...] are quantities of each type
  array <int, TYPE_CNT> n;
  // m[...] are mean vectors
  // the format of the array m is the same as n
  array <Dat, TYPE_CNT> m;
  void DatSetInit();  // initializes n and m
 public:
   DatSet(const char* f_name);
   ~DatSet();
   // calculates The within-class scatter matrix of type i
   void CalSwi(Matrix2i& Sw_i, DatType t);
};

static void ReadDat(vector <Dat>& d_vec, const char* f_name);
static int char2int(char* s);