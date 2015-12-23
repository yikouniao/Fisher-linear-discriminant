#include <opencv.hpp>
#include <highgui.hpp>
#include "datset.h"
#include "sample.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
  if (argc < 3) {
    return -1;
  }
  DatSet train(argv[1]);
  DatSet test(argv[2]);
  DatSet result = test;
  SamFisher(train, test, result);
  waitKey(0);
  return 0;
}