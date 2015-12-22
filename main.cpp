#include <opencv.hpp>
#include <highgui.hpp>
#include "datset.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
  if (argc < 3) {
    return -1;
  }
  DatSet train(argv[1]);
  Matrix2d Sw_inv;
  train.CalSwSumInv(Sw_inv);
  cout << Sw_inv << '\n';
  waitKey(0);
  return 0;
}