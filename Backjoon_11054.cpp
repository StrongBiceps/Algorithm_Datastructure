#include <iostream>
using namespace std;

int N;
int DP[1000]= { 0 };
int DP2[1000] = { 0 };
int arr[1000] = { 0 };

int Result = 0;

//이 문제는 가장 긴 증가하는 부분 수열과 가장 긴 감소하는 부분수열을 더한 결과가 될 것이다.

//먼저 DP테이블로 가장 긴 증가하는 부분 수열에 대한 테이블을 채운다.

//그리고 나서 DP2 테이블로 가장 긴 감소하는 부분 수열에 대한 테이블을 채우는데, 수열을 거꾸로 순회한다.

//그러한 과정에서 DP와 DP2 테이블의 값을 더하고 -1을 한 값(중복된 기준 수) 중에서 가장 큰 것을 답으로 찾으면 된다.

int main()
{
    cin >> N;

    for (int i = 0; i < N; ++i)
    {
        cin >> arr[i];
    }

    for (int i = 0; i < N; ++i)
    {
        DP[i] = 1;
        for (int j = 0; j < i; ++j)
        {
            if (arr[i] > arr[j])
                DP[i] = max(DP[i], DP[j] + 1);
        }
    }

    for (int i = N-1; i>=0; --i)
    {
        DP2[i] = 1;
        for (int j = N-1; j > i; --j)
        {
            if (arr[i] > arr[j])
                DP2[i] = max(DP2[i], DP2[j] + 1);
        }
        
        Result = max(DP[i] + DP2[i] - 1, Result);
    }

    cout << Result;
}