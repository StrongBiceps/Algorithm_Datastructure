#include <iostream>
#include <vector>
using namespace std;

//모든 알파벳의 빈도를 DP에 저장하고, 구간합을 구하는 것이 전부이다.

string A;
string B;
int DP[26][200002] = { 0 };
int N;

int main()
{
    //이 두 줄 안붙이면 50점이다.... 나머지 로직은 전혀 문제가 없다.
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

    cin >> A;
    cin >> N;

   for (int i = 0; i <= 25; ++i)
    {
        for (int j = 1; j <= A.size(); ++j)
        {
            if (i + 'a' == (int)A[j-1])
                DP[i][j] = DP[i][j - 1]+1;
            else
                DP[i][j] = DP[i][j - 1];
        }
    }

    for (int i = 0; i < N; ++i)
    {
        int a, b;
        char Character;
        cin >> Character;
        cin >> a >> b;
        if(a == 0)
            //문제의 입력에서 요구하는 문자열의 index는 0부터 시작인데 DP값은 1부터 시작이므로 두 번째 차원을 +1해서 계산해야 함.
            cout << DP[Character - 'a'][b+1]<<'\n';
        else
            cout << DP[Character - 'a'][b+1] - DP[Character - 'a'][a]<<'\n';
    }
}