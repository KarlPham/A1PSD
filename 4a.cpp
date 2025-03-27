#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Directions for searching in 8 possible ways
const vector<pair<int, int>> directions = {
    {0, 1}, {1, 0}, {1, 1}, {1, -1}, 
    {0, -1}, {-1, 0}, {-1, -1}, {-1, 1}};

// Check if a position is within grid bounds
bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

// Function to count occurrences of a word in the grid
int countWordOccurrences(vector<vector<char>> &grid, string word) {
    int rows = grid.size(), cols = grid[0].size(), count = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == word[0]) { // Start searching from first letter
                for (auto [dx, dy] : directions) {
                    int x = i, y = j, k = 0;
                    while (k < word.size() && isValid(x, y, rows, cols) && grid[x][y] == word[k]) {
                        x += dx;
                        y += dy;
                        k++;
                    }
                    if (k == word.size()) count++;
                }
            }
        }
    }
    return count;
}

int main() {
    ifstream file("./inputFile/day4Input.txt"); // Open input file
    if (!file) {
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    vector<string> lines;
    string line;

    // Read all lines from file
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    if (lines.empty()) {
        cerr << "Error: Empty file." << endl;
        return 1;
    }

    // Last line is the word to search
    string word = "XMAS";

    // Determine grid size
    int rows = lines.size();
    int cols = lines[0].size();

    // Convert string vector into a 2D grid
    vector<vector<char>> grid(rows, vector<char>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = lines[i][j]; // Copy each character
        }
    }

    // Count occurrences of the word in the grid
    int count = countWordOccurrences(grid, word);
    cout << "Word \"" << word << "\" found " << count << " times in the grid." << endl;

    return 0;
}
