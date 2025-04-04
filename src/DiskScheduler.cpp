#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

class DiskScheduler
{
private:
    const int CYLINDERS_NUMBER = 5000;
    const int REQUESTS_NUMBER = 1000;
    vector<int> requests;
    int initialHeadPosition;

public:
    DiskScheduler(int startPos) : initialHeadPosition(startPos)
    {
        generateRequests();
    }

    void generateRequests()
    {
        srand(time(0));
        requests.clear();
        for (int i = 0; i < REQUESTS_NUMBER; i++)
        {
            requests.push_back(rand() % CYLINDERS_NUMBER);
        }
    }
    
    int fcfs()
    {
        int currentPosition = initialHeadPosition, headMovement = 0;
        for (int i = 0; i < REQUESTS_NUMBER; i++)
        {
            headMovement += abs(requests[i] - currentPosition);
            currentPosition = requests[i];
        }
        return headMovement;
    }

    // int sstf();
    // int scan();
    // int cscan();
    // int look();
    // int clook();
};