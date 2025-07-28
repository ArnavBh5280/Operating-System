#include <iostream>
#include <vector>
using namespace std;

// Function to simulate paging
void simulatePaging(int logicalAddress, int pageSize, int numPages, vector<int> &pageTable) {
    int pageNumber = logicalAddress / pageSize;       // Determine the page number
    int offset = logicalAddress % pageSize;          // Determine the offset within the page

    // Check if the page number is valid
    if (pageNumber >= numPages || pageNumber < 0) {
        cout << "Invalid Logical Address: " << logicalAddress << "\n";
        return;
    }

    // Map the logical address to physical address
    int frameNumber = pageTable[pageNumber];         // Get the frame number from the page table
    if (frameNumber == -1) {
        cout << "Page Fault! Page " << pageNumber << " is not in memory.\n";
        return;
    }

    int physicalAddress = frameNumber * pageSize + offset;  // Calculate physical address
    cout << "Logical Address: " << logicalAddress
         << " | Page Number: " << pageNumber
         << " | Offset: " << offset
         << " | Physical Address: " << physicalAddress << "\n";
}

int main() {
    int pageSize, numPages;

    // Input page size and number of pages
    cout << "Enter page size (in bytes): ";
    cin >> pageSize;
    cout << "Enter number of pages: ";
    cin >> numPages;

    vector<int> pageTable(numPages, -1); // Initialize page table with -1 (indicating pages are not in memory)

    // Input frame numbers for pages
    cout << "Enter the frame number for each page (-1 if the page is not in memory):\n";
    for (int i = 0; i < numPages; i++) {
        cout << "Page " << i << ": ";
        cin >> pageTable[i];
    }

    int logicalAddress;
    char choice;

    // Simulate address mapping
    do {
        cout << "\nEnter a logical address to map: ";
        cin >> logicalAddress;

        simulatePaging(logicalAddress, pageSize, numPages, pageTable);

        cout << "Do you want to map another address? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
