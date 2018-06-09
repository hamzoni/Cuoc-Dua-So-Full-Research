#ifndef SVMDETECTOR_H
#define SVMDETECTOR_H

#endif // SVMDETECTOR_H
#ifndef DETECTORSVM_H
#define DETECTORSVM_H

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect.hpp>
#include <dirent.h>
#include <string>

using namespace cv;
using namespace ml;
using namespace std;

namespace SVMConfig {
    extern int isTrain;
    extern Mat trackImg;
    extern Scalar lower;
    extern Scalar upper;
    extern Mat closing;
    extern Mat opening;
    extern vector<int> vals;
}

class DetectorSVM
{
private:

    Ptr<SVM> svm;
    string model;  // model file
    string data;  // data train folder
    string sample; // seeding file

    vector<string> labels; // labels

    void load();

public:

    DetectorSVM();

    void preprocess(Mat &img, Mat &img2, Mat &hsv, Mat &gray);

    Rect pooling(Mat &mask, Mat &out, Mat &gray);

    vector<Rect> poolingMult(Mat &mask, Mat &gray, vector<Mat> &outs);

    int predict(Mat &test);

    string label(int &id);

    int train();

    int detect(Mat &img);

    vector<int> detectMult(Mat &img);

    Mat draw(Mat frame, vector<Rect> boxes, String label);

    void lsdirs(string path, vector<string> &folders);

    void lsfiles(string path, vector<string> &files);

    void setLabels(string labels[]);

    void slider(int &val, int max, string title, string wname);
};


#endif // DETECTORSVM_H
