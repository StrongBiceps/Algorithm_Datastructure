#include <iostream>
#include <climits>
using namespace std;

int DP[100001] = { 0 };
int arr[100001] = { 0 };
int N;
int K;
int Result = INT_MIN;

//절대 어려운 문제가 아니고, 누적합을 사용하는 문제와 동일하다.

int main()
{
    cin >> N >> K;

    for (int i = 1; i <= N; ++i)
    {
        cin >> arr[i];
        DP[i] = DP[i - 1] + arr[i];
    }

    for (int i = K; i <= N; ++i)
    {
        Result = max(DP[i] - DP[i - K], Result);
    }

    cout << Result;
}