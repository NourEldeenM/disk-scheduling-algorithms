#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <unordered_set>

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

    // time complexity: O(REQUESTS_NUMBER)
    // space complexity: O(1)

    /// @brief First-Come-First-Serve disk scheduling algorithm
    /// @return total amount of head movement from start position
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

    /// @brief Shortest-Seek-Time-First disk scheduling algorithm
    /// @return total amount of head movement from start position
    int sstf() {
        int currentPosition = initialHeadPosition;
        int headMovement = 0;
        
        unordered_set<int> servedRequests;
        while (servedRequests.size() < REQUESTS_NUMBER) {
            int minDistance = INT_MAX;
            int servedRequestIndex;
            for (int i = 0; i < REQUESTS_NUMBER; i++) {
                if (servedRequests.find(i) == servedRequests.end()) { // if this request not served
                    if (abs(requests[i] - currentPosition) < minDistance) { // check if its seek time is the least or not
                        minDistance = abs(requests[i] - currentPosition);
                        servedRequestIndex = i;
                    }
                }
            }
            headMovement += minDistance;
            servedRequests.insert(servedRequestIndex);
        }
        return headMovement;
    }

    int scan() {
        int currentPosition = initialHeadPosition;
        int headMovement = 0;

        vector<int> tempRequests = requests;
        sort(tempRequests.begin(), tempRequests.end());

        int startIdx = 0;
        for (int i = 0; i < REQUESTS_NUMBER; i++)
        {
            if (tempRequests[i] >= currentPosition)
            {
                startIdx = i;
                break;
            }
        }

        // move to highest request
        for (int i = startIdx; i < REQUESTS_NUMBER; i++) {
            headMovement += abs(currentPosition - tempRequests[i]);
            currentPosition = tempRequests[i];
        }

        headMovement += abs(currentPosition - (CYLINDERS_NUMBER - 1)); // simulate it reached the end
        currentPosition = CYLINDERS_NUMBER - 1;

        if (startIdx > 0) {
            for (int i = startIdx - 1; i >= 0; i--) {
                headMovement += abs(currentPosition - tempRequests[i]);
                currentPosition = tempRequests[i];
            }
        }
        return headMovement;
    }
    // int cscan();
    // int look();
    // int clook();
};