#include <opencv.hpp>
#include <highgui.hpp>
#include <Eigen/Dense>
#include <vector>
#include "dat.h"

using namespace std;
using namespace Eigen;
using namespace cv;

int main(int argc, char** argv)
{
  Matrix2d ab;
  ab << 1, 2,
       3, 4;
  std::cout << "a * 2.5 =\n" << ab * 2.5 << std::endl;
  if (argc < 3) {
    return -1;
  }
  vector <Dat> train;
  ReadDat(train, argv[1]);
  waitKey(0);
  return 0;
}