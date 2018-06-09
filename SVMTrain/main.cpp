#include <svm.h>
#include <iostream>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <dirent.h>
#include <getfiles.h>
#include <time.h>



using namespace std;

int train(){
    int m=0;
    int numfiles;
    cv::Mat img, img0;
    vector<string> files;
    vector<string> folders;
    string f = "/home/taquy/Projects/python/ctr-crop/TestSVM/data-new/";

    img0 = cv::imread("/home/taquy/Projects/python/ctr-crop/TestSVM/data-new/1/81.jpg", 1);

    if(img0.empty()){
        cout << "Failed open image 0" << endl;
        return -1;
    }

    cv::Mat re;

    cv::resize(img0, re, cv::Size(64,48));

    vector<float> size_;

    cv::HOGDescriptor hog( cv::Size(64,48), cv::Size(8,8), cv::Size(4,4), cv::Size(4,4), 9);


    hog.compute(re, size_);
    list_folders(f, folders);
    for(string s: folders){
        cout << s << endl;
    }
    int num_imgs = 200;
    numfiles= num_imgs  * folders.size();
    cv::Mat labels(numfiles, 1, CV_32S);
    cv::Mat trainMat(numfiles, size_.size(), CV_32FC1);

    for(unsigned int x= 0; x < folders.size(); x++ ){
        list_file(folders[x], files);
        cout << folders[x] << endl;
        for(unsigned int y = 0; y< num_imgs; y++){
            cout << files[y] << endl;
            img = cv::imread(files[y], 0);
            cv::resize(img, img, cv::Size(64,48));
            vector<float> des;
            hog.compute(img,des);
            for (unsigned int i = 0; i < size_.size(); i++)
                trainMat.at<float>(m,i)= des[i];
                labels.at<int>(m, 0) = x;
                m++;
            }
      }
    cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
    svm->setType(cv::ml::SVM::C_SVC);
    svm->setKernel(cv::ml::SVM::LINEAR);
    svm->setTermCriteria(cv::TermCriteria(cv::TermCriteria::MAX_ITER, 10000, 1e-6));
    svm->train(trainMat, cv::ml::ROW_SAMPLE, labels);
    svm->save(f + "train.txt");
    cout << "FINISHED" << endl;

}



void testFileImage(cv::Mat &img, cv::Ptr<cv::ml::SVM> &svm){
    cv::Mat img2 ,mask , hsv_image, out;

    cv::cvtColor(img , img2, cv::COLOR_BGR2GRAY);

//    img = ~img;

    cv::cvtColor(img, hsv_image, cv::COLOR_BGR2HSV);

    findReadColor(hsv_image, mask);

    findTraffic(mask, out, img2);

    int st, end, frame = 0;

    if(!out.empty()){
        cv::imshow("origin", out);

        st = cv::getTickCount();

        cout << predict(out, svm) << endl;

        end = cv::getTickCount();

        cout <<"fps : " << 1/double(end - st) << endl;
    }
}

void testCam(){
    cv::VideoCapture video(0);

    cv::Mat frame, gray;

    cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
    svm = cv::ml::SVM::load("/home/taquy/Projects/python/ctr-crop/TestSVM/data-new/train.txt");

    while(true){
        video >> frame;

        if(frame.empty()){
            break;
        }

        testFileImage(frame, svm);
        imshow("frame", frame);

        int k = cv::waitKey(30) & 0xff;

        if(k == 27){
            break;
        }
        if(k == 32){
            cv::waitKey();
        }
    }
}

int main(){
//   train();
    testCam();
}
