#pragma once

#include <array>

class Dat {
 public:
  // two-dimensional data of the objects
  std::array<double, 2> xy_;

  Dat(const std::array<double, 2>& a);
  Dat(double x = 0, double y = 0);
  ~Dat();
  Dat& operator= (const Dat& d);
  Dat& operator+= (const Dat& d);
  Dat& operator/= (int n);
  friend Dat operator+ (const Dat& d1, const Dat& d2);
  friend Dat operator/ (const Dat& d, int n);
};