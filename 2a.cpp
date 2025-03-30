#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
    ifstream file("./inputFile/day2Input.txt"); // Open the input file

    if (!file)
    {
        cout << "Error" << endl; // Display error if file fails to open
        return 1;
    }

    vector<vector<int>> allLines; // Vector to store all lines as vectors of integers
    string line;

    // Read each line from the file
    while (getline(file, line))
    {
        stringstream ss(line); // Create stringstream from the line
        vector<int> numbers;   // Vector to store numbers from the line
        int num;

        // Extract all integers from the line
        while (ss >> num)
        {
            numbers.push_back(num);
        }

        allLines.push_back(numbers); // Add the extracted line to allLines
    }

    file.close(); // Close the file

    int countSafe = 0; // Count of valid "safe" lines

    // Process each line
    for (int i = 0; i < allLines.size(); i++)
    {
        bool isIncrease = false; // Whether the line has increasing values
        bool isDecrease = false; // Whether the line has decreasing values
        int check = 1; // Flag to check if all differences are between 1 and 3

        // Compare each adjacent pair of numbers in the line
        for (int j = 0; j < allLines[i].size() - 1; j++)
        {
            int diff = allLines[i][j + 1] - allLines[i][j];

            // If the absolute difference is not in the range 1–3, mark as invalid
            if (abs(diff) < 1 || abs(diff) > 3)
            {
                check = 0;
                break;
            }

            // Track the direction of the difference
            if (diff > 0)
            {
                isIncrease = true;
            }
            else
            {
                isDecrease = true;
            }
        }

        // Count as "safe" if the whole line is strictly increasing or strictly decreasing
        if (check && isIncrease && !isDecrease)
        {
            countSafe++;
        }
        else if (check && !isIncrease && isDecrease)
        {
            countSafe++;
        }
    }

    cout << "The numbers of safe reports are: " << countSafe; // Output the count of safe lines
}
