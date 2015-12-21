#pragma once

enum DatType { TYPE_ALL = 0, TYPE_A, TYPE_B, TYPE_CNT};

DatType& operator++ (DatType& t);

class Dat {
 public:
  // two-dimensional data of the objects
  int x_;
  int y_;
  // objects are divided into two types
  DatType type_;

  Dat();
  Dat(const Dat& d);
  Dat(int x, int y, DatType type);
  ~Dat();
  Dat& operator= (const Dat& d);
  Dat& operator+= (const Dat& d);
  Dat& operator/= (const int n);
  friend Dat operator- (const Dat& d1, const Dat& d2);
};