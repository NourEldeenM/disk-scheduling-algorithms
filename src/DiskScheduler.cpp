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

    /// @brief Gets the starting index in a sequence of requests based on initial head position
    /// @param sortedRequests requests sorted ascending
    /// @return starting index in the sorted requests array
    int getStartIndex(const vector<int> &sortedRequests) {
        int startIndex = 0;
        for (int i = 0; i < REQUESTS_NUMBER; i++)
        {
            if (sortedRequests[i] >= initialHeadPosition)
            {
                startIndex = i;
                break;
            }
        }
        return startIndex;
    }

    /// @brief generates a sequence of REQUESTS_NUMBER requests in range 0-4999
    void generateRequests()
    {
        srand(time(0));
        requests.clear();
        for (int i = 0; i < REQUESTS_NUMBER; i++)
        {
            requests.push_back(rand() % CYLINDERS_NUMBER);
        }
    }

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
            currentPosition = requests[servedRequestIndex];
        }
        return headMovement;
    }

    /// @brief SCAN disk scheduling algorithm
    /// @return total amount of head movement from start position
    int scan() {
        int currentPosition = initialHeadPosition;
        int headMovement = 0;

        vector<int> tempRequests = requests;
        sort(tempRequests.begin(), tempRequests.end());

        int startIndex = getStartIndex(tempRequests);

        // move to highest request
        for (int i = startIndex; i < REQUESTS_NUMBER; i++) {
            headMovement += abs(currentPosition - tempRequests[i]);
            currentPosition = tempRequests[i];
        }

        headMovement += abs(currentPosition - (CYLINDERS_NUMBER - 1)); // simulate it reached the end
        currentPosition = CYLINDERS_NUMBER - 1;

        if (startIndex > 0) {
            for (int i = startIndex - 1; i >= 0; i--) {
                headMovement += abs(currentPosition - tempRequests[i]);
                currentPosition = tempRequests[i];
            }
        }
        return headMovement;
    }

    /// @brief C-SCAN disk scheduling algorithm
    /// @return total amount of head movement from start position
    int cscan() {
        int currentPosition = initialHeadPosition;
        int headMovement = 0;

        vector<int> tempRequests = requests;
        sort(tempRequests.begin(), tempRequests.end());

        int startIndex = getStartIndex(tempRequests);

        // move the head to the right end of the cylinder
        for (int i = startIndex; i < REQUESTS_NUMBER; i++) {
            headMovement += abs(currentPosition - tempRequests[i]);
            currentPosition = tempRequests[i];
        }
        
        // Jump to beginning
        if (startIndex > 0) {
            headMovement += abs(currentPosition - (CYLINDERS_NUMBER - 1)); // From final request to end
            headMovement += CYLINDERS_NUMBER - 1; // From end to 0
            currentPosition = 0;
        }

        for (int i = 0; i < startIndex; i++) {
            headMovement += abs(currentPosition - tempRequests[i]);
            currentPosition = tempRequests[i];
        }

        return headMovement;
    }

    /// @brief LOOK disk scheduling algorithm
    /// @return total amount of head movement from start position
    int look() {
        int currentPosition = initialHeadPosition;
        int headMovement = 0;
        vector<int> tempRequests = requests;

        sort(tempRequests.begin(), tempRequests.end());

        int startIndex = getStartIndex(tempRequests);

        // serve from start position till the final request
        for (int i = startIndex; i < REQUESTS_NUMBER; i++) {
            headMovement += abs(currentPosition - tempRequests[i]);
            currentPosition = tempRequests[i];
        }

        
        for (int i = startIndex - 1; i >= 0; i--) {
            headMovement += abs(currentPosition - tempRequests[i]);
            currentPosition = tempRequests[i];
        }
        return headMovement;
    }

    /// @brief C-LOOK disk scheduling algorithm
    /// @return total amount of head movement from start position
    int clook() {
        int currentPosition = initialHeadPosition;
        int headMovement = 0;
        vector<int> tempRequests = requests;

        sort(tempRequests.begin(), tempRequests.end());

        int startIndex = getStartIndex(tempRequests);

        // serve from start position till the final request
        for (int i = startIndex; i < REQUESTS_NUMBER; i++)
        {
            headMovement += abs(currentPosition - tempRequests[i]);
            currentPosition = tempRequests[i];
        }

        // jump from final request to first request
        if (startIndex > 0) {
            headMovement += abs(currentPosition - tempRequests[0]);
            currentPosition = tempRequests[0];
        }

        // serve from first request
        for (int i = 0; i < startIndex; i++)
        {
            headMovement += abs(currentPosition - tempRequests[i]);
            currentPosition = tempRequests[i];
        }
        return headMovement;
    }
};