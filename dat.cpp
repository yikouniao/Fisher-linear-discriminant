#include "dat.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <array>

Dat::Dat() : x_(0), y_(0), type_(TYPE_ALL) {}

Dat::Dat(const Dat& d) : x_(d.x_), y_(d.y_), type_(d.type_) {}

Dat::Dat(double x, double y, DatType type) : x_(x), y_(y), type_(type) {}

Dat::~Dat() {}

Dat& Dat::operator= (const Dat& d) {
  x_ = d.x_;
  y_ = d.y_;
  type_ = d.type_;
  return *this;
}

Dat& Dat::operator+= (const Dat& d) {
  if (d.type_ != type_) {
    type_ = TYPE_ALL;
  }
  x_ += d.x_;
  y_ += d.y_;
  return *this;
}

Dat& Dat::operator/= (int n) {
  x_ /= n;
  y_ /= n;
  return *this;
}

Dat operator- (const Dat& d1, const Dat& d2) {
  return Dat(d1.x_ - d2.x_, d1.y_ - d2.y_,
             (d1.type_ == d2.type_) ? d1.type_ : TYPE_ALL);
}

DatType& operator++ (DatType& t) {
  t = static_cast<DatType>(t + 1);
  return t;
}

DatType operator+ (const DatType& t1, const int i) {
  return static_cast<DatType>(static_cast<int>(t1) + i);
}

void ReadDat(vector <Dat>& d_vec, const char* f_name) {
  ifstream f_dat(f_name);
  if (!f_dat)
  {
    cerr << f_name << " could not be opened!\n" << endl;
    exit(1);
  }
  array<double, 2> xy;
  array<char, 5> c;
  while (1) {
    f_dat.getline(&c[0], 65532, ' ');  // read x_
    if (c[0] == '#')
      break;
    xy[0] = char2double(&c[0]);
    f_dat.getline(&c[0], 65532, ' ');  // read y_
    xy[1] = char2double(&c[0]);
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

static double char2double(char* s) {
  char* p{ s };  // save the start position of the string
  double a{ 0 };
  while (*s) {  // let s point to '\0'
    ++s;
  }
  int i{ 0 };
  while (!(--s < p)) {
    a += (*s - 48) * pow(10, i++);
  }
  return a;
}