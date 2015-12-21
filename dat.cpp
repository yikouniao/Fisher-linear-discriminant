#include "dat.h"
#include <iostream>

Dat::Dat() : x_(0), y_(0), type_(TYPE_ALL) {}

Dat::Dat(const Dat& d) : x_(d.x_), y_(d.y_), type_(d.type_) {}

Dat::Dat(int x, int y, DatType type) : x_(x), y_(y), type_(type) {}

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