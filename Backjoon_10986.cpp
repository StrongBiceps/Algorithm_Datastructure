//모듈로 연산의 특성을 이용한 문제이다.

//Area(i+1,j) = Psum(j) - Psum(i) 임은 자명하다.

//   (Psum(j) - Psum(i)) % M = 0 일 때는,

//Psum(j) % M = Psum(i) % M 이 성립한다.

//따라서 Mod 배열을 사용하여 M으로 나누었을 때 나머지가 같은 값들 끼리 묶어서 조합을 사용하여 경우의 수를 탐색한다.

//즉 나누어서 1의 나머지가 나오는 수가 10개 있다고 가정하자, 즉 Mod[1] = 10이 될 것이다. 그러면 이 10개의 Index중에서 2개를

//골라야 (i,j)의 경우를 생각할 수 있다. 따라서 10개 중에서 2개를 선택하는 조합(nCr)을 사용해서 계산하면 된다.

//그리고 마지막으로 Mod[0]에 대해서 다시 한 번 생각해봐야 하는데, 이는 나누어 떨어지는 것들의 모음이다. 마지막에

//Mod[0]을 더해주는 이유는 구간합이 아닌 숫자 하나가 M으로 나누어 떨어지는 경우를 생각한 것이다. 즉, Mod[0]에 들어간 수들은

//모두 M으로 나누어 떨어진다. 즉, 이들의 조합을 사용해서 경우의 수를 구하고, 각자 혼자 존재하는 경우의 수도 함께 더해야 한다.

#include <iostream>
using namespace std;

long long Mod[1001] = { 0 };
int N, M;
long long Total = 0;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    long long number = { 0 };
    long long Result = 0;

    for (int i = 0; i < N; ++i)
    {
        cin >> number;
        Result += number;
        ++Mod[Result % M];
    }

    for (int i = 0; i < M; ++i)
    {
        Total += (Mod[i] * (Mod[i] - 1)) / 2;
    }
    Total += Mod[0];

    cout << Total;
}