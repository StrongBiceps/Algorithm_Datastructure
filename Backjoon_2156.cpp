#include <iostream>
using namespace std;

int N;
int DP[10000] = { 0 };
int Value[10000] = { 0 };

int main()
{
    cin >> N;

    for (size_t i = 0; i < N; ++i)
    {
        cin >> Value[i];
    }
    
    //DP[2]까지 최대 값을 고정시킨다. 아래 경우밖에 없기 때문이다. (3번째 잔까지)

    //점화식의 항의 갯수가 계단문제에서 한 개가 늘었다. 즉 i-1까지의 경우, 현재 잔을 선택하지 않아도 되므로 
    //그 바로 전 잔까지 마셨을 경우까지 비교하면 된다.
    DP[0] = Value[0];
    DP[1] = Value[0] + Value[1];
    DP[2] = max(Value[0] + Value[1],max(Value[1]+Value[2], Value[0] + Value[2]));

    for (size_t i = 3; i < N; ++i)
    {
        DP[i] = max(DP[i-2]+Value[i],max(DP[i-3] + Value[i-1] + Value[i],DP[i-1]));
    }

    cout << DP[N - 1];
}