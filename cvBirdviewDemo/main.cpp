#include <iostream>

// OpenCV imports
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

// C++ imports
#include <iostream>

using namespace std;
using namespace cv;
#define PI 3.1415926


int frameWidth = 640;
int frameHeight = 480;

int main(int argc, char const *argv[]) {


    // capture object
    String img = "/home/taquy/Desktop/street.jpg";
    string vid = "/home/taquy/Desktop/vid/10.avi";
    Mat image;
    image = imread(img, CV_LOAD_IMAGE_COLOR);


    VideoCapture capture(vid);

    // mat container to receive images
    Mat source, destination;

    // check if capture was successful
    if( !capture.isOpened()) throw "Error reading video";


    int alpha_ = 90, beta_ = 90, gamma_ = 90;
    int f_ = 500, dist_ = 500;

    namedWindow("Result", 1);

    createTrackbar("Alpha", "Result", &alpha_, 180);
    createTrackbar("Beta", "Result", &beta_, 180);
    createTrackbar("Gamma", "Result", &gamma_, 180);
    createTrackbar("f", "Result", &f_, 2000);
    createTrackbar("Distance", "Result", &dist_, 2000);
    int wv = 200;
    while( true ) {

        capture >> source;
//        source = image;

        resize(source, source,Size(frameWidth, frameHeight));

        double focalLength, dist, alpha, beta, gamma;

        alpha =((double)alpha_ -90) * PI/180;
        beta =((double)beta_ -90) * PI/180;
        gamma =((double)gamma_ -90) * PI/180;
        focalLength = (double)f_;
        dist = (double)dist_;

        Size image_size = source.size();
        double w = (double)image_size.width, h = (double)image_size.height;


        // Projecion matrix 2D -> 3D
        Mat A1 = (Mat_<float>(4, 3)<<
            1, 0, -w/2,
            0, 1, -h/2,
            0, 0, 0,
            0, 0, 1 );


        // Rotation matrices Rx, Ry, Rz

        Mat RX = (Mat_<float>(4, 4) <<
            1, 0, 0, 0,
            0, cos(alpha), -sin(alpha), 0,
            0, sin(alpha), cos(alpha), 0,
            0, 0, 0, 1 );

        Mat RY = (Mat_<float>(4, 4) <<
            cos(beta), 0, -sin(beta), 0,
            0, 1, 0, 0,
            sin(beta), 0, cos(beta), 0,
            0, 0, 0, 1	);

        Mat RZ = (Mat_<float>(4, 4) <<
            cos(gamma), -sin(gamma), 0, 0,
            sin(gamma), cos(gamma), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1	);


        // R - rotation matrix
        Mat R = RX * RY * RZ;

        // T - translation matrix
        Mat T = (Mat_<float>(4, 4) <<
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, dist,
            0, 0, 0, 1);

        // K - intrinsic matrix
        Mat K = (Mat_<float>(3, 4) <<
            focalLength, 0, w/2, 0,
            0, focalLength, h/2, 0,
            0, 0, 1, 0
            );


        Mat transformationMat = K * (T * (R * A1));

        warpPerspective(source, destination, transformationMat, image_size, INTER_CUBIC | WARP_INVERSE_MAP);

        imshow("Result", destination);
        int k = waitKey(wv) & 0xff;

        if(k == 27) break;
        if(k == 38) wv += 10;
        if(k == 40) wv -= 10;
        if(k == 32) waitKey();
    }


    return 0;
}
