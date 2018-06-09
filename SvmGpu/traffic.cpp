#include "traffic.h"

Traffic::Traffic()
{
    this->kernel = Size(64, 48);
    this->model = "/home/taquy/train.txt";
//    this->hog = cv::HOGDescriptor(this->kernel, Size(8,8), Size(4,4), Size(4,4), 9);

//    this->hog.load(this->model, "1");
//    this->hog.setSVMDetector(cv::HOGDescriptor.getDefaultPeopleDetector());

}


int Traffic::taquy(Mat &frame) {
    vector<Rect> rects = this->predict(frame);
    this->draw(frame, rects, "1");
}



vector<Rect> Traffic::predict(Mat &test) {


      vector<Rect> rects;
      this->hog.detectMultiScale(test, rects);

      return rects;
}



Mat Traffic::draw(Mat frame, vector<Rect> boxes, String label) {

    // draw rects
    for( size_t i = 0; i < boxes.size(); i++ )
    {
        int x = boxes[i].x;
        int y = boxes[i].y;
        Point a(x, y);
        Point b(x + boxes[i].width, y + boxes[i].height);

        rectangle(frame, a, b, Scalar(0, 255, 0), 3);

        putText(frame, label, a, FONT_HERSHEY_SIMPLEX, 1, (0, 125, 255), 3, 0, false);
    }
    return frame;
}
