#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    ifstream file("./inputFile/day2Input.txt");

    if (!file)
    {
        cout << "Error" << endl;
        return 1;
    }

    vector<vector<int> > allLines;

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        vector<int> numbers;
        int num;

        while (ss >> num)
        {
            numbers.push_back(num);
        }
        allLines.push_back(numbers);
    }


    file.close();
    int countSafe = 0;

    for (int i = 0; i < allLines.size(); i++)
    {
        bool isIncrease = false;
        bool isDecrease = false;
        int check = 1;
        for (int j = 0; j < allLines[i].size() - 1; j++)
        {

            int diff = allLines[i][j + 1] - allLines[i][j];
            
            if (abs(diff) < 1 || abs(diff) > 3)
            {
                check = 0;
                break;
            }
            if (diff > 0)
            {
                isIncrease = true;
            }
            else
            {
                isDecrease = true;
            }
        }

        if (check && isIncrease && !isDecrease)
        {
            countSafe++;
        }
        else if (check && !isIncrease && isDecrease)
        {
            countSafe++;
        }
    }

    cout << countSafe;
}