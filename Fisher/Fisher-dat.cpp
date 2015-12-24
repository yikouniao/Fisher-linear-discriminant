#include "Fisher-dat.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <array>

using namespace std;
using namespace Eigen;

FisherDat::FisherDat() : Dat(0, 0), type_(TYPE_ALL) {}

FisherDat::FisherDat(const FisherDat& d) : Dat(d.xy_), type_(d.type_) {}

FisherDat::FisherDat(double x, double y, FisherDatType type)
    : Dat(x, y), type_(type) {}

FisherDat::FisherDat(double x, double y, int type)
    : Dat(x, y), type_(static_cast<FisherDatType>(type)) {}

FisherDat::~FisherDat() {}

FisherDat& FisherDat::operator= (const FisherDat& d) {
  xy_ = d.xy_;
  type_ = d.type_;
  return *this;
}

FisherDat& FisherDat::operator+= (const FisherDat& d) {
  if (d.type_ != type_) {
    type_ = TYPE_ALL;
  }
  xy_[0] += d.xy_[0];
  xy_[1] += d.xy_[1];
  return *this;
}

FisherDat& FisherDat::operator/= (int n) {
  xy_[0] /= n;
  xy_[1] /= n;
  return *this;
}

FisherDat operator+ (const FisherDat& d1, const FisherDat& d2) {
  return FisherDat(d1.xy_[0] + d2.xy_[0], d1.xy_[1] + d2.xy_[1],
                   (d1.type_ == d2.type_) ? d1.type_ : TYPE_ALL);
}

FisherDat operator- (const FisherDat& d1, const FisherDat& d2) {
  return FisherDat(d1.xy_[0] - d2.xy_[0], d1.xy_[1] - d2.xy_[1],
                   (d1.type_ == d2.type_) ? d1.type_ : TYPE_ALL);
}

FisherDat::operator Eigen::Vector2d() {
  return Vector2d(xy_[0], xy_[1]);
}

void ReadFisherDat(vector <FisherDat>& d_vec, const char* f_name) {
  ifstream f_dat(f_name);
  if (!f_dat)
  {
    cerr << f_name << " could not be opened!\n" << endl;
    exit(1);
  }
  array<double, 2> xy;
  array<char, 5> c;
  while (1) {
    f_dat.getline(&c[0], 65532, '\t');  // read x_
    if (c[0] == '#')
      break;
    xy[0] = char2double(&c[0]);
    f_dat.getline(&c[0], 65532, '\t');  // read y_
    xy[1] = char2double(&c[0]);
    f_dat.getline(&c[0], 65532, '\n');  // read type_
    FisherDatType dat_type;
    if (c[0] == 'a') {
      dat_type = TYPE_A;
    } else if (c[0] == 'b') {
      dat_type = TYPE_B;
    } else if (c[0] == 'c') {
      dat_type = TYPE_C;
    }
    else {
      dat_type = TYPE_ALL;
    }
    d_vec.push_back(FisherDat{ xy[0], xy[1], dat_type });
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

FisherDatType& operator++ (FisherDatType& t) {
  t = static_cast<FisherDatType>(t + 1);
  return t;
}

FisherDatType operator+ (const FisherDatType& t1, const int i) {
  return static_cast<FisherDatType>(static_cast<int>(t1) + i);
}