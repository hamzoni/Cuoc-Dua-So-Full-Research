#pragma once
class RGBProcess : ImageProcess
{
public:
    RGBProcess();
    ~RGBProcess();
 
    void debug(cv::Mat image, cv::Scalar min, cv::Scalar max);

};

