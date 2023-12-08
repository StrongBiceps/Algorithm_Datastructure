#include <iostream>
#include <string>
using namespace std;

int DP[1001][1001] = { 0 };

string A;
string B;


//DP 테이블의 차원은 문자열의 길이보다 1 큰 것으로 설정한다. 이유는 문자열이 존재하지 않는 경우를 생각해서 기저 조건인
//DP[0][?] , DP[?][0] 의 값을 0으로 만들기 위해서이다. 또한 이전 값을 사용하는 DP의 특성을 고려하여 기저 조건을 정한 것이다.
//DP[i][j]의 값은 i,j원소까지 비교했을 때 최대 공통 부분 문자열의 길이이다. A[i-1][j-1]로 비교하는 이유는 
//문자열의 인덱스가 0부터 시작이고, DP는 1부터 의미있는 값의 시작이기 때문이다.

int main()
{
    cin >> A >> B;

    for (int i = 0; i <= A.size(); ++i)
    {
        for (int j = 0; j <= B.size(); ++j)
        {
            if (i == 0 || j == 0)
                DP[i][j] = 0;
            else if (A[i-1] == B[j-1])
                DP[i][j] = DP[i - 1][j - 1] + 1;
            else
                DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
        }
    }

    cout << DP[A.size()][B.size()];
}