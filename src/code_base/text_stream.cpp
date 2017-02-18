
#include "visualization/text_stream.hpp"

namespace visualization{

#define SCOPE TextStream

SCOPE::TextStream(std::string text, cv::Point2i topleft, cv::Point3f color)
  :text_(text)
  ,topLeft_(topleft)
  ,color_(color)
  ,changed_(false)
{

  // Put text
  cv::Size textsize = getTextSize(text_, cv::FONT_HERSHEY_DUPLEX, 1,1,0);

  // Create Matrices
  image_ = cv::Mat(textsize.height,textsize.width,CV_32FC3);
  image_ = cv::Scalar(color_.x,color_.y,color_.z);

  cv::putText(image_, text_, cv::Point(0,textsize.height-1),cv::FONT_HERSHEY_DUPLEX, 1,cv::Scalar(0.0,0.0,0.0));

  roi_ = cv::Rect(topLeft_.x,topLeft_.y,textsize.width,textsize.height);

}

SCOPE::~TextStream(){

}

cv::Point2i SCOPE::getTopLeft(){

  return topLeft_;
}

cv::Rect SCOPE::getRoi(){
  return roi_;
}

void SCOPE::setText(std::string text, cv::Point3f color){

  changed_ = true;

  cv::Size textsize = getTextSize(text, cv::FONT_HERSHEY_DUPLEX, 1,1,0);

  image_= cv::Mat(textsize.height,textsize.width, CV_32FC3);
  image_ = cv::Scalar(color_.x,color_.y,color_.z);

  cv::putText(image_, text, cv::Point(0,textsize.height-1),cv::FONT_HERSHEY_DUPLEX, 1,cv::Scalar(0.0,0.0,0.0));

  roi_ = cv::Rect(topLeft_.x,topLeft_.y,textsize.width,textsize.height);

}

bool SCOPE::changed(){
  return changed_;
}

void SCOPE::setUnchanged(){
  changed_ = false;
}


#undef SCOPE

}
