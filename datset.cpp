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
  array<int, 2> xy;
  array<char, 5> c;
  while (1) {
    f_dat.getline(&c[0], 65532, ' ');  // read x_
    if (c[0] == '#')
      break;
    xy[0] = char2int(&c[0]);
    f_dat.getline(&c[0], 65532, ' ');  // read y_
    xy[1] = char2int(&c[0]);
    f_dat.getline(&c[0], 65532, '\n');  // read type_
    DatType dat_type;
    if (c[0] == 'a') {
      dat_type = TYPE_A;
    }
    else {  // c[0] == 'b'
      dat_type = TYPE_B;
    }
    d_vec.push_back(Dat{ xy[0], xy[1], dat_type });
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
  // Set all data to 0
  n.fill(0);
  for (DatType i = TYPE_ALL; i < TYPE_CNT; ++i) {
    m[i] = Dat(0, 0, i);
  }
  // Calculate sum
  for (auto& e : datset_)
  {
    n[TYPE_ALL] += 1;
    m[TYPE_ALL] += e;
    n[e.type_] += 1;
    m[e.type_] += e;
  }
  // Calculate mean
  for (DatType i = TYPE_ALL; i < TYPE_CNT; ++i) {
    m[i] /= n[i];
  }
}

void DatSet::CalSwi(Matrix2i& Sw_i, DatType t) {
  for (auto& e : datset_) {
    if (e.type_ == t) {
      Dat d {e - m[t]};
      Vector2i v(d.x_, d.y_);
      Sw_i += v * v.transpose();
      cout << Sw_i;
    }
  }
}