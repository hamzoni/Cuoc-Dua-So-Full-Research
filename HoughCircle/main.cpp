#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;


#include <iostream>
#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

string wname = "test";

void createSlider(int &val, int max, string title, string wname) {
    title = title + " " + std::to_string(max);
    createTrackbar(title, wname, &val, max, NULL);
}

int main()
{
    int n = 6;
    int val[n];
    std::fill(val, val + n, 0);

    VideoCapture cap(0);

    namedWindow(wname, CV_WINDOW_AUTOSIZE);

    createSlider(val[0], 100, "A");
    createSlider(val[1], 100, "B");
    createSlider(val[2], 100, "C");
    createSlider(val[3], 100, "D");


    Mat frame;
    while (1) {
        cap >> frame;

        Mat gray;
        medianBlur(frame, frame, 5);
        if (!frame.empty()) cv::cvtColor(frame, gray, CV_BGR2GRAY);

        vector<Vec3f> circles;
        HoughCircles(gray, circles, HOUGH_GRADIENT, 1, 10, 100, 30, 1, 30);
        for( size_t i = 0; i < circles.size(); i++ )
        {
            Vec3i c = circles[i];
            circle( frame, Point(c[0], c[1]), c[2], Scalar(0,0,255), 2, LINE_AA);
            circle( gray, Point(c[0], c[1]), c[2], Scalar(0,0,255), 2, LINE_AA);
        }
        imshow("gray", gray);
        imshow("test", frame);
        waitKey(10);

    }
    return 0;
}
