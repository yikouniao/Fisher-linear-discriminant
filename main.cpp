#include <opencv.hpp>
#include <highgui.hpp>
#include <Eigen/Dense> 

using namespace Eigen;
using namespace cv;

int main(int argc, char** argv)
{
  Matrix2d a;
  a << 1, 2,
       3, 4;
  std::cout << "a * 2.5 =\n" << a * 2.5 << std::endl;
  if (argc < 3) {
    return -1;
  }

  waitKey(0);
  return 0;
}