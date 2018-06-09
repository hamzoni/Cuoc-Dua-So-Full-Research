#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define NUM_THREADS 5

void *PrintHello(void *threadid) {
   long tid;
   tid = (long)threadid;

   cout << "Hello World! Thread ID, " << tid << endl;

   while (true) {

   }

   pthread_exit(NULL);
}

int main () {
   pthread_t threads[NUM_THREADS];
   int rc;
   int i;

   VideoCapture cam(0);

   if(!cam.isOpened()){
       return -1;
   }

   for( i = 0; i < NUM_THREADS; i++ ) {
      cout << "main() : creating thread, " << i << endl;
      rc = pthread_create(&threads[i], NULL, PrintHello, (void *)i);

   }

   while(1){
       Mat frame;
       cam >> frame;



       if(frame.empty()){
           break;
       }

       imshow("asdf", frame);

       int k = waitKey(30) & 0xff;

       if(k == 32){
           break;
       }
   }



   pthread_exit(NULL);
}
