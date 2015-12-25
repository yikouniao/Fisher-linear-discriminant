#pragma
#include "perception-dat.h"
#include <Eigen/Dense>
#include <array>
#include <vector>

// perception approach
namespace Percp {
typedef std::vector<Dat> DatSet;

void InitDatSet(DatSet& ds, char* f_name);
static double char2double(char* s);

// parameters of discriminant function
class D_F
{
 public:
  std::array<Eigen::Vector3d, TYPE_ALL> w_; // weight vector
  double p_; // step size

  D_F();
  ~D_F();
  // modify p_
  void SetP(double p);
  // train the weight vector
  void Train(DatSet& ds);
  // use the weight vector to classify patterns
  void Test(DatSet& ds);
  // output the weight vector
  void Out();
  // Calculate the error rate, assume standard is reference data
  void ErrRate(DatSet& standard, DatSet& comparison);
};
} // namespace Percp