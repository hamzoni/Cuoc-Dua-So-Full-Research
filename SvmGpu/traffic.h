#ifndef SVMDETECTOR_H
#define SVMDETECTOR_H

#endif // SVMDETECTOR_H
#ifndef Traffic_H
#define Traffic_H

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect.hpp>
#include <dirent.h>
#include <string>

using namespace cv;
using namespace ml;
using namespace std;

#include <opencv2/cudaobjdetect.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/gpu/gpu.hpp>


class Traffic
{
private:

    string model;  // model file


public:

    Traffic();

    HOGDescriptor hog;

    Size kernel;

    int taquy(Mat &frame);

    vector<Rect> predict(Mat &test);


    Mat draw(Mat frame, vector<Rect> boxes, String label);

};


#endif // Traffic_H
