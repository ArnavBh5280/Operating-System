#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Define INT_MAX manually
#define INT_MAX 2147483647

// Function to simulate FIFO Page Replacement
void simulateFIFO(vector<int> pages, int capacity) {
    cout << "\nFIFO Page Replacement:\n";
    vector<int> frame;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        // Check if the page is already in the frame
        if (find(frame.begin(), frame.end(), pages[i]) == frame.end()) {
            if (frame.size() == capacity) {
                frame.erase(frame.begin()); // Remove the oldest page
            }
            frame.push_back(pages[i]); // Add the new page
            pageFaults++;
        }
        cout << "Page: " << pages[i] << " | Frame: ";
        for (int page : frame) cout << page << " ";
        cout << "\n";
    }
    cout << "Total Page Faults (FIFO): " << pageFaults << "\n";
}

// Function to simulate LRU Page Replacement
void simulateLRU(vector<int> pages, int capacity) {
    cout << "\nLRU Page Replacement:\n";
    vector<int> frame;
    unordered_map<int, int> recent; // Stores the most recent use of each page
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        // Check if the page is already in the frame
        if (find(frame.begin(), frame.end(), pages[i]) == frame.end()) {
            if (frame.size() == capacity) {
                // Find the least recently used page
                int lru = INT_MAX, lruIndex = -1;
                for (int j = 0; j < frame.size(); j++) {
                    if (recent[frame[j]] < lru) {
                        lru = recent[frame[j]];
                        lruIndex = j;
                    }
                }
                frame.erase(frame.begin() + lruIndex); // Remove the LRU page
            }
            frame.push_back(pages[i]); // Add the new page
            pageFaults++;
        }
        recent[pages[i]] = i; // Update the most recent use of the page

        cout << "Page: " << pages[i] << " | Frame: ";
        for (int page : frame) cout << page << " ";
        cout << "\n";
    }
    cout << "Total Page Faults (LRU): " << pageFaults << "\n";
}

// Function to simulate Optimal Page Replacement
void simulateOptimal(vector<int> pages, int capacity) {
    cout << "\nOptimal Page Replacement:\n";
    vector<int> frame;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        // Check if the page is already in the frame
        if (find(frame.begin(), frame.end(), pages[i]) == frame.end()) {
            if (frame.size() == capacity) {
                // Find the page to replace based on future use
                int farthest = i, victimIndex = -1;
                for (int j = 0; j < frame.size(); j++) {
                    auto it = find(pages.begin() + i + 1, pages.end(), frame[j]);
                    if (it == pages.end()) { // Page is not used in the future
                        victimIndex = j;
                        break;
                    }
                    int distance = it - pages.begin();
                    if (distance > farthest) {
                        farthest = distance;
                        victimIndex = j;
                    }
                }
                frame.erase(frame.begin() + victimIndex); // Remove the victim page
            }
            frame.push_back(pages[i]); // Add the new page
            pageFaults++;
        }
        cout << "Page: " << pages[i] << " | Frame: ";
        for (int page : frame) cout << page << " ";
        cout << "\n";
    }
    cout << "Total Page Faults (Optimal): " << pageFaults << "\n";
}

int main() {
    int numPages, capacity;

    // Input the number of pages and frame capacity
    cout << "Enter the number of pages: ";
    cin >> numPages;
    vector<int> pages(numPages);
    cout << "Enter the reference string (page numbers):\n";
    for (int i = 0; i < numPages; i++) {
        cin >> pages[i];
    }

    cout << "Enter the frame capacity: ";
    cin >> capacity;

    // Simulate all algorithms
    simulateFIFO(pages, capacity);
    simulateLRU(pages, capacity);
    simulateOptimal(pages, capacity);

    return 0;
}
