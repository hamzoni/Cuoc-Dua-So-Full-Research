
#include "ScreenObj.h"

ScreenObj::ScreenObj(cv::Rect location, cv::Mat image)
{
    this->location = location;
    this->image = image;
}

long ScreenObj::getdistance()
{
    long balance = balance_pixel();

    return gray_to_distance(balance);
}
long ScreenObj::gray_to_distance(int value)
{
    long distance = 0;
    long flag; //moc khoang cach thuc
    double pi;
    long pos;
    if (value < 65.5)
    {
	   flag = 80;
	   pi = 1.23076923;
	   pos = 65.5;
    }
    else if (value >= 65.5 && value < 98)
    {
	   flag = 80;
	   pi = 1.23076923;
	   pos = 65.5;
    }
    else if (value>=98 && value <= 135.5)
    {
	   flag = 120;
	   pi = 1.06666667;
	   pos = 98;
    }
    else if (value>135.5)
    {
	   flag = 160;
	   pi = 0.924444451;
	   pos = 135.5;
    }
    
    distance = flag + pi * (value - pos);
    return distance;
}
long ScreenObj::balance_pixel(int number_pixels)
{
    int x = int(location.x + location.width * 0.3);
    int y = int(location.y + location.height * 0.3);
    int width = int(location.width * 0.3);
    int height = int(location.height * 0.3);
    cv::Rect inside = cv::Rect(x, y, width, height);
    cv::Mat crop = image(inside);
    int sumvalue = 0;
    if (crop.size[0] == 0 || crop.size[1] == 0)
	   return 0;
    for (int i = 0; i < number_pixels; ++i)
    {
	   int rand_x = std::rand() % (crop.size[0]);
	   int rand_y = std::rand() % (crop.size[1]);
	   sumvalue += crop.at<uchar>(rand_x, rand_y);
    }

//    cv::rectangle(image, inside, cv::Scalar(0, 0, 255), 2);

    return sumvalue / number_pixels;
}

