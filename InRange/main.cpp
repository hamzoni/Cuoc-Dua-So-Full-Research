#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

int main()
{

    Mat frame;
    VideoCapture cap(0);

    while (1) {
        cap >> frame;
        frame = imread("/home/taquy/Downloads/capture_1.jpg");

        Mat hsv, mask;
        cvtColor(frame, frame, cv::COLOR_RGB2BGR);
        cvtColor(frame, hsv, COLOR_BGR2HSV);
        inRange(hsv, Scalar(10, 86, 183), Scalar(16, 223, 252), mask);

        imshow("mask", mask);
        imshow("frame", frame);

        waitKey(1);
    }
    return -1;
}
