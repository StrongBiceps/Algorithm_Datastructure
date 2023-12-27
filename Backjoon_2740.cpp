#include <iostream>
using namespace std;

int A[100][100] = { 0 };
int B[100][100] = { 0 };
int N, M, K;

int Result[100][100] = { 0 };

//분할 정복이 아니라 단순한 반복문의 느낌이다.
int main()
{
    cin >> N >> M;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            cin >> A[i][j];
        }
    }

    cin >> M >> K;

    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < K; ++j)
        {
            cin >> B[i][j];
        }
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < K; ++j)
        {
            for (int l = 0; l < M; ++l)
            {
                Result[i][j] += A[i][l] * B[l][i];
            }
            cout << Result[i][j] << " ";
        }
        cout << '\n';
    }
}