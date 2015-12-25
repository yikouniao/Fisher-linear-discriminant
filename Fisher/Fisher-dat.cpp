#include "Fisher-dat.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <array>

namespace Fisher {
using namespace std;
using namespace Eigen;

Dat::Dat() : type_(TYPE_ALL) {
  xy_[0] = 0;
  xy_[1] = 0;
}

Dat::Dat(const Dat& d) : xy_(d.xy_), type_(d.type_) {}

Dat::Dat(double x, double y, DatType type) : type_(type) {
  xy_[0] = x;
  xy_[1] = y;
}

Dat::Dat(double x, double y, int type)
    : type_(static_cast<DatType>(type)) {
  xy_[0] = x;
  xy_[1] = y;
}

Dat::~Dat() {}

Dat& Dat::operator= (const Dat& d) {
  xy_ = d.xy_;
  type_ = d.type_;
  return *this;
}

Dat& Dat::operator+= (const Dat& d) {
  if (d.type_ != type_) {
    type_ = TYPE_ALL;
  }
  xy_[0] += d.xy_[0];
  xy_[1] += d.xy_[1];
  return *this;
}

Dat& Dat::operator/= (int n) {
  xy_[0] /= n;
  xy_[1] /= n;
  return *this;
}

Dat operator+ (const Dat& d1, const Dat& d2) {
  return Dat(d1.xy_[0] + d2.xy_[0], d1.xy_[1] + d2.xy_[1],
             (d1.type_ == d2.type_) ? d1.type_ : TYPE_ALL);
}

Dat operator- (const Dat& d1, const Dat& d2) {
  return Dat(d1.xy_[0] - d2.xy_[0], d1.xy_[1] - d2.xy_[1],
             (d1.type_ == d2.type_) ? d1.type_ : TYPE_ALL);
}

Dat::operator Eigen::Vector2d() {
  return Vector2d(xy_[0], xy_[1]);
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
    f_dat.getline(&c[0], 65532, '\t');  // read x_
    if (c[0] == '#')
      break;
    xy[0] = char2double(&c[0]);
    f_dat.getline(&c[0], 65532, '\t');  // read y_
    xy[1] = char2double(&c[0]);
    f_dat.getline(&c[0], 65532, '\n');  // read type_
    DatType dat_type;
    if (c[0] == 'a') {
      dat_type = TYPE_A;
    } else if (c[0] == 'b') {
      dat_type = TYPE_B;
    } else if (c[0] == 'c') {
      dat_type = TYPE_C;
    } else {
      dat_type = TYPE_ALL;
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

DatType& operator++ (DatType& t) {
  t = static_cast<DatType>(t + 1);
  return t;
}

DatType operator+ (const DatType& t1, const int i) {
  return static_cast<DatType>(static_cast<int>(t1) + i);
}
}  // namespace Fisher