#include <bits/stdc++.h>
using namespace std;

int main()
{

    int Sum = 0;
    int a,b;
    vector<int> arrLeft;
    vector<int> arrRight;

    ifstream file("./day1Input.txt");

    if(!file){
        cout << "File is not open successfully" << endl;
    }

    while(file >> a >> b){
        arrLeft.push_back(a);
        arrRight.push_back(b);
    }

    for (int i = 0; i < arrLeft.size(); i++)
    {
        int count = 0;
        for (int j = 0; j < arrRight.size(); j++)
        {
            if (arrLeft[i] == arrRight[j])
            {
                count++;
            }
        }
        Sum += arrLeft[i] * count;
    }

    cout << Sum;
}