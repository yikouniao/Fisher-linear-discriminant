#pragma once

#include "datset.h"
#include <opencv.hpp>
#include <highgui.hpp>
#include <vector>

using namespace std;
using namespace cv;

const int width = 300, height = 300;  // range of pic
// Correspond to each DatType except TYPE_CNT
const vector<Vec3b> color{ Vec3b(0, 0, 0), Vec3b(255, 0, 0), Vec3b(0, 255, 0) };

void Dat2Pic(DatSet& ds, const char* win_name);