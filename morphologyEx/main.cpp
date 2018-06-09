#include <iostream>
#include <chrono>


using namespace std;

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;

RNG rng(12345);
double st = 0, et = 0, fps = 0;
double freq = getTickFrequency();

Mat convert(Mat frame) {
    cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);

    blur(frame, frame, Size(5,5));

    cv::threshold(frame, frame, 125, 255, cv::THRESH_BINARY);


    Mat k(5,5, CV_8U, Scalar(1));
    cv::morphologyEx(frame, frame, cv::MORPH_OPEN, k);
    cv::morphologyEx(frame, frame, cv::MORPH_CLOSE, k);
    cv::morphologyEx(frame, frame, cv::MORPH_OPEN, k);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;


    /// Find contours
    findContours( frame, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

    vector<vector<Point> >hull( contours.size() );
    for( int i = 0; i < contours.size(); i++ )
    {
        convexHull( Mat(contours[i]), hull[i], false );
    }

    Mat drawing = Mat::zeros( frame.size(), CV_8UC3);

    for( int i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
        drawContours( drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
        drawContours( drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
    }

    return drawing;
}

int main() {
    VideoCapture cap(0);
    Mat frame;
    while (1) {
        cap >> frame;
        cv::flip(frame, frame, 1);

        st = getTickCount();


        Mat drawing = frame.clone();

        drawing = convert(frame);

        et = getTickCount();
        fps = 1.0 / ((et-st) / freq);
        cerr << "FPS: "<< fps<< '\n';

        imshow("y", drawing);
        imshow("x", frame);

        if (waitKey(1) > 30) break;
    }
    return -1;
}
