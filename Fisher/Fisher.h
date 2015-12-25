#pragma once
#include "Fisher-datset.h"

namespace Fisher {
// parameters of discriminant function
class D_F {
 private:
// u_trans: the matrix transpose of u
// yt: threshold for dividing patterns
// The format of u_trans and yt is u_trans_mn or yt_mn,
// m is row, n is column:
// [0            yt_12        yt_13 ... yt_1TYPE_ALL]
// [yt_21        0            yt_23 ... yt_2TYPE_ALL]
// [...                       ...                   ]
// [yt_TYPE_ALL1 yt_TYPE_ALL2 ...                  0]
// yt_mn is threshold for pattern m and pattern n
// yt_mn = -yt_mn
// As for u_trans, the format is the same.
  std::array<std::array<Eigen::RowVector2d, TYPE_ALL>, TYPE_ALL> u_trans;
  std::array<std::array<double, TYPE_ALL>, TYPE_ALL> yt;
 public:
// Train Fisher's discriminant function
// ds: input data set
  void Train(DatSet& ds);
// std::cout the u_trans and yt
  void Out();
// Discriminate a single Dat data
// If don't want test to be covered by result,
// use DatSet result = test; or Dat result = test; before this function
  void DiscriDat(Dat& x);
// Discriminate a DatSet data
// If don't want test to be covered by result,
// use DatSet result = test; before this function
  void Discri(DatSet& ds);
// Calculate the error rate for train data
  void TrainErrRate(DatSet& ds);
// Calculate the error rate for test data
  void TestErrRate(DatSet& test, DatSet& result);
// Calculate the error rate, assume standard is reference data
  void ErrRate(DatSet& standard, DatSet& comparison);
};
}  // namespace Fisher