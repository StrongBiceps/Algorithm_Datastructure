#include <iostream>
#include <climits>
using namespace std;

int DP[100001] = { 0 };
int arr[100001] = { 0 };
int N;
int K;
int Result = INT_MIN;

//���� ����� ������ �ƴϰ�, �������� ����ϴ� ������ �����ϴ�.

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