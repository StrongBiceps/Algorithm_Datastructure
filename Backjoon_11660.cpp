#include <iostream>
using namespace std;

// ��� ������ �������� ���ϴ� ����̴�. ��� �����̱� ������ �ߺ��ǰ� �������� ���̳� ������ ���� ��������� �Ѵ�.

long long DP[1025][1025] = { 0 };
int N, M;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;
    int number = 0;

    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            cin >> number;
            DP[i][j] = DP[i - 1][j] + DP[i][j - 1] - DP[i - 1][j - 1] + number;
        }
    }

    pair<int, int> str;
    pair<int, int> end;

    for (int i = 0; i < M; ++i)
    {
        cin >> str.first >> str.second;
        cin >> end.first >> end.second;

        cout << DP[end.first][end.second] - DP[str.first - 1][end.second]
            - DP[end.first][str.second - 1] +
            DP[str.first - 1][str.second - 1] << '\n';
    }
}