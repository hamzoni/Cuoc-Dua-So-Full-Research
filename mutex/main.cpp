
#include <opencv2/opencv.hpp>

using namespace cv;

class RandomFillBody : public ParallelLoopBody
{
    Mat3b img;

public:
    RandomFillBody(Mat3b& img) : img(img)
    { }

    void operator()(const Range& range) const override
    {
        theRNG().state = getTickCount();
        Vec3b color{ theRNG(), theRNG(), theRNG() };

        for (int i = range.start; i < range.end; ++i)
        {
            int x = i % 8, y = i / 8;
            img(Range{ y * 10, (y + 1) * 10 }, Range{ x * 10, (x + 1) * 10 }) = color;
        }
    }
};

int main()
{
    Mat3b img = Mat3b::zeros(80,80);

    parallel_for_(Range{ 0, 64 }, RandomFillBody{ img });

    imshow("img", img);
    waitKey();
}
