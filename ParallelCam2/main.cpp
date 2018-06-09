#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

using namespace cv;

void F1() {
    cout << "This is F1" << endl;
}


void F2() {
    cout << "This is F2" << endl;
}


void (* FS [2])() = {F1, F2};

class X : public ParallelLoopBody
{
    int x;

public:
    X(int &y) : x(y)
    { }


    void operator()(const Range& range) const override
    {
        FS[x]();
//        cout << x << endl;
    }
};

int main()
{
    int x = 0;
    int y = 1;

    parallel_for_(Range{0, 1}, X{x});


    waitKey();
}
