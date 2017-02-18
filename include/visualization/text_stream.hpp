#pragma once
#include <stdlib.h>
#include <functional>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace visualization{

class TextStream{

public:
  TextStream(std::string text, cv::Point2i topleft, cv::Point3f color);
  ~TextStream();

  cv::Rect getRoi();

  void setText(std::string text, cv::Point3f color = cv::Point3f(0.0f,0.0f,0.0f));

  void setUnchanged();

  cv::Point2i getTopLeft();

  bool changed();

  cv::Mat image_;

protected:

  cv::Point2i topLeft_;

  bool changed_;

  std::string text_;

  cv::Point3f color_;

  cv::Rect roi_;



};
}
