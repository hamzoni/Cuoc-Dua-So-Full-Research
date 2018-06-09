#include <iostream>
#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int val;
const int maxv = 2000;

Mat frame;

void slider() {
    string wname = "test";

    namedWindow(wname, CV_WINDOW_AUTOSIZE);

    char name[50]; sprintf(name, "X %d", maxv);
    createTrackbar(name, wname, &val, maxv, NULL);
}

int main() {
    val = 1;

    VideoCapture cap(0);
    slider();

    while (1) {
        cap >> frame;
        if (val < 1) val = 1;
        cv::blur(frame, frame, Size(val, val));

        imshow("test", frame);
        if (waitKey(1) >= 0) break;
    }

    return 0;
}
