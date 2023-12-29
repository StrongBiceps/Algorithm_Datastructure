#include <iostream>
using namespace std;

//2740번과 1629번을 참고하면 풀 수 있는 문제이다.

long long Mat[5][5] = { 0 };
long long Result[5][5] = { 0 };
long long Temp[5][5] = { 0 };
int N, M;

void Multi(long long _Mat1[5][5], long long _Mat2[5][5])
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            Temp[i][j] = 0;
            for (int k = 0; k < N; ++k)
            {
                Temp[i][j] += _Mat1[i][k] * _Mat2[k][j];
            }
            Temp[i][j] %= 1000;
        }
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            _Mat1[i][j] = Temp[i][j];
        }
    }
}

int main()
{
    cin >> N >> M;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> Mat[i][j];
        }
        Result[i][i] = 1;
    }

    while (M > 0)
    {
        if (M % 2 == 1)
        {
            Multi(Result, Mat);
        }
        Multi(Mat, Mat);
        M /= 2;
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << Result[i][j] << " ";
        }
        cout << '\n';
    }
}