#include <iostream>
#include "DiskScheduler.cpp"

using namespace std;

int main(int argc, char *argv[]) {

    int initialPosition;
    cout << "Enter start position: ";
    cin >> initialPosition;
    if (initialPosition < 0 || initialPosition > 4999) {
        cout << "Invalid initial position, must be between 0 & 4999\n";
        return 1;
    }

    DiskScheduler scheduler(initialPosition);

    cout << "Total head movement for each algorithm:" << endl;
    cout << "FCFS:\t" << scheduler.fcfs() << endl;
    cout << "SSTF:\t" << scheduler.sstf() << endl;
    cout << "SCAN:\t" << scheduler.scan() << endl;
    cout << "C-SCAN:\t" << scheduler.cscan() << endl;
    cout << "LOOK:\t" << scheduler.look() << endl;
    cout << "C-LOOK:\t" << scheduler.clook() << endl;

    return 0;
}