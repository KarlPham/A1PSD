#include <bits/stdc++.h>
using namespace std;
int main()
{
    int distantSum = 0;
    int a,b;
    vector<int> arrLeft;
    vector<int> arrRight;
    ifstream file("./day1Input.txt");

    if(!file){
        cout << "File is not open successfully" << endl;
    }


    while (file >> a >> b){
        arrLeft.push_back(a);
        arrRight.push_back(b);
    }

    file.close();

    sort(arrLeft.begin(), arrLeft.end());
    sort(arrRight.begin(), arrRight.end());

    for (int i = 0; i < arrLeft.size(); i++)
    {
        distantSum += abs(arrLeft[i] - arrRight[i]);
    }
    
     
    cout << distantSum;
}
