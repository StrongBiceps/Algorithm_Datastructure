#include <iostream>
using namespace std;

int arr[300] = { 0 };
int DP[300] = { 0 };
int N;

int main()
{
    cin >> N;

    for (size_t i = 0; i < N; ++i)
    {
        cin >> arr[i];
    }

    DP[0] = arr[0];
    DP[1] = arr[0] + arr[1];
    DP[2] = max(arr[0] + arr[2], arr[1] + arr[2]);

    for (size_t i = 3; i < N; ++i)
    {
        DP[i] = max(DP[i - 3] + arr[i - 1] + arr[i], DP[i - 2] + arr[i]);
    }

    cout << DP[N - 1];
}