#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <ScreenObj.h>


class ImageProcess
{
    public:
        ImageProcess();
        ~ImageProcess();
        ScreenObj getObject(cv::Mat image, cv::Scalar min, cv::Scalar max);
    protected:
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::Mat mask;
        cv::Scalar color = cv::Scalar(0, 125, 0);
        std::vector<std::vector<cv::Point> > findhull();
        cv::Rect findBigestRect();
        void getmask(cv::Mat image, cv::Scalar min, cv::Scalar max);
};

