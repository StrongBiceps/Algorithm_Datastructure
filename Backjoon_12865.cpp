#include <iostream>
#include <vector>
using namespace std;

int N;
int K;

int main()
{
    cin >> N;
    cin >> K;

    vector<int> W(N + 1, 0);
    vector<int> V(N + 1, 0);

    for (int i = 0; i < N; ++i)
    {
        cin >> W[i] >> V[i];
    }

    vector<vector<int>> DP(N + 1, vector<int>(K+1, 0));

    for (int i = 1; i <= N; ++i)
    {
        int w = W[i - 1];
        int v = V[i - 1];

        for (int j = 1; j <= K; ++j)
        {
            if (j < w)
                DP[i][j] = DP[i - 1][j];
            else
            {
                DP[i][j] = max(DP[i - 1][j], DP[i - 1][j - w] + v);
            }
        }
    }
    cout << DP[N][K];
}