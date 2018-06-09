#include <iostream>
#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int valblur = 1;
int valthresh = 125;
int valopening = 15;
int valclosing = 15;


string wname = "test";

Mat frame;

void sliderBlur(int maxv) {
    char name[50]; sprintf(name, "blur %d", maxv);
    createTrackbar(name, wname, &valblur, maxv, NULL);
}

void sliderThresh(int maxv) {
    char name[50]; sprintf(name, "thresh %d", maxv);
    createTrackbar(name, wname, &valthresh, maxv, NULL);
}

void sliderOpening(int maxv) {
    char name[50]; sprintf(name, "opening %d", maxv);
    createTrackbar(name, wname, &valopening, maxv, NULL);
}

void sliderClosing(int maxv) {
    char name[50]; sprintf(name, "closing %d", maxv);
    createTrackbar(name, wname, &valclosing, maxv, NULL);
}

int main() {
    string vid = "/home/taquy/Desktop/c/6.avi";
    VideoCapture cap(vid);

    namedWindow(wname, CV_WINDOW_AUTOSIZE);

    sliderBlur(100);
    sliderThresh(255);
    sliderOpening(100);
    sliderClosing(100);
    int wv = 200;
    while (1) {
        cap >> frame;
        if (valblur < 1) valblur = 1;
        cv::cvtColor(frame, frame, cv::COLOR_RGB2BGR);
        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
        cv::blur(frame, frame, Size(valblur, valblur));
        cv::threshold(frame, frame, valthresh, 255, cv::THRESH_BINARY);
        cv::morphologyEx(frame, frame, cv::MORPH_CLOSE, Mat(valclosing,valclosing, CV_8U, Scalar(1)));
        cv::morphologyEx(frame, frame, cv::MORPH_OPEN, Mat(valopening,valopening, CV_8U, Scalar(1)));

        imshow("test", frame);

        int k = waitKey(wv) & 0xff;

        if(k == 27) break;
        if(k == 38) wv += 10;
        if(k == 40) wv -= 10;
        if(k == 32) waitKey();
    }

    return 0;
}
