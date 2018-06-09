//#include <iostream>

//#include <opencv2/highgui.hpp>
//#include <pthread.h>
//#include <X11/Xlib.h>

//using namespace std;
//using namespace cv;

//Mat frame;
//Mat frames[2];
//VideoWriter wt[2];
//bool stop;



//void *f(void *id)
//{
//    int x = (long) id;
//    string title = std::to_string(x);

//    while (!stop) {
//        if (!frames[x].empty()) {
//            wt[x].write(frames[x]);
//        }
//    }

//    wt[x].release();

//    pthread_exit(NULL);
//}


//int main ()
//{

//    wt[0].open("/home/taquy/Desktop/c/x1.avi", CV_FOURCC('D','I','V', 'X'), 15, Size(640,480), true);
//    wt[1].open("/home/taquy/Desktop/c/x2.avi", CV_FOURCC('D','I','V', 'X'), 25, Size(640,480), true);


//    stop = false;

//    pthread_t threads[2];
//    int rc;
//    for(int i=0; i < 2; i++ ){
//         rc = pthread_create(&threads[i], NULL, f, (void *) i);
//    }


//    VideoCapture cap(0);
//    while (!stop) {
//        cap >> frame;
//        frames[0] = frame.clone();
//        frames[1] = frame.clone();

//        imshow("x", frame);

//        int k = waitKey(1);
//        if (k == '8') stop = true;

//    }

//    cap.release();

////    pthread_exit(NULL);


//}


#include <thread>
#include <iostream>

void func1() {
    while (1) std::cout << "1" << std::endl;
}

void func2() {
    while (1) std::cout << "2" << std::endl;
}

int main() {
    std::thread td1(func1);
    std::thread td2(func2);
//    td1.join();
//    td2.join();
    std::cout << "Threads finished." << std::endl;
    return 0;
}


