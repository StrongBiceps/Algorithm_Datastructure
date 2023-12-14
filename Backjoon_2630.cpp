#include <iostream>
using namespace std;

//���� ������ ����Ͽ� ������ �ذ��Ѵ�.

//���� �־��� size��ŭ �κ� ����� ��ȸ�ϸ鼭 �ٸ� ������ �ִ��� Ȯ���Ѵ�.

//�ٸ� ������ �����Ѵٸ�, �����Ѵ�.

//���� ��� ���Ҹ� ��ȸ�ߴµ� ������ ���� ���ٸ�, �ش��ϴ� ���� ���� ������ �ϳ� ������Ų��.

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