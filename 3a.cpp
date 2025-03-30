#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

int main()
{
    ifstream file("./inputFile/day3Input.txt");
    if (!file)
    { // Check if the file was opened successfully
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    // Read the entire file into a single string
    string corrupted_memory((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // Define regex pattern to match valid mul(X, Y) instructions
    regex pattern("mul\\((\\d{1,3}),(\\d{1,3})\\)");
    smatch match;
    int totalSum = 0;

    // Use const_iterator correctly
    string::const_iterator search_start = corrupted_memory.cbegin();

    // Find all valid mul(X, Y) instructions
    while (regex_search(search_start, corrupted_memory.cend(), match, pattern))
    {
        if (match[1].length() < 4 && match[2].length() < 4)
        {
            int x = stoi(match[1]);
            int y = stoi(match[2]);
            totalSum += x * y;
        }

        search_start = match.suffix().first; // Move iterator forward
    }

    cout << "the results of the multiplications is: " << totalSum << endl;
}
