#include "Fisher-datset.h"

using namespace std;
using namespace Eigen;

FisherDatSet::FisherDatSet(const char* f_name) {
  ReadFisherDat(datset_, f_name);
  FisherDatSetInit();
}

FisherDatSet::~FisherDatSet() {}

void FisherDatSet::FisherDatSetInit() {
  // Set all data to 0
  for (int i = TYPE_MINUS_1 + 1; i <= TYPE_ALL; ++i) {
    n[i] = 0;
    m[i] = FisherDat(0, 0, i);
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

void FisherDatSet::CalSwi(Matrix2d& Sw_i, FisherDatType t) const {
  for (auto& e : datset_) {
    if (e.type_ == t) {
      FisherDat d {e - m[t]};
      Vector2d v(d.xy_[0], d.xy_[1]);
      Sw_i += v * v.transpose();
    }
  }
}

void FisherDatSet::CalSwi(Matrix2d& Sw_i, int t) const {
  CalSwi(Sw_i, static_cast<FisherDatType>(t));
}

void FisherDatSet::CalSwSum(Matrix2d& Sw) const {
  for (int i = TYPE_MINUS_1 + 1; i < TYPE_ALL; ++i) {
    Matrix2d Swi = Matrix2d::Zero();
    CalSwi(Swi, i);
    Sw += Swi;
  }
}

void FisherDatSet::CalSwSumInv(Matrix2d& Sw_inv) const {
  Matrix2d Sw = Matrix2d::Zero();
  CalSwSum(Sw);
  Sw_inv = Sw.inverse();
}