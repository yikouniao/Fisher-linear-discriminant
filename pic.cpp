#include "pic.h"

using namespace std;
using namespace cv;

namespace Fisher {
void Dat2Pic(DatSet& ds, const char* win_name) {
  Mat M(width, height, CV_8UC3, Scalar::all(0));
  for (auto& e : ds.datset_) {
    M.at<Vec3b>(static_cast<int>(e.xy_[0]),
                static_cast<int>(e.xy_[1])) = color[e.type_];
  }
  namedWindow(win_name);
  imshow(win_name, M);
}
}  // namespace Fisher

namespace Percp {
void Dat2Pic(DatSet& ds, const char* win_name) {
  Mat M(width, height, CV_8UC3, Scalar::all(0));
  for (auto& e : ds) {
    M.at<Vec3b>(static_cast<int>(e.xy_[0]),
                static_cast<int>(e.xy_[1])) = color[e.type_];
  }
  namedWindow(win_name);
  imshow(win_name, M);
}
} // namespace Percp