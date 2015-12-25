#include "H-K-dat.h"

namespace HK {
using namespace Eigen;

Dat::Dat() : xy_(Vector3d(0, 0, 1)), type_(TYPE_ALL) {}

Dat::Dat(const std::array<double, 2>& xy, DatType type) {
  xy_ = Vector3d(xy[0], xy[1], 1);
  type_ = type;
}

Dat::~Dat() {}
} // namespace HK