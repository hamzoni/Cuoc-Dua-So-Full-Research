
#include "Detector.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

DepthProcess check_object = DepthProcess();

int main()
{
    std::string folder = "C:/Users/Binh Bum/Desktop/depth/";
    std::string rgb_file = folder + "color.avi";
    std::string depth_file = folder + "depth.avi";
    cv::Mat color_frame, depth_frame;
//    cv::VideoCapture cap_color(rgb_file), cap_depth(depth_file);
    cv::VideoCapture cap_color(0), cap_depth(0);

    if (!cap_color.isOpened() || !cap_depth.isOpened())
       throw "Error when reading steam_avi";

    Detector detector = Detector();

    for (; ; )
    {
       cap_color >> color_frame;
       cap_depth >> depth_frame;

       if (depth_frame.empty() || color_frame.empty())
          break;
       cv::flip(color_frame, color_frame, 1);
       cv::cvtColor(depth_frame, depth_frame, cv::COLOR_RGB2GRAY);
       detector.debug(color_frame,depth_frame); // hien cua so opencv
//
//	   std::vector<cv::Rect> reactangles = detector.detect(frame); // box tra ve
//	   for (auto reactangle : reactangles)
//	   {
//		  std::cout << "Rect : " << reactangle << " \n";
//	   }
       cv::waitKey(20);
    }
    cv::waitKey(0);

}
