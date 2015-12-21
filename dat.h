#pragma once

enum DatType { TYPE_UNKNOWN, TYPE_A, TYPE_B};

class Dat {
 private:
  // two-dimensional data of the objects
  int x_;
  int y_;
  // objects are divided into two types
  DatType type_;
 public:
   Dat();
   Dat(int x, int y, DatType type);
   ~Dat();
   Dat& operator= (const Dat& d);
   Dat& operator+= (const Dat& d);
   Dat& operator/= (const int n);
   DatType& ReadType();
};