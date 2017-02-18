#include "visualization/gui.hpp"
#include <iostream>

namespace visualization {

#define SCOPE GraphicalUserInterface

void test(){
  std::cout<<"Did something...\n";
}

SCOPE::GraphicalUserInterface(uint32_t borderSymmetrical, uint32_t height, uint32_t width)
  :borderSymmetrical_(borderSymmetrical)
  ,width_(width)
  ,height_(height)
{

  //GUI window
  cv::namedWindow("DVS-Monochromatic GUI", cv::WINDOW_AUTOSIZE);

  //Draw canvas
  canvas_ = cv::Mat(height_+ 2*borderSymmetrical,width_+2*borderSymmetrical,CV_32FC3);

  color_ = cv::Point3f(145.0/255,176.0/255,195.0/255);
  canvas_ = cv::Scalar(color_.x, color_.y, color_.z);


  // Initialize mouse callback
  cv::setMouseCallback("DVS-Monochromatic GUI", onMouseEvent, this);


}


SCOPE::~GraphicalUserInterface(){
  if(guiThread_.joinable())
    guiThread_.join();
}

void SCOPE::render(){

  for(uint8_t i = 0; i < image_views_.size();++i){
    // copy Image to canvas if there is any
    if(!(*(image_views_[i]->imagePtr_)).empty())
    (*(image_views_[i]->imagePtr_)).copyTo(canvas_(image_views_[i]->getRoi()));

    cv::Size textsize = getTextSize(image_views_[i]->getText(), cv::FONT_HERSHEY_DUPLEX, 1,1,0);

     cv::putText(canvas_, image_views_[i]->getText(), image_views_[i]->getTopLeft()+cv::Point(3,3+textsize.height),cv::FONT_HERSHEY_DUPLEX, 1,cv::Scalar(1.0,1.0,1.0));
  }

  for(uint8_t i = 0; i<text_streams_.size();++i){
    if(text_streams_[i]->changed())
    {

      if(!(text_streams_[i]->image_).empty())
        (text_streams_[i]->image_).copyTo(canvas_(text_streams_[i]->getRoi()));


     text_streams_[i]->setUnchanged();
    }
  }

  cv::imshow("DVS-Monochromatic GUI", canvas_);
  cv::waitKey(16);
}


void SCOPE::onMouseEvent(int event, int x, int y, int flags, void* userdata)
{

   SCOPE* eventdataPtr = reinterpret_cast<SCOPE*>(userdata);

     if  ( event == cv::EVENT_MOUSEMOVE )
     {
          // Buttons
          for(uint8_t i; i<eventdataPtr->buttons_.size();++i){
            if(eventdataPtr->buttons_[i]->isInside(x,y)){
              if(eventdataPtr->buttons_[i]->state_ == eventdataPtr->buttons_[i]->OFF){
                (eventdataPtr->buttons_[i]->buttonHover_).copyTo(eventdataPtr->canvas_(eventdataPtr->buttons_[i]->getRoi()));
              }
            }
            else
            {
              if(eventdataPtr->buttons_[i]->state_ == eventdataPtr->buttons_[i]->ON){
                //leave as is
              }

              else{
                 (eventdataPtr->buttons_[i]->buttonOff_).copyTo(eventdataPtr->canvas_(eventdataPtr->buttons_[i]->getRoi()));
              }
            }
          }
     }
     if(event == cv::EVENT_LBUTTONDOWN){

       // Buttons
       for(uint8_t i; i<eventdataPtr->buttons_.size();++i){
         if(eventdataPtr->buttons_[i]->isInside(x,y)){
           if(eventdataPtr->buttons_[i]->state_ == eventdataPtr->buttons_[i]->OFF){
              //toggle button
              eventdataPtr->buttons_[i]->state_ = eventdataPtr->buttons_[i]->ON;
              (eventdataPtr->buttons_[i]->buttonOn_).copyTo(eventdataPtr->canvas_(eventdataPtr->buttons_[i]->getRoi()));

              eventdataPtr->buttons_[i]->activateEffect();
           }
           else{
             eventdataPtr->buttons_[i]->state_ = eventdataPtr->buttons_[i]->OFF;
             (eventdataPtr->buttons_[i]->buttonOff_).copyTo(eventdataPtr->canvas_(eventdataPtr->buttons_[i]->getRoi()));

             eventdataPtr->buttons_[i]->deactivateEffect();
           }
         }
       }

     }

}

void SCOPE::setButtonCallback(uint16_t button_id , std::function<void(void)> cb_func){
  buttons_[button_id]->setCallback(cb_func);
}

void SCOPE::addCanvasElement(ElementType type, cv::Point topLeft, uint32_t width, uint32_t height, std::string identifier , std::function<void(void)> cb_func , std::function<void(void)> cb_func2){

  if(type == BUTTON){

    // Create button
    Button *Bptr = new Button(identifier, topLeft + cv::Point(borderSymmetrical_,borderSymmetrical_), height,width);
    buttons_.push_back(Bptr);
    Bptr->setCallback(cb_func, cb_func2);

    Bptr->buttonOff_.copyTo(canvas_(Bptr->getRoi()));

  }
  else if(type == TEXT_STREAM){

    TextStream *TPtr = new TextStream(identifier, topLeft, color_);
    text_streams_.push_back(TPtr);

    TPtr->image_.copyTo(canvas_(TPtr->getRoi()));

  }
  else if(type == IMAGE_VIEW){

    // Create image viewer
    ImageView *Iptr = new ImageView(identifier, topLeft + cv::Point(borderSymmetrical_,borderSymmetrical_), height, width);
    image_views_.push_back(Iptr);
    Iptr->setCallback(cb_func);

  }

}

cv::Point3f SCOPE::getColor(){
  return color_;
}

#undef SCOPE

}
