#include <iostream>
using namespace std;

int N;
int DP[1000]= { 0 };
int DP2[1000] = { 0 };
int arr[1000] = { 0 };

int Result = 0;

//�� ������ ���� �� �����ϴ� �κ� ������ ���� �� �����ϴ� �κм����� ���� ����� �� ���̴�.

//���� DP���̺�� ���� �� �����ϴ� �κ� ������ ���� ���̺��� ä���.

//�׸��� ���� DP2 ���̺�� ���� �� �����ϴ� �κ� ������ ���� ���̺��� ä��µ�, ������ �Ųٷ� ��ȸ�Ѵ�.

//�׷��� �������� DP�� DP2 ���̺��� ���� ���ϰ� -1�� �� ��(�ߺ��� ���� ��) �߿��� ���� ū ���� ������ ã���� �ȴ�.

int main()
{
    cin >> N;

    for (int i = 0; i < N; ++i)
    {
        cin >> arr[i];
    }

    for (int i = 0; i < N; ++i)
    {
        DP[i] = 1;
        for (int j = 0; j < i; ++j)
        {
            if (arr[i] > arr[j])
                DP[i] = max(DP[i], DP[j] + 1);
        }
    }

    for (int i = N-1; i>=0; --i)
    {
        DP2[i] = 1;
        for (int j = N-1; j > i; --j)
        {
            if (arr[i] > arr[j])
                DP2[i] = max(DP2[i], DP2[j] + 1);
        }
        
        Result = max(DP[i] + DP2[i] - 1, Result);
    }

    cout << Result;
}