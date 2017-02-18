

#include "visualization/button.hpp"

namespace visualization{

#define SCOPE Button

SCOPE::Button(std::string text, cv::Point2i topleft, uint32_t height, uint32_t width)
  :text_(text)
  ,height_(height)
  ,width_(width)
  ,topLeft_(topleft)
  ,state_(OFF)
{

  //cv::namedWindow("Button Off", cv::WINDOW_NORMAL);
  //cv::namedWindow("Button On", cv::WINDOW_NORMAL);
  //cv::namedWindow("Button Hover", cv::WINDOW_NORMAL);

  // Create Matrices
  buttonHover_ = cv::Mat(height_,width_,CV_32FC3);
  buttonOn_ = cv::Mat(height_,width_,CV_32FC3);
  buttonOff_ = cv::Mat(height_,width_,CV_32FC3);

  // Fill buttons
  buttonOn_ = cv::Scalar(0.3,0.3,0.3);
  buttonOff_ = cv::Scalar(0.5,0.5,0.5);
  buttonHover_ = cv::Scalar(0.4,0.4,0.4);

  // Draw borders
  cv::line(buttonOff_, cv::Point(0,0),cv::Point(buttonOff_.cols-1, 0),cv::Scalar(0.6,0.6,0.6));
  cv::line(buttonOff_, cv::Point(0,1),cv::Point(buttonOff_.cols-1, 1),cv::Scalar(0.7,0.7,0.7));
  cv::line(buttonOff_, cv::Point(0,0),cv::Point(0, buttonOff_.rows-1),cv::Scalar(0.6,0.6,0.6));
  cv::line(buttonOff_, cv::Point(1,0),cv::Point(1, buttonOff_.rows-1),cv::Scalar(0.7,0.7,0.7));

  cv::line(buttonOff_, cv::Point(0,buttonOff_.rows-1),cv::Point(buttonOff_.cols-1, buttonOff_.rows-1),cv::Scalar(0.2,0.2,0.2));
  cv::line(buttonOff_, cv::Point(buttonOff_.cols-1,0),cv::Point(buttonOff_.cols-1, buttonOff_.rows-1),cv::Scalar(0.3,0.3,0.3));
  cv::line(buttonOff_, cv::Point(0,buttonOff_.rows-2),cv::Point(buttonOff_.cols-2, buttonOff_.rows-2),cv::Scalar(0.2,0.2,0.2));
  cv::line(buttonOff_, cv::Point(buttonOff_.cols-2,0),cv::Point(buttonOff_.cols-2, buttonOff_.rows-2),cv::Scalar(0.3,0.3,0.3));


  cv::line(buttonOn_, cv::Point(0,0),cv::Point(buttonOn_.cols-1, 0),cv::Scalar(0.2,0.2,0.2));
  cv::line(buttonOn_, cv::Point(0,1),cv::Point(buttonOn_.cols-1, 1),cv::Scalar(0.3,0.3,0.3));
  cv::line(buttonOn_, cv::Point(0,0),cv::Point(0, buttonOn_.rows-1),cv::Scalar(0.2,0.2,0.2));
  cv::line(buttonOn_, cv::Point(1,0),cv::Point(1, buttonOn_.rows-1),cv::Scalar(0.3,0.3,0.3));

  cv::line(buttonOn_, cv::Point(0,buttonOn_.rows-1),cv::Point(buttonOn_.cols-1, buttonOn_.rows-1),cv::Scalar(0.5,0.5,0.5));
  cv::line(buttonOn_, cv::Point(buttonOn_.cols-1,0),cv::Point(buttonOn_.cols-1, buttonOn_.rows-1),cv::Scalar(0.6,0.6,0.6));
  cv::line(buttonOn_, cv::Point(0,buttonOn_.rows-2),cv::Point(buttonOn_.cols-2, buttonOn_.rows-2),cv::Scalar(0.5,0.5,0.5));
  cv::line(buttonOn_, cv::Point(buttonOn_.cols-2,0),cv::Point(buttonOn_.cols-2, buttonOn_.rows-2),cv::Scalar(0.6,0.6,0.6));


  cv::line(buttonHover_, cv::Point(0,0),cv::Point(buttonHover_.cols-1, 0),cv::Scalar(0.6,0.6,0.6));
  cv::line(buttonHover_, cv::Point(0,1),cv::Point(buttonHover_.cols-1, 1),cv::Scalar(0.7,0.7,0.7));
  cv::line(buttonHover_, cv::Point(0,0),cv::Point(0, buttonHover_.rows-1),cv::Scalar(0.6,0.6,0.6));
  cv::line(buttonHover_, cv::Point(1,0),cv::Point(1, buttonHover_.rows-1),cv::Scalar(0.7,0.7,0.7));

  cv::line(buttonHover_, cv::Point(0,buttonHover_.rows-1),cv::Point(buttonHover_.cols-1, buttonHover_.rows-1),cv::Scalar(0.2,0.2,0.2));
  cv::line(buttonHover_, cv::Point(buttonHover_.cols-1,0),cv::Point(buttonHover_.cols-1, buttonHover_.rows-1),cv::Scalar(0.3,0.3,0.3));
  cv::line(buttonHover_, cv::Point(0,buttonHover_.rows-2),cv::Point(buttonHover_.cols-2, buttonHover_.rows-2),cv::Scalar(0.2,0.2,0.2));
  cv::line(buttonHover_, cv::Point(buttonHover_.cols-2,0),cv::Point(buttonHover_.cols-2, buttonHover_.rows-2),cv::Scalar(0.3,0.3,0.3));



  // Put text
  cv::Size textsize = getTextSize(text_, cv::FONT_HERSHEY_DUPLEX, 1,1,0);
  cv::putText(buttonOff_, text_, cv::Point((width_-textsize.width)*0.5,(height_+textsize.height)*0.5),cv::FONT_HERSHEY_DUPLEX, 1,cv::Scalar(0.0,0.0,0.0));
  cv::putText(buttonOn_, text_, cv::Point((width_-textsize.width)*0.5,(height_+textsize.height)*0.5),cv::FONT_HERSHEY_DUPLEX, 1,cv::Scalar(0.0,0.0,0.0));
  cv::putText(buttonHover_, text_, cv::Point((width_-textsize.width)*0.5,(height_+textsize.height)*0.5),cv::FONT_HERSHEY_DUPLEX, 1,cv::Scalar(0.8,0.0,0.0));

  roi_ = cv::Rect(topLeft_.x,topLeft_.y,width_,height_);

  /*imshow("Button Off",buttonOff_);
  cv::waitKey(30);
  imshow("Button Hover",buttonHover_);
  cv::waitKey(30);

  imshow("Button On", buttonOn_);
  cv::waitKey(0);*/
}

SCOPE::~Button(){

}

bool SCOPE::isInside(uint32_t x, uint32_t y){

 if(x >= topLeft_.x && y >= topLeft_.y && x <= topLeft_.x + width_ && y <= topLeft_.y + height_){
  return true;
 }
 else{
   return false;
 }

}

uint32_t SCOPE::getWidth(){
  return width_;
}

uint32_t SCOPE::getHeight(){
  return height_;
}

cv::Point2i SCOPE::getTopLeft(){

  return topLeft_;
}

cv::Rect SCOPE::getRoi(){
  return roi_;
}

void SCOPE::setCallback(std::function<void(void)> cb_func, std::function<void(void)> cb_func2){
 cb_func_ = cb_func;
 cb_func2_ = cb_func2;
}

void SCOPE::activateEffect(){
  cb_func_();
}

void SCOPE::deactivateEffect(){
  cb_func2_();
}

#undef SCOPE

}
