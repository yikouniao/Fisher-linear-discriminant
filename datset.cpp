#include "datset.h"
#include <fstream>
#include <string>
#include <array>
#include <cmath>
#include <iostream>

DatSet::DatSet(const char* f_name) {
  ReadDat(datset_, f_name);
  DatSetInit();
}

DatSet::~DatSet() {}

static void ReadDat(vector <Dat>& d_vec, const char* f_name) {
  ifstream f_dat(f_name);
  if (!f_dat)
  {
    cerr << f_name << " could not be opened!\n" << endl;
    exit(1);
  }
  array<int, 2> dat_xy;
  array<char, 5> dat_c;
  while (1) {
    f_dat.getline(&dat_c[0], 65532, ' ');  // read x_
    if (dat_c[0] == '#')
      break;
    dat_xy[0] = char2int(&dat_c[0]);
    f_dat.getline(&dat_c[0], 65532, ' ');  // read y_
    dat_xy[1] = char2int(&dat_c[0]);
    f_dat.getline(&dat_c[0], 65532, '\n');  // read type_
    DatType dat_type;
    if (dat_c[0] == 'a') {
      dat_type = TYPE_A;
    }
    else {  // dat_c[0] == 'b'
      dat_type = TYPE_B;
    }
    d_vec.push_back(Dat{ dat_xy[0], dat_xy[1], dat_type });
  }  // while (1)
}

static int char2int(char* s) {
  char* p{ s };  // save the start position of the string
  int a{ 0 };
  while (*s) {  // let s point to '\0'
    ++s;
  }
  int i{ 0 };
  while (!(--s < p)) {
    a += (*s - 48) * static_cast<int>(pow(10, i++));
  }
  return a;
}

void DatSet::DatSetInit() {
  n1_ = n2_ = 0;
  m1_ = Dat(0, 0, TYPE_A);
  m2_ = Dat(0, 0, TYPE_B);
  for (auto& e : datset_)
  {
    if (e.ReadType() == TYPE_A) {
      n1_ += 1;
      m1_ += e;
    } else {  // e.ReadType() == TYPE_B
      n2_ += 1;
      m2_ += e;
    }
  }
  m1_ /= n1_;
  m2_ /= n2_;
}