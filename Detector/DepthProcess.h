#include "stdafx.h"
#include "ScreenObj.h"
#include "ImageProcess.h"
#pragma once
class DepthProcess : ImageProcess
{
public:
    DepthProcess();
    ~DepthProcess();
    
    void debug(cv::Mat depth, int min = 10, int max = 110);
private:
    
   
    
};

