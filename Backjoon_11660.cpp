#include <iostream>
using namespace std;

long long DP[1024][1024] = { 0 };
int N, M;

int main()
{
    cin >> N >> M;
    int number;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> number;
            DP[i][j] = DP[i - 1][j] + DP[i][j - 1]
        }
    }
}