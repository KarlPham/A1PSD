#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

/**
 * Splits a given line of text into integers based on a specified separator.
 * For example: "75,47,61" with separator ',' becomes [75, 47, 61]
 * 
 * @param input A string containing numbers separated by a delimiter.
 * @param delimiter The character separating the numbers in the string.
 * @return A vector of integers extracted from the string.
 */
vector<int> parseNumbers(const string& input, char delimiter) {
    vector<int> numbers;
    stringstream ss(input);
    string segment;

    // Split the string by the delimiter and convert each part to an integer
    while (getline(ss, segment, delimiter)) {
        numbers.push_back(stoi(segment)); // Convert string to integer
    }
    return numbers;
}

/**
 * Conducts a topological sort on a list of pages using Kahn's algorithm.
 * It orders the pages according to the defined dependencies.
 *
 * @param pages The list of page numbers to be sorted.
 * @param dependencies A list of dependency rules indicating the order of pages.
 * @return A vector representing the sorted order of pages.
 */
vector<int> sortPagesTopologically(const vector<int>& pages, const vector<pair<int, int>>& dependencies) {
    unordered_map<int, vector<int>> adjList;   // Adjacency list to represent the graph
    unordered_map<int, int> inDegree;          // Map for tracking the in-degree of each page

    unordered_set<int> pageSet(pages.begin(), pages.end()); // Set for fast page lookup

    // Initialize the in-degree map for all pages
    for (int page : pages) {
        inDegree[page] = 0;
    }

    // Build the graph and calculate in-degrees based on the dependency rules
    for (const auto& [before, after] : dependencies) {
        if (pageSet.count(before) && pageSet.count(after)) {
            adjList[before].push_back(after);  // Add edge: before -> after
            inDegree[after]++;  // Increase in-degree of the "after" page
        }
    }

    // Initialize the queue with pages that have no incoming edges (in-degree of 0)
    queue<int> q;
    for (const auto& [page, degree] : inDegree) {
        if (degree == 0) q.push(page);
    }

    // Perform Kahn's algorithm for topological sorting
    vector<int> sortedPages;
    while (!q.empty()) {
        int current = q.front(); q.pop();
        sortedPages.push_back(current);

        // Process all neighbors (dependent pages)
        for (int neighbor : adjList[current]) {
            inDegree[neighbor]--;  // Decrease the in-degree
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);  // If no more dependencies, add to queue
            }
        }
    }

    return sortedPages;  // Return the topologically sorted pages
}

int main() {
    ifstream file("./inputFile/day5Input.txt"); // Open the input file
    string line;

    vector<pair<int, int>> dependencyRules;  // Stores page dependency rules
    vector<vector<int>> updates;             // Stores updates (lists of page numbers)

    // Read the file and parse each line
    while (getline(file, line)) {
        if (line.find('|') != string::npos) {
            // Line contains a dependency rule (e.g., "47|53")
            vector<int> rule = parseNumbers(line, '|');
            dependencyRules.push_back({rule[0], rule[1]});
        } else if (!line.empty()) {
            // Line contains a page update list (e.g., "75,47,61")
            updates.push_back(parseNumbers(line, ','));
        }
    }

    int correctedMiddleSum = 0;  // Total sum of middle pages after fixing invalid updates

    // Process each update
    for (const auto& update : updates) {
        unordered_map<int, int> pageIndices; // Store the position of each page in the update

        // Map the pages to their respective positions in the update
        for (int i = 0; i < update.size(); ++i) {
            pageIndices[update[i]] = i;
        }

        bool isValidUpdate = true;  // Assume the update is valid unless proven otherwise

        // Check if the update respects all ordering rules
        for (const auto& [before, after] : dependencyRules) {
            if (pageIndices.count(before) && pageIndices.count(after)) {
                // Ensure that 'before' appears before 'after'
                if (pageIndices[before] >= pageIndices[after]) {
                    isValidUpdate = false;  // Rule violated
                    break;
                }
            }
        }

        // If the update is invalid, correct it by topologically sorting the pages
        if (!isValidUpdate) {
            vector<int> sortedPages = sortPagesTopologically(update, dependencyRules);

            // Get the middle page from the sorted order
            int middlePage = sortedPages[sortedPages.size() / 2];

            // Add the middle page to the total sum
            correctedMiddleSum += middlePage;
        }
    }

    // Output the final result
    cout << "Corrected sum of middle pages from valid updates: " << correctedMiddleSum << endl;

    return 0;
}
