#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

/**
 * Parses a string and splits it into integers based on a given delimiter.
 * For instance: "75,47,61" with a comma separator will result in [75, 47, 61].
 *
 * @param line The string to split
 * @param delimiter The character that separates the integers
 * @return A vector of integers extracted from the string
 */
vector<int> parseLineToInt(const string& line, char delimiter) {
    vector<int> numbers;
    stringstream stream(line);  // Use a stringstream to tokenize the string
    string temp;

    // Split the string by the delimiter and convert each part to an integer
    while (getline(stream, temp, delimiter)) {
        numbers.push_back(stoi(temp));  // Convert string to int and add to the vector
    }

    return numbers;
}

int main() {
    ifstream inputFile("./inputFile/day5Input.txt");  // Open the input file
    string line;

    vector<pair<int, int>> rules;  // Holds the ordering rules (first page must come before second page)
    vector<vector<int>> updates;   // Holds the update page lists

    // Read the file line by line
    while (getline(inputFile, line)) {
        if (line.find('|') != string::npos) {
            // If the line contains '|' it's a rule (e.g., "47|53")
            vector<int> rule = parseLineToInt(line, '|');
            rules.push_back({rule[0], rule[1]});
        } else if (!line.empty()) {
            // If the line doesn't contain '|' and is not empty, it's an update
            vector<int> updatePages = parseLineToInt(line, ',');
            updates.push_back(updatePages);
        }
    }

    int totalMiddlePage = 0;  // To store the sum of middle pages from valid updates

    // Process each update in the list
    for (const auto& update : updates) {
        unordered_map<int, int> pageOrder;  // A map to store the position of each page in the update list

        // Populate the page position map
        for (int i = 0; i < update.size(); ++i) {
            pageOrder[update[i]] = i;
        }

        bool isOrderValid = true;  // Assume the order is valid unless proven otherwise

        // Validate each rule for this update
        for (const auto& rule : rules) {
            int pageA = rule.first;
            int pageB = rule.second;

            // Check if both pages from the rule are in the update list
            if (pageOrder.count(pageA) && pageOrder.count(pageB)) {
                // Ensure that pageA comes before pageB
                if (pageOrder[pageA] >= pageOrder[pageB]) {
                    isOrderValid = false;  // Rule violation
                    break;  // No need to check further rules
                }
            }
        }

        // If the update satisfies all rules, calculate the middle page and add it to the total
        if (isOrderValid) {
            int middlePage = update[update.size() / 2];  // Get the middle page from the update
            totalMiddlePage += middlePage;  // Add the middle page to the total sum
        }
    }

    // Output the result
    cout << "Sum of middle pages from valid updates: " << totalMiddlePage << endl;

    return 0;
}
