#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

int main()
{
    int Sum = 0; // Variable to store the final calculated sum
    int a, b; // Temporary variables to store pairs from the file

    vector<int> arrLeft;  // Vector to store first values from each pair
    vector<int> arrRight; // Vector to store second values from each pair

    ifstream file("./inputFile/day1Input.txt"); // Open input file

    if(!file){
        cout << "File is not open successfully" << endl; // Error message if file not opened
    }

    // Read pairs of integers from the file and store them in two arrays
    while(file >> a >> b){
        arrLeft.push_back(a);
        arrRight.push_back(b);
    }

    // Loop through each element in arrLeft
    for (int i = 0; i < arrLeft.size(); i++)
    {
        int count = 0; // To count how many times arrLeft[i] appears in arrRight

        // Compare with every element in arrRight
        for (int j = 0; j < arrRight.size(); j++)
        {
            if (arrLeft[i] == arrRight[j]) // Match found
            {
                count++;
            }
        }

        // Multiply arrLeft[i] by number of matches and add to total sum
        Sum += arrLeft[i] * count;
    }

    cout << "Sum is: " << Sum; // Output the final result
}
