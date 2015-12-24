#include "Fisher-datset.h"

using namespace std;
using namespace Eigen;

namespace Fisher {
DatSet::DatSet(const char* f_name) {
  ReadDat(datset_, f_name);
  DatSetInit();
}

DatSet::~DatSet() {}

void DatSet::DatSetInit() {
  // Set all data to 0
  for (int i = TYPE_MINUS_1 + 1; i <= TYPE_ALL; ++i) {
    n[i] = 0;
    m[i] = Dat(0, 0, i);
  }
  // Calculate sum
  for (auto& e : datset_)
  {
    n[TYPE_ALL] += 1;
    m[TYPE_ALL] += e;
    n[e.type_] += 1;
    m[e.type_] += e;
  }
  // Calculate mean
  for (int i = TYPE_MINUS_1 + 1; i <= TYPE_ALL; ++i) {
    m[i] /= n[i];
  }
}

void DatSet::CalSwi(Matrix2d& Sw_i, DatType t) const {
  for (auto& e : datset_) {
    if (e.type_ == t) {
      Dat d {e - m[t]};
      Vector2d v(d.xy_[0], d.xy_[1]);
      Sw_i += v * v.transpose();
    }
  }
}

void DatSet::CalSwi(Matrix2d& Sw_i, int t) const {
  CalSwi(Sw_i, static_cast<DatType>(t));
}

void DatSet::CalSwSum(Matrix2d& Sw) const {
  for (int i = TYPE_MINUS_1 + 1; i < TYPE_ALL; ++i) {
    Matrix2d Swi = Matrix2d::Zero();
    CalSwi(Swi, i);
    Sw += Swi;
  }
}

void DatSet::CalSwSumInv(Matrix2d& Sw_inv) const {
  Matrix2d Sw = Matrix2d::Zero();
  CalSwSum(Sw);
  Sw_inv = Sw.inverse();
}
}  // namespace Fisher