#pragma once
#include <Eigen/Dense>
#include <array>

namespace HK {
enum DatType { TYPE_MINUS_1 = -1, TYPE_A, TYPE_B, TYPE_ALL, TYPE_ALL_PLUS_1 };

class Dat {
 public:
  Eigen::Vector3d xy_;
  DatType type_;

  Dat();
  Dat(const std::array<double, 2>& xy_, DatType type);
  ~Dat();
};
} // namespace HK