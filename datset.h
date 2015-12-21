#pragma once

#include "dat.h"
#include <vector>

using namespace std;

class DatSet {
 private:
  vector <Dat> datset_;
  int n1_, n2_;  // quantities of each type
  Dat m1_, m2_;  // mean vectors of each type
  void DatSetInit();  // initializes n and m
 public:
   DatSet(const char* f_name);
   ~DatSet();
};

static void ReadDat(vector <Dat>& d_vec, const char* f_name);
static int char2int(char* s);