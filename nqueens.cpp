#include <iostream>
#define MAX 15
using namespace std;

int col[MAX];
int N, total = 0;

//지금까지 배치한 열까지 검사를 진행한다 level 이후의 열은 배치하지도 않았으므로 검사할 이유가 없다.
bool check(int level)
{
    for (int i = 0; i < level; i++)
        if (col[i] == col[level] || abs(col[level] - col[i]) == level - i)// 대각선이거나 같은 라인
            return false;
    //col[i]가 의미하는 것이 X좌표, i가 의미하는것이 Y좌표이므로 차이가 일정하다면 대각선에 있다고 볼 수 있다.
    return true;
}

void nqueen(int x)
{
    if (x == N)
        total++;
    else
    {
        for (int i = 0; i < N; i++)
        {
            col[x] = i; // 해당 위치에 퀸을 배치
            if (check(x)) // 유효하다면 다음행의 퀸 배치, 유효하지않다면 다른 위치로 퀸 배치 변경
                nqueen(x + 1);
        }
    }
}
int main() {
    cin >> N;
    nqueen(0);
    cout << total;
}

/*백트래킹 특성은 재귀를 잘 생각해보면 이해할 수 있다. 각 열에 어떤 행에 퀸을 배치할 지 결정한 다음 재귀를 깊게 들어간다.
기저 조건에 걸려서 빠져나왔다면 바로 이전 재귀에서 다음 위치를 탐색할 것이다. 이런 식으로 재귀의 가지가 넓어져 나간다.*/