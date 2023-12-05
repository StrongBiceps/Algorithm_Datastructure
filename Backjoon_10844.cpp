#include <iostream>
using namespace std;

//이 문제도 하향식으로 접근해야 한다.

//먼저 테이블을 2차원으로 설정한다. 첫 번째 차원은 자릿수이다. 두 번째 차원은 해당 자릿수의 숫자이다.

//먼저 for문에서 첫 번째 자리의 숫자는 0이 될 수 없으므로 1부터 9까지 순회하며 memo 재귀함수를 호출한다.

//즉 첫 번째 자릿수에서 1~9까지의 경우의 수를 더한 것이 최종 결과가 된다.

//재귀가 깊어지면서 테이블에 값을 채워 나간다.

//예를 들어 N == 2일때 재귀의 시작은 memo(1,0)일 것이다. 그리고 memo 내부의 for문에서 memo(0,1) ,memo(2,1)이 호출될 것이고,

//각각의 경우에서 1이 반환될 것이다. 따라서 Table[0][1] = 2가 된다. 이러한 로직으로 반복한다.

//N == 2일때 최종 답안은 Table[0][1] ~ Table[0][9] 의 합산 결과가 될 것이다.

//또한 최적화의 원리는 다음과 같다.

//만약 memo(3,9)에서 memo(2,10)이 호출되고 for문이 돈다고 가정한다.

//그러면 memo(1,11)과 memo(3,11)이 호출될 것이다. 그러면 Table[11][1]과 Table[11][3]이 채워질 것이다.

//memo(4,10)이 호출되고 for문이 돌면 memo(3,11)과 memo(5,11)이 호출될 것이다. 그러면 Table[11][3]은 이미 계산된 값이므로

//이 경우에 대해서는 재귀를 하지 않아도 된다.

int N;
long long Result = 0;

long long Table[100][10] = { 0 };

long long memo(long long number, int cnt)
{
    if (cnt == N - 1)
    {
        return 1;
    }

    if (Table[cnt][number] != 0)
        return Table[cnt][number];

    for (int i = 0; i <= 9; ++i)
    {
        if (abs(number - i) == 1)
            Table[cnt][number] += memo(i, cnt+1) % 1000000000;
    }

    return Table[cnt][number];
}

int main()
{
    cin >> N;

    for (int i = 1; i <= 9; ++i)
    {
        Result += memo(i, 0);
    }


    cout << Result % 1000000000;
}