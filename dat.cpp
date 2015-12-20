#include "dat.h"
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <cmath>

Dat::Dat(int x, int y, DatType type) : x_(x), y_(y), type_(type) {}

Dat::~Dat() {}

void ReadDat(vector <Dat>& d_vec, const char* f_name) {
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
    } else {  // dat_c[0] == 'b'
      dat_type = TYPE_B;
    }
    d_vec.push_back(Dat { dat_xy[0], dat_xy[1], dat_type });
  }  // while (1)
}

static int char2int(char* s) {
  char* p { s };  // save the start position of the string
  int a { 0 };
  while (*s) {  // let s point to '\0'
    ++s;
  }
  int i { 0 };
  while (!(--s < p)) {
    a += (*s - 48) * static_cast<int>(pow(10, i++));
  }
  return a;
}