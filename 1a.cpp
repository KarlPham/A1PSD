#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int distantSum = 0; // Variable to store total distance
    int a, b; // Temporary variables to read input pairs

    vector<int> arrLeft;  // Vector to store the first numbers of each pair
    vector<int> arrRight; // Vector to store the second numbers of each pair

    ifstream file("./inputFile/day1Input.txt"); // Open the input file

    if(!file){
        cout << "File is not open successfully" << endl; // Error if file cannot be opened
    }

    // Read pairs of integers from the file
    while (file >> a >> b){
        arrLeft.push_back(a);   // Store first number in arrLeft
        arrRight.push_back(b);  // Store second number in arrRight
    }

    file.close(); // Close the file after reading

    // Sort both arrays
    sort(arrLeft.begin(), arrLeft.end());
    sort(arrRight.begin(), arrRight.end());

    // Calculate the total distance by summing up absolute differences
    for (int i = 0; i < arrLeft.size(); i++)
    {
        distantSum += abs(arrLeft[i] - arrRight[i]);
    }

    cout << "Result is: "<<distantSum; // Output the result
}
