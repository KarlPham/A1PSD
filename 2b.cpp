#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    ifstream file("./inputFile/day2Input.txt"); // Open input file
    if (!file) {
        cout << "Error opening file!" << endl; // Show error if file can't be opened
        return 1;
    }

    vector<vector<int>> allLines; // Store each line as a vector of integers
    string line;
    
    // Read file line by line
    while (getline(file, line)) {
        stringstream ss(line);  // Use stringstream to extract integers
        vector<int> numbers;
        int num;

        while (ss >> num) {
            numbers.push_back(num); // Add each number to the vector
        }
        allLines.push_back(numbers); // Add the line to the list of all lines
    }

    file.close(); // Close the file

    int countSafe = 0; // Counter for "safe" lines

    // Go through each line of numbers
    for (int i = 0; i < allLines.size(); i++) {
        bool isIncrease = false; // To check if values increase
        bool isDecrease = false; // To check if values decrease
        int check = 1; // Set to 0 if the line is invalid
        
        // Compare adjacent values
        for (int j = 0; j < allLines[i].size() - 1; j++) {
            int diff = allLines[i][j + 1] - allLines[i][j];
            
            // Check if the difference is out of allowed range
            if (abs(diff) < 1 || abs(diff) > 3) {
                check = 0;
                break;
            }

            // Track direction
            if (diff > 0) {
                isIncrease = true;
            } else {
                isDecrease = true;
            }
        }

        // Safe if valid and strictly increasing or decreasing
        if (check && (isIncrease != isDecrease)) {
            countSafe++;
            continue;
        }

        // Try removing one element to see if the line can become safe
        bool canBeSafe = false;
        for (int j = 0; j < allLines[i].size(); j++) {
            vector<int> modified = allLines[i]; 
            modified.erase(modified.begin() + j); // Remove one element
            
            bool tempIncrease = false;
            bool tempDecrease = false;
            int tempCheck = 1;

            // Re-check the modified line
            for (int k = 0; k < modified.size() - 1; k++) {
                int tempDiff = modified[k + 1] - modified[k];
                
                if (abs(tempDiff) < 1 || abs(tempDiff) > 3) {
                    tempCheck = 0;
                    break;
                }

                if (tempDiff > 0) {
                    tempIncrease = true;
                } else {
                    tempDecrease = true;
                }
            }

            // If valid and strictly increasing/decreasing after deletion
            if (tempCheck && (tempIncrease != tempDecrease)) {
                canBeSafe = true;
                break;
            }
        }

        // If it can be made safe by removing one element
        if (canBeSafe) {
            countSafe++;
        }
    }

    cout << "The numbers of safe reports are:" << countSafe << endl; // Output total safe lines
    return 0;
}
