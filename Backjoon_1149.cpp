#include <iostream>
#include <vector>
using namespace std;

int N;
int DP[1000][3] = { 0 };
int Value[1000][3] = { 0 };
int Result = 1000000;

void Dynamic()
{
    DP[0][0] = Value[0][0];
    DP[0][1] = Value[0][1];
    DP[0][2] = Value[0][2];

    for (size_t i = 1; i < N; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            if (j == 0)
                DP[i][j] = min(DP[i - 1][1] + Value[i][0], DP[i - 1][2] + Value[i][0]);
            else if (j == 1)
                DP[i][j] = min(DP[i - 1][0] + Value[i][1], DP[i - 1][2] + Value[i][1]);
            else
                DP[i][j] = min(DP[i - 1][0] + Value[i][2], DP[i - 1][1] + Value[i][2]);
        }
    }

    for (size_t i = 0; i < 3; ++i)
    {
        if (DP[N - 1][i] < Result)
            Result = DP[N - 1][i];
    }
}

int main()
{
    cin >> N;

    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            cin >> Value[i][j];
        }
    }

    Dynamic();

    cout << Result;
}

/*모범 답안*/
#include <iostream>
#include <algorithm>
using namespace std;
int house[1001][3];
int main() {
    int N;
    int cost[3];
    house[0][0] = 0;
    house[0][1] = 0;
    house[0][2] = 0;
    cin >> N;
    for (int i = 1; i <= N; ++i)
    {
        cin >> cost[0] >> cost[1] >> cost[2];
        house[i][0] = min(house[i - 1][1], house[i - 1][2]) + cost[0];
        house[i][1] = min(house[i - 1][0], house[i - 1][2]) + cost[1];
        house[i][2] = min(house[i - 1][1], house[i - 1][0]) + cost[2];
    }
    cout << min(house[N][2], min(house[N][0], house[N][1]));
}