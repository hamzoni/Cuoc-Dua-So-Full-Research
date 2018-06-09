#include <svmdetector.h>
#include <iostream>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <dirent.h>
#include <time.h>
using namespace std;

double st = 0, et = 0, fps = 0;
double freq = getTickFrequency();

void testTrain() {
    DetectorSVM *dsvm;
    dsvm = new DetectorSVM();
    dsvm->train();
}

void testCam(){
    string vid = "/home/taquy/Desktop/c/10.avi";
    string pic = "/home/taquy/Downloads/HSV_auto_range/x.png";

    cv::VideoCapture video(0);
    int frame_counter = 0;

    cv::Mat frame, gray;
    DetectorSVM *dsvm = new DetectorSVM();
//    int wv = 200;
    int wv = 1;
    while(true){

//        if (frame_counter == video.get(CV_CAP_PROP_FRAME_COUNT)) {
//            frame_counter = 0 ;
//            video.set(CV_CAP_PROP_POS_FRAMES, 0);
//        }


        st = getTickCount();
        video >> frame;
//        frame = cv::imread(pic,1);

        if(frame.empty()) continue;

//        cv::resize(frame, frame, Size(frame.cols / 4, frame.rows / 4), 1, 1, cv::INTER_LANCZOS4);
//        dsvm->detectMult(frame);
        int id = dsvm->detect(frame);
//        cout << id << endl;
        imshow("frame", frame);

        int k = cv::waitKey(wv) & 0xff;

        et = getTickCount();
        fps = 1.0 / ((et-st) / freq);
        cout << "FPS: "<< fps<< '\n';

        if(k == 27) break;
        if(k == 38) wv += 10;
        if(k == 32) waitKey();
    }
}

int main(){
//    testTrain();
    testCam();
}
