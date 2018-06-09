#include <iostream>
#include <traffic.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main()
{
    string vid = "/home/taquy/Desktop/c/14.avi";
    Traffic *d = new Traffic();

    cv::HOGDescriptor hog;
    hog.load("/home/taquy/train.txt");

//    vector<float> vts = hog.getDefaultPeopleDetector();
//    hog.setSVMDetector(vts);

    VideoCapture cap(vid);
    Mat frame;
    while(1) {

        cap >> frame;
        vector<Rect> rects;
        hog.detectMultiScale(frame, rects);
        d->draw(frame, rects, "1");

        imshow("frame", frame);

        int k = cv::waitKey(1) & 0xff;
        waitKey(30);
        if(k == 32) waitKey();
    }

    return -1;
}
