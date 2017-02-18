#pragma once
#include <stdlib.h>
#include <functional>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace visualization{

class ImageView{

public:
  ImageView(std::string text, cv::Point2i topleft, uint32_t height, uint32_t width);
  ~ImageView();

  void setCallback(std::function<void(void)> cb_func);

  void activateEffect();

  void setImageSource(cv::Mat* externalSource);

  cv::Rect getRoi();

  std::string& getText();

  bool isInside(uint32_t x, uint32_t y);

  uint32_t getWidth();
  uint32_t getHeight();
  cv::Point2i getTopLeft();
  cv::Mat* imagePtr_;
  cv::Mat image_;



protected:

  std::function<void(void)> cb_func_;

  cv::Point2i topLeft_;
  uint32_t height_;
  uint32_t width_;

  std::string text_;

  cv::Point3f color_;

  cv::Rect roi_;



};



}
