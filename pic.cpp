#include "pic.h"

using namespace std;
using namespace cv;

void Dat2Pic(FisherDatSet& ds, const char* win_name) {
  Mat M(width, height, CV_8UC3, Scalar::all(0));
  for (auto& e : ds.datset_) {
    M.at<Vec3b>(static_cast<int>(e.x_), static_cast<int>(e.y_)) = color[e.type_];
  }
  namedWindow(win_name);
  imshow(win_name, M);
}