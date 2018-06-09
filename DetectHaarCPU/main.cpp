
#include <iostream>
#include <chrono>


using namespace std;


#include <opencv2/highgui.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


#include <time.h>


using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */
String face_cascade_name = "/home/taquy/Projects/cpp/GPUTrafficSignDetector/models/stop.xml";
CascadeClassifier face_cascade;
string window_name = "Capture - Face detection";
RNG rng(12345);


double st = 0, et = 0, fps = 0;
double freq = getTickFrequency();

int main (int argc, char* argv[])
{
    VideoCapture cap(0);
    face_cascade.load( face_cascade_name );

    while (1) {
        st = getTickCount();


        Mat frame;
        cap >> frame;

        detectAndDisplay(frame);


        et = getTickCount();
        fps = 1.0 / ((et-st) / freq);
        cerr << "FPS: "<< fps<< '\n';
        if (waitKey(1) >= 0) break;

    }
    return 0;
}


void detectAndDisplay(Mat frame)
{
  std::vector<Rect> boxes;
  Mat frame_gray;

  cvtColor(frame, frame_gray, CV_BGR2GRAY );
  equalizeHist(frame_gray, frame_gray);

  face_cascade.detectMultiScale( frame_gray, boxes, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
  for( size_t i = 0; i < boxes.size(); i++ )
  {
      int x = boxes[i].x;
      int y = boxes[i].y;
      cv::Point a(x, y);
      cv::Point b(x + boxes[i].width, y + boxes[i].height);

      cv::rectangle(frame, a, b, cv::Scalar(0, 255, 0), 3);
  }
  imshow( window_name, frame );
 }
