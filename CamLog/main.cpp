#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <fstream>
#include <thread>
#include <unistd.h>

using namespace std;
using namespace cv;

int j = 0;
string dir = "/home/taquy/Projects/cpp/CamLog/";
double st = 0, et = 0, fps = 0;
double freq = getTickFrequency();
bool isAlive;

void func1() {
    ofstream fp;
    fp.open(dir + "log.txt");

    int c = 0;
    while (isAlive) {
        c++;
        fp << c << "-" << j << "\n";
        sleep(1 / 5);
    }

    fp.close();
}

int main() {

    isAlive = true;

    thread td2(func1);


    VideoCapture cap(0);
    Mat frame;

    int c = 0;
    while (isAlive) {

        st = getTickCount();

        cap >> frame;

        imshow("x", frame);

        int k = waitKey(1);

        if (k == 27) {
            isAlive = false;
            break;
        }

        et = getTickCount();
        fps = 1.0 / ((et-st) / freq);

        c++;

        if (c % 10 == 0) {
            j++;
            cout << "update k: " << j << endl;
        }

//        cout << "FPS: "<< fps << '\n';
    }

    td2.join();

    cap.release();

    return -1;
}
