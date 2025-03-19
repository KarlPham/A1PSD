#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <numeric>

using namespace std;

int main()
{
    ifstream file("./inputFile/day3Input.txt");
    if (!file)
    {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    // Read the entire file into a single string
    string corrupted_memory((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close(); // Close the file after reading

    // Define regex pattern to match valid mul(X, Y), do(), and don't() instructions
    regex pattern("(mul\\((\\d{1,3}),(\\d{1,3})\\)|do\\(\\)|don't\\(\\))");
    smatch match;

    bool calculate = true;  // Flag to determine if calculations should be performed
    int totalSum = 0;       // Store the sum of valid multiplications

    string::const_iterator search_start = corrupted_memory.cbegin();

    // Scan through the input and process each instruction
    while (regex_search(search_start, corrupted_memory.cend(), match, pattern))
    {
        string command = match[0].str();

        if (command == "do()")
        {
            calculate = true;  // Enable calculations
        }
        else if (command == "don't()")
        {
            calculate = false; // Disable calculations
        }
        else if (calculate && match.size() > 2) // Ensure valid mul(X,Y)
        {
            int x = stoi(match[2].str());
            int y = stoi(match[3].str());
            totalSum += x * y; // Add the multiplication result to the sum
        }
        // Move the search forward
        search_start = match.suffix().first;
    }

    // Print the final total sum
    cout << "Total sum of enabled multiplications: " << totalSum << endl;

    return 0;
}
