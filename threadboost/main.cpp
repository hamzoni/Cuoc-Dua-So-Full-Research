#include <thread>
#include <iostream>
using namespace std;

CRITICAL_SECTION critSection;

void task1() {
    // do something
    while (1) {
        cout << "task 1" << endl;
    }
}

void task2() {
    // do something
    while (1) {
        cout << "task 2" << endl;
    }
}

int main () {
    thread thread1 = thread(task1);
    thread thread2 = thread(task2);
    thread2.join();
    thread1.join();

    return -1;
}
