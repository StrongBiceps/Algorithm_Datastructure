#include <iostream>
#include <string>
using namespace std;

int DP[1001][1001] = { 0 };

string A;
string B;

int main()
{
    cin >> A >> B;

    for (int i = 0; i <= A.size(); ++i)
    {
        for (int j = 0; j <= B.size(); ++j)
        {
            if (i == 0 || j == 0)
                DP[i][j] = 0;
            else if (A[i-1] == B[j-1])
                DP[i][j] = DP[i - 1][j - 1] + 1;
            else
                DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
        }
    }

    cout << DP[A.size()][B.size()];
}