#include <opencv.hpp>
#include <highgui.hpp>
#include "sample.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
  if (argc < 3) {
    return -1;
  }
  SamFisher(argv[1], argv[2]);
  SamPercp(argv[3], argv[4]);
  waitKey(0);
  return 0;
}