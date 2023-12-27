#include <iostream>
using namespace std;

int N;

int One = 0;
int Zero = 0;
int Minus = 0;

int    arr[2200][2200] = { 0 };

void Back(int R, int C, int size)
{
    bool Differ = false;

    for (int i = R; i < R + size; ++i)
    {
        for (int j = C; j < C + size; ++j)
        {
            if (arr[i][j] != arr[R][C])
            {
                Differ = true;
                break;
            }
        }
    }

    if (Differ == true)
    {
        Back(R, C, size / 3);
        Back(R + size / 3, C, size / 3);
        Back(R + size / 3 + size / 3, C, size / 3);
        Back(R, C + size / 3, size / 3);
        Back(R, C + size / 3 + size / 3, size / 3);
        Back(R + size / 3, C + size / 3, size / 3);
        Back(R + size / 3 + size / 3, C + size / 3 + size / 3, size / 3);
        Back(R + size / 3, C + size / 3 + size / 3, size / 3);
        Back(R + size / 3 + size / 3, C + size / 3, size / 3);
    }
    else
    {
        if (arr[R][C] == -1)
        {
            ++Minus;
        }
        else if (arr[R][C] == 0)
        {
            ++Zero;
        }
        else
        {
            ++One;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);


    cin >> N;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cin >> arr[i][j];
        }
    }

    Back(0, 0, N);

    cout << Minus << '\n';
    cout << Zero << '\n';
    cout << One;

}