#include <iostream>
using namespace std;

int DP[1000001] = { 0 };

int main()
{
    int N;
    DP[0] = 1;
    DP[1] = 2;
    cin >> N;
    
    for (size_t i = 2; i < N; ++i)
    {
        DP[i] = DP[i - 1]%15746 + DP[i - 2]%15746;
    }

    cout << DP[N - 1] % 15746;
}