#include <iostream>
using namespace std;

int N;
int Table[1000001] = { 0 };

int Result = 0;

//memoization(하향식)을 이용한 최적화 예제이다.
//먼저 Table의 값은 n부터 1까지 가는 최단 연산 횟수이다. 즉 n이 3이라면 3에서 1로 가는 경우는 2로 먼저 가는 경우와 바로 1로 가는 경우가 된다.
//그 중에서 가장 작은 값이 Tqble[3]의 값이 된다. Table의 값은 memo에서 Return하는 값에 1을 더한다. 연산 횟수를 늘리는 작업이다.
//또한 중복된 값에 대한 memo가 호출될 때는 Table의 값을 리턴하여 더 이상 재귀가 깊어지지 않게 한다. 
//예를 들어 Table[3]의 값은 4에서도 호출될 수 있고, Table[6]에서도 호출될 수 있다. 따라서 중복된 값은 바로 테이블에서 가져온다.
//이렇게 각 숫자에서 1로 가는 최소 연산 경우의 수를 테이블에 작성하면서 하향식으로 진행한 후 Table[N]의 값을 리턴하면 된다.

int memo(int n)
{
    if (n == 1)
    {
        return 0;
    }

    if (Table[n] != 0)
        return Table[n];

    int a = 99, b = 99, c = 99;

    if (n % 3 == 0)
    {
        a = memo(n / 3)+1;
    }

    if (n % 2 == 0)
    {
        b = memo(n / 2)+1;
    }

    c = memo(n - 1)+1;

    Table[n] += min(a, min(b, c));

    return Table[n];
}

int main()
{
    cin >> N;

    memo(N);

    cout << Table[N];
}