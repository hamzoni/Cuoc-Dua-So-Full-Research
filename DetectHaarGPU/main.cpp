#include <iostream>

using namespace std;

#include "opencv2/core/core.hpp"

#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudaobjdetect.hpp>
#include <opencv2/cudaarithm.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <X11/Xlib.h>

#include <opencv2/gpu/gpu.hpp>

using namespace cv;


cv::String modeldir = "/home/taquy/Projects/cpp/GPUTrafficSignDetector/models/";

cv::String model = modeldir + "stop.xml";
double st = 0, et = 0, fps = 0;
double freq = getTickFrequency();

int main(int argc, char *argv[])
{


    VideoCapture cap(0);

    while (1) {

        st = getTickCount();
        Mat frame;
        cap >> frame;


        cv::cuda::GpuMat gpuMat, grayMat;
        cv::Mat area = frame.clone();
        gpuMat.upload(area);

        cv::cuda::cvtColor(gpuMat, grayMat, cv::COLOR_BGR2GRAY);

        grayMat = grayMat.clone();
        cv::Ptr<cv::cuda::CascadeClassifier> classifier = cv::cuda::CascadeClassifier::create(model);
        std::vector<cv::Rect> boxes;

        cv::cuda::GpuMat gpuFound;

        classifier->setMinNeighbors(15);
        classifier->detectMultiScale(grayMat, gpuFound);
        classifier->convert(gpuFound, boxes);

        et = getTickCount();
        fps = 1.0 / ((et-st) / freq);
        cerr << "FPS: "<< fps<< '\n';
        if (waitKey(1) >= 0) break;

        for( size_t i = 0; i < boxes.size(); i++ )
        {
            int x = boxes[i].x;
            int y = boxes[i].y;
            cv::Point a(x, y);
            cv::Point b(x + boxes[i].width, y + boxes[i].height);

            cv::rectangle(frame, a, b, cv::Scalar(0, 255, 0), 3);

            // cv::putText(frame, label, a, cv::FONT_HERSHEY_SIMPLEX, 1, (0, 125, 255), 3, 0, false);
        }


        cv::imshow("Frame", frame);

        if (waitKey(1) >= 0) break;

    }


}
