
#ifndef ScreenObj
#define ScreenObj

#include "opencv2/core.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class ScreenObj
{
    public:

        ScreenObj(cv::Rect location, cv::Mat image);//mat image la con tro


        /**
        * \tim khoang cach tu xe den object,
        * 1. cat object in side box ( 40% ben trong)
        * 2. get distance via depth image
        *
        */
        long getdistance();

        cv::Rect location;

    private:

        long gray_to_distance(int value);
        cv::Mat image;
        long balance_pixel(int number_pixels = 10);

};

#endif
