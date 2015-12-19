#include "dat.h"
#include <fstream>
#include <iostream>
#include <string>
#include <array>

void ReadDat(vector <Dat>& d_vec, char* f_name) {
  ifstream f_dat(f_name);
  if (!f_dat)
  {
    cerr << f_name << " could not be opened!\n" << endl;
    exit(1);
  }
  for (array<char, 4> a; f_dat.getline(&a[0], 65532, ' ');) {

  }
}