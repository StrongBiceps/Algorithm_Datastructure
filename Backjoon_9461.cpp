#include <iostream>

using namespace std;

long long DP[100] = { 0 };

long long Dynamic(int n)
{

    for (size_t i = 5; i < n; ++i)
    {
        DP[i] = DP[i - 1] + DP[i - 5];
    }

    return DP[n-1];
}

int main()
{
    DP[0] = 1;
    DP[1] = 1;
    DP[2] = 1;
    DP[3] = 2;
    DP[4] = 2;

    int N;
    int T;
    cin >> T;

    int Count = 0;
    while (Count < T)
    {
        cin >> N;
 
        cout << Dynamic(N) << '\n';
        ++Count;
    }
}