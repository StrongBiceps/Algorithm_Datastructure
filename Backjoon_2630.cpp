#include <iostream>
using namespace std;

//분할 정복을 사용하여 문제를 해결한다.

//먼저 주어진 size만큼 부분 행렬을 순회하면서 다른 색깔이 있는지 확인한다.

//다른 색깔이 존재한다면, 분할한다.

//만약 모든 원소를 순회했는데 색깔이 전부 같다면, 해당하는 색깔에 대한 갯수를 하나 증가시킨다.

int N;
int arr[129][129] = { 0 };

bool Blue = true;
bool White = false;

int Blue_Count = 0;
int White_Count = 0;

void Back(int R, int C, int size)
{
    bool Blue_Temp = false;
    bool White_Temp = false;

    for (int i = R; i < R + size; ++i)
    {
        for (int j = C; j < C + size; ++j)
        {
            if (arr[i][j] == Blue)
            {
                Blue_Temp = true;
                if (White_Temp == true)
                {
                    Back(R, C, size / 2);
                    Back(R + size / 2, C, size / 2);
                    Back(R, C + size / 2, size / 2);
                    Back(R + size / 2, C + size / 2, size / 2);
                    return;
                }

            }

            if (arr[i][j] == White)
            {
                White_Temp = true;
                if (Blue_Temp == true)
                {
                    Back(R, C, size / 2);
                    Back(R + size / 2, C, size / 2);
                    Back(R, C + size / 2, size / 2);
                    Back(R + size / 2, C + size / 2, size / 2);

                    return;
                }
            }
        }
    }

    if (White_Temp == true)
    {
        ++White_Count;
    }

    if (Blue_Temp == true)
    {
        ++Blue_Count;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;

    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            cin >> arr[i][j];
        }
    }

    Back(1, 1, N);

    cout << White_Count << '\n';
    cout << Blue_Count;
}