#pragma once

#include "Fisher/Fisher-datset.h"
#include <opencv.hpp>
#include <highgui.hpp>
#include <vector>

const int width = 300, height = 300;  // range of pic
// Correspond to each DatType
const std::vector<cv::Vec3b> color{ cv::Vec3b(255, 0, 0),
                                    cv::Vec3b(0, 255, 0),
                                    cv::Vec3b(255, 255, 255) };  // TYPE_ALL

void Dat2Pic(FisherDatSet& ds, const char* win_name);