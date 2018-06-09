
#include "ScreenObj.h"
#include "ImageProcess.h"
#include "opencv2/core.hpp"

class DepthProcess : ImageProcess
{
    public:
        DepthProcess();
        ~DepthProcess();

        void debug(cv::Mat depth, int min = 10, int max = 110);

};

