#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

using namespace cv;

void F1() {
    cout << "This is F1" << endl;
}

void test(void (*f)()) {
  f();
}

void F2() {
    cout << "ok" << endl;
}

class X : public ParallelLoopBody
{
    int x;
    void (*f)();

public:
    X(int &y, void (*fx)()) : x(y), f(fx)
    { }


    void operator()(const Range& range) const override
    {
        while (1) {
            f();
        }
    }
};

int main()
{
    int x = 0;
    int y = 1;

    parallel_for_(Range{0, 1}, X{x, F1});


    waitKey();
}
