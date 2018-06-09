#include <iostream>

using namespace std;
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/cudaimgproc.hpp"

using namespace cv;

int main (int argc, char* argv[])
{



    VideoCapture cap(0);
    if(!cap.isOpened()) return -1;

    while (1) {
        Mat frame;
        cap >> frame;

        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);

        cv::cuda::GpuMat dst, src;
        src.upload(frame);


        cv::cuda::threshold(src, dst, 128.0, 255.0, CV_THRESH_BINARY);

        cv::Mat result_host;
        dst.download(result_host);

        cv::imshow("Result", result_host);

        if(waitKey(30) >= 0) break;
    }

    return 0;
}
