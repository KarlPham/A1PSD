#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Directional vectors for diagonals (↖ A ↘ and ↙ A ↗)
const int DX1[] = {-1, 0, 1};  // Diagonal directions for top-left to bottom-right
const int DY1[] = {-1, 0, 1};

const int DX2[] = {1, 0, -1};  // Diagonal directions for bottom-left to top-right
const int DY2[] = {-1, 0, 1};

/**
 * Extracts a 3-letter word from the grid diagonally, starting from a given (row, col) position.
 * The direction is determined by the provided dx and dy arrays, which specify the offset to move.
 *
 * @param grid The 2D grid of characters (string vector)
 * @param row The current row (starting point)
 * @param col The current column (starting point)
 * @param dx Array of x-direction offsets
 * @param dy Array of y-direction offsets
 * @return A 3-letter string representing the diagonal word or an empty string if out of bounds
 */
string getDiagonalWord(const vector<string>& grid, int row, int col, const int dx[], const int dy[]) {
    string word;  // String to hold the diagonal word
    int rows = grid.size();    // Number of rows in the grid
    int cols = grid[0].size(); // Number of columns in the grid

    // Collect the 3 letters diagonally from the starting point (row, col)
    for (int i = 0; i < 3; ++i) {
        int r = row + dy[i];  // Calculate the next row position
        int c = col + dx[i];  // Calculate the next column position

        // If the position is out of bounds, return an empty string
        if (r < 0 || r >= rows || c < 0 || c >= cols)
            return " ";

        word += grid[r][c];  // Add the character to the word
    }
    return word;  // Return the formed word from the diagonal
}

/**
 * Counts the number of "X-MAS" occurrences in the grid.
 * An "X-MAS" pattern requires two diagonals with the words "MAS" or "SAM",
 * centered around a character 'A' in the grid.
 *
 * @param grid The 2D grid of characters (string vector)
 * @return The total number of valid "X-MAS" patterns found in the grid
 */
int countXMAS(const vector<string>& grid) {
    int count = 0;  // Initialize the count of valid "X-MAS" patterns

    // Loop through each cell in the grid, avoiding the edge cells (since they can't have 'A' as a center)
    for (int row = 1; row < grid.size() - 1; ++row) {
        for (int col = 1; col < grid[0].size() - 1; ++col) {

            // If the current cell contains 'A' (center of the potential "X-MAS" pattern)
            if (grid[row][col] == 'A') {
                // Get both diagonals from the current 'A' (↖ A ↘ and ↙ A ↗)
                string diag1 = getDiagonalWord(grid, row, col, DX1, DY1); // First diagonal (↖ A ↘)
                string diag2 = getDiagonalWord(grid, row, col, DX2, DY2); // Second diagonal (↙ A ↗)

                // Check if both diagonals are valid (either "MAS" or "SAM")
                if ((diag1 == "MAS" || diag1 == "SAM") && (diag2 == "MAS" || diag2 == "SAM"))
                    count++;  // Increment the count if both diagonals are valid
            }
        }
    }

    return count;  // Return the total count of valid "X-MAS" patterns
}

int main() {
    // Open the input file containing the grid
    ifstream file("./inputFile/day4Input.txt");

    // Check if the file opened successfully
    if (!file) {
        cerr << "Error opening input file.\n";  // Print error message if the file can't be opened
        return 1;
    }

    vector<string> grid;  // Vector to store each line of the grid as a string
    string line;

    // Read the grid from the file line by line
    while (getline(file, line))
        grid.push_back(line);  // Add each line to the grid
    file.close();  // Close the file after reading

    // Compute the total number of "X-MAS" patterns in the grid
    int result = countXMAS(grid);

    // Output the result
    cout << "Total X-MAS: " << result << endl;

    return 0;  // Return 0 to indicate successful execution
}
