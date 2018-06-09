#include "stdafx.h"
#include "ImageProcess.h"


ImageProcess::ImageProcess()
{
}


ImageProcess::~ImageProcess()
{
}

ScreenObj ImageProcess::getObject(cv::Mat image, cv::Scalar min, cv::Scalar max)
{
    getmask(image, min, max);
   
    cv::imshow("as", mask);
    return ScreenObj(findBigestRect(), image);
}

std::vector<std::vector<cv::Point>> ImageProcess::findhull()
{
    findContours(mask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
   
	std::vector<std::vector<cv::Point>> hull(contours.size());
    
    for (int i = 0; i < contours.size(); i++)
    {
	   convexHull(cv::Mat(contours[i]), hull[i], false);
	   
    }
    return hull;
  //Test
}

cv::Rect ImageProcess::findBigestRect()
{
    double maxsize = 0;
    cv::Rect bigest;
    std::vector<std::vector<cv::Point> > hull = findhull();
    for (int i = 0; i < hull.size(); ++i)
    {
	   cv::Rect current_rect = cv::boundingRect(hull[i]);
	   long ratio = current_rect.size().width / current_rect.size().height;
	   if (current_rect.area() > maxsize && ratio < 3)
	   {
		  bigest = current_rect;
		  maxsize = current_rect.area();
	   }
    }
    return bigest;
}

void ImageProcess::getmask(cv::Mat image, cv::Scalar min, cv::Scalar max)
{
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_RGB2HSV);
    inRange(hsv, min, max, mask);
    cv::blur(mask, mask, cv::Size(5, 5));
}
