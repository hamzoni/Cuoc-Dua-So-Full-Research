#include <iostream>
#include <thread>

using namespace std;

float sprod(float * a, float *b, int start, int end, double *sum)
{
    float lsum = 0.0;
    for (int i = start; i < end; i++) {
        lsum += a[i] * b[i];
    }
    *sum = lsum;
}

float sprod(float *a, float *b, int size) {
    float sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}




int main() {

    int n = 4;
    float a[] = {1,2,3,4};
    float b[] = {1,2,3,4};

    int nthr = 2;
    int *sum_array = new int[nthr];

    thread *t_arr[nthr];
    for (int i = 0; i < nthr; i++) {
        int start = i * n / nthr;
        int end = (i + 1) * n / nthr;
        if (i == nthr - 1) end = n;
        sum_array[i] = 0.0;
        t_arr[i] = new thread(sprod, a, b, start, end, &sum_array[i]);
    }


    for (int i = 0; i < nthr; i++) {
        t_arr[i]->join();
        sum += sum_array[i];
    }


    return -1;
}
