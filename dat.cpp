#include "dat.h"

using namespace std;

Dat::Dat(const array<double, 2>& a) : xy_(a) {}

Dat::Dat(double x, double y) {
  xy_[0] = x;
  xy_[1] = y;
}

Dat::~Dat() {}

Dat& Dat::operator= (const Dat& d) {
  xy_[0] = d.xy_[0];
  xy_[1] = d.xy_[1];
  return *this;
}

Dat& Dat::operator+= (const Dat& d) {
  *this = xy_ + d;
  return *this;
}

Dat& Dat::operator/= (int n) {
  *this = xy_ / n;
  return *this;
}

Dat operator+ (const Dat& d1, const Dat& d2) {
  return Dat(d1.xy_[0] + d2.xy_[0], d1.xy_[1] + d2.xy_[1]);
}

Dat operator/ (const Dat& d, int n) {
  return Dat(d.xy_[0] / n, d.xy_[1] / n);
}