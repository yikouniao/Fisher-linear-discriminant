#pragma once
#include "H-K-dat.h"
#include <Eigen/Dense>
#include <array>
#include <vector>

// H-K algorithm
namespace HK {
typedef std::vector<Dat> DatSet;

void InitDatSet(DatSet& ds, char* f_name);
static double char2double(char* s);

// parameters of discriminant function
class D_F
{
 public:
  Eigen::Vector3d w_; // weight vector
  double p_; // step size
  double threshold_; // for e equals to 0, positive

  D_F();
  ~D_F();
  // set p_
  void SetP(double p);
  // set threshold_
  void SetThreshold(double threshold);
  // train the weight vector
  void Train(DatSet& ds);
  // use the weight vector to classify patterns
  void Test(DatSet& ds);
  // output the weight vector
  void Out();
  // Calculate the error rate, assume standard is reference data
  void ErrRate(DatSet& standard, DatSet& comparison);
};

template <typename Derived>
bool IsLittle(const Eigen::MatrixBase<Derived>& m, double threshold) {
  for (int i = 0; i < m.rows(); ++i) {
    for (int j = 0; j < m.cols(); ++j) {
      if(m(i, j) > threshold && m(i, j) < -threshold)
        return false;
    }
  }
  return true;
}
} // namespace HK