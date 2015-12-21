#include "dat.h"
#include <iostream>

Dat::Dat() : x_(0), y_(0), type_(TYPE_UNKNOWN) {}

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
    std::cerr << "Cannot add data of different type!\n";
  } else {
    x_ += d.x_;
    y_ += d.y_;
  }
  return *this;
}

Dat& Dat::operator/= (int n) {
  x_ /= n;
  y_ /= n;
  return *this;
}

DatType& Dat::ReadType() {
  return type_;
}