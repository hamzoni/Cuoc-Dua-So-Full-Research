#include "stdafx.h"
#include "RGBProcess.h"


RGBProcess::RGBProcess()
{
}


RGBProcess::~RGBProcess()
{
}

void RGBProcess::debug(cv::Mat image, cv::Scalar min, cv::Scalar max)
{
    getmask(image, min, max);
    std::vector<std::vector<cv::Point> > hull = findhull();
    cv::Rect bigest = findBigestRect();
    cv::Mat rgb = image.clone();
    cv::cvtColor(image, rgb, cv::COLOR_GRAY2RGB);
    for (int i = 0; i < contours.size(); i++)
    {
	   //	   drawContours(rgb, hull, i, color, 2, 8, hierarchy, 0, cv::Point());
    }
    ScreenObj screen_obj = ScreenObj(bigest, image);
    //    cv::Point center = cv::Point(int(depth.size().width / 2), int(depth.size().height / 2));
    cv::Point center = cv::Point();
    cv::circle(rgb, center, 50, cv::Scalar(255, 255, 120), 2, 8);
    std::string text = "d : ";
    long gray_value = screen_obj.getdistance();
    text.append(std::string(" cm"));
    cv::putText(rgb, text, cv::Point2f(cv::Point(center.x - 30, center.y)), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 0, 0), 2);
    rectangle(rgb, bigest.tl(), bigest.br(), cv::Scalar(255, 255, 120), 2);
    cv::imshow("debug", rgb);
}

