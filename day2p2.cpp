#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main() {
    ifstream file("./inputFile/day2Input.txt");
    if (!file) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    vector<vector<int> > allLines;
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        vector<int> numbers;
        int num;

        while (ss >> num) {
            numbers.push_back(num);
        }
        allLines.push_back(numbers);
    }

    file.close();
    int countSafe = 0;

    for (int i = 0; i < allLines.size(); i++) {
        bool isIncrease = false;
        bool isDecrease = false;
        int check = 1;
        
        for (int j = 0; j < allLines[i].size() - 1; j++) {
            int diff = allLines[i][j + 1] - allLines[i][j];
            
            if (abs(diff) < 1 || abs(diff) > 3) {
                check = 0;
                break;
            }
            if (diff > 0) {
                isIncrease = true;
            } else {
                isDecrease = true;
            }
        }

        if (check && (isIncrease != isDecrease)) {
            countSafe++;
            continue;
        }
        
        bool canBeSafe = false;
        for (int j = 0; j < allLines[i].size(); j++) {
            vector<int> modified = allLines[i]; 
            modified.erase(modified.begin() + j); 
            
            bool tempIncrease = false;
            bool tempDecrease = false;
            int tempCheck = 1;
            
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
            
            if (tempCheck && (tempIncrease != tempDecrease)) {
                canBeSafe = true;
                break;
            }
        }
        
        if (canBeSafe) {
            countSafe++;
        }
    }

    cout << countSafe << endl;
    return 0;
}
