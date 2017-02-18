#pragma once
#include <functional>
#include <stdlib.h>
#include <thread>
#include "visualization/button.hpp"
#include "visualization/image_view.hpp"
#include "visualization/text_stream.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace visualization{

enum ElementType{BUTTON, IMAGE_VIEW, HEADER, TEXT_STREAM, EXCLUSIVE_BUTTON};

class GraphicalUserInterface{

public:

  GraphicalUserInterface(uint32_t borderSymmetrical = 0, uint32_t height = 1000, uint32_t width = 1000);

  ~GraphicalUserInterface();



  void setButtonCallback(uint16_t button_id,std::function<void(void)> cb_func);

  void addCanvasElement(ElementType type, cv::Point topLeft, uint32_t width = 0, uint32_t height = 0, std::string identifier = "", std::function<void(void)> cb_func = [](){}, std::function<void(void)> cb_func2 = [](){});

  void render();

  cv::Point3f getColor();

 static void onMouseEvent(int event, int x, int y, int flags, void* userdata);



  uint32_t width_;
  uint32_t height_;

  cv::Rect roi_;

  cv::Point3f color_;

  uint32_t borderSymmetrical_ = 0;

  std::thread guiThread_;

  cv::Mat canvas_;

  std::vector<ImageView*> image_views_;
  std::vector<Button*> buttons_;
  std::vector<TextStream*> text_streams_;

};


}
