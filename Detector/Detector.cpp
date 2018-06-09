#include "stdafx.h"
#include "Detector.h"


Detector::Detector()
{
}


Detector::~Detector()
{
}

void Detector::debug(cv::Mat color,cv::Mat depth)
{
    cv::Mat mask = findmask(color, min, max);
   
    ImageProcess image_process = ImageProcess();
    std::vector<std::vector<cv::Point>> hull = findcontour(mask);

    ScreenObj screen_obj = image_process.getObject(color, cv::Scalar(0, 93, 148), cv::Scalar(42, 255, 255));
    long distance = screen_obj.getdistance();
    for (int i = 0; i < hull.size(); ++i)
    {
	   cv::Rect current_rect = cv::boundingRect(hull[i]);
	   long ratio = current_rect.size().width / current_rect.size().height;
	   if (current_rect.area() > 1000)
	   {
		  drawContours(color, hull, i, cv::Scalar(255, 255, 120), 2, 8, hierarchy, 0, cv::Point());
		 
		
	   }
    }
    
    cv::rectangle(color, screen_obj.location, cv::Scalar(0, 255, 0),2);
    cv::Point center = cv::Point(screen_obj.location.x, screen_obj.location.y);
    cv::putText(color, "Distance : " + std::to_string(distance)+" cm", center, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 0, 0), 2);


    cv::imshow("mask", color);
    cv::imshow("frame", depth);
}

std::vector<cv::Rect> Detector::detect(cv::Mat image)
{
    cv::Mat mask = findmask(image, cv::Scalar(70, 75, 96), cv::Scalar(101, 255, 255));
    cv::blur(mask, mask, cv::Size(5, 5));
    std::vector<cv::Rect> rectangles;
    std::vector<std::vector<cv::Point>> hull = findcontour(mask);
    for (int i = 0; i < hull.size(); ++i)
    {
	   cv::Rect current_rect = cv::boundingRect(hull[i]);
	   long ratio = current_rect.size().width / current_rect.size().height;
	   if (current_rect.area() > 150)
	   {
		  rectangles.push_back(cv::boundingRect(hull[i]));
	   }
    }
    return rectangles;
}

std::vector<std::vector<cv::Point>> Detector::findcontour(cv::Mat mask)
{
    
    findContours(mask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
    std::vector<std::vector<cv::Point>> hull(contours.size());


    for (int i = 0; i < contours.size(); i++)
    {
	   convexHull(cv::Mat(contours[i]), hull[i], false);
    }
    return hull;
}


cv::Mat Detector::findmask(cv::Mat image, cv::Scalar min, cv::Scalar max)
{
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_RGB2HSV);
    cv::Mat mask;
    cv::inRange(hsv, min, max, mask);
    return mask;
}
