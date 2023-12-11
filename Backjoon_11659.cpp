#include <iostream>
using namespace std;

//구간합 문제 또한 DP 문제라고 할 수 있다. 먼저 모든 구간에서의 합을 DP로 구한다음, 답을 구할 때는 상수시간에 계산할 수 있도록 한다.


int arr[100000] = { 0 };
int DP[100000] = { 0 };
int N;
int M;
pair<int, int> Temp[100000];

int Result = 0;


int main()
{
    cin >> N >> M;
    for (int i = 0; i < N; ++i)
    {
        cin >> arr[i];
    }

    for (int i = 0; i < M; ++i)
    {
        cin >> Temp[i].first >> Temp[i].second;
    }

    DP[0] = arr[0];

    for (int i = 1; i < N; ++i)
    {
        DP[i] = DP[i - 1] + arr[i];
    }

    for (int i = 0; i < M; ++i)
    {
        cout << DP[Temp[i].second-1] - DP[Temp[i].first-2]<<'\n';
    }
}