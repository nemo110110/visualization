

#include "visualization/image_view.hpp"

namespace visualization{

#define SCOPE ImageView

SCOPE::ImageView(std::string text, cv::Point2i topleft, uint32_t height, uint32_t width)
  :text_(text)
  ,height_(height)
  ,width_(width)
  ,topLeft_(topleft)
{



  // Create Matrices
  image_ = cv::Mat(height_,width_,CV_32FC3);


   // Put text
  cv::Size textsize = getTextSize(text_, cv::FONT_HERSHEY_DUPLEX, 1,1,0);
  cv::putText(image_, text_, cv::Point(topLeft_.x + 10, topLeft_.y + 10),cv::FONT_HERSHEY_DUPLEX, 1,cv::Scalar(0.0,0.0,0.0));

  roi_ = cv::Rect(topLeft_.x,topLeft_.y,width_,height_);

}

SCOPE::~ImageView(){

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

void SCOPE::setCallback(std::function<void(void)> cb_func){
 cb_func_ = cb_func;
}

void SCOPE::activateEffect(){
  cb_func_();
}

void SCOPE::setImageSource(cv::Mat* externalSource){
  imagePtr_ = externalSource;
}

std::string& SCOPE::getText(){
  return text_;
}

#undef SCOPE

}
