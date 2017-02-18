#pragma once
#include <stdlib.h>
#include <functional>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace visualization{

class Button{

public:
  Button(std::string text, cv::Point2i topleft, uint32_t height, uint32_t width);
  ~Button();

  void setCallback(std::function<void(void)> cb_func, std::function<void(void)> cb_func2 = [](){});

  void activateEffect();

  void deactivateEffect();

  cv::Rect getRoi();

  bool isInside(uint32_t x, uint32_t y);

  uint32_t getWidth();
  uint32_t getHeight();
  cv::Point2i getTopLeft();
   cv::Mat buttonHover_, buttonOn_,buttonOff_;

  enum ButtonState{OFF,ON} state_;

protected:

  std::function<void(void)> cb_func_;
  std::function<void(void)> cb_func2_;

  cv::Point2i topLeft_;
  uint32_t height_;
  uint32_t width_;

  std::string text_;

  cv::Point3f color_;

  cv::Rect roi_;



};



}
