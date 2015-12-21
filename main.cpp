#include <opencv.hpp>
#include <highgui.hpp>
#include "datset.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
  //Matrix2d ab;
  //ab << 1, 2,
  //     3, 4;
  //std::cout << "a * 2.5 =\n" << ab * 2.5 << std::endl;
  if (argc < 3) {
    return -1;
  }
  DatSet train(argv[1]);
  Matrix2i Swi = Matrix2i::Zero();
  cout << Swi;
  train.CalSwi(Swi, TYPE_A);
  waitKey(0);
  return 0;
}