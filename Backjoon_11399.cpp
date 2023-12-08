#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;

int Result = 0;

//�� ������ ���ð��� �ƴ϶� �� �۾��ð��̹Ƿ� ���ð� + �ڽ��� �۾��ð��� ����ؾ� �Ѵ�.

int main()
{
    cin >> N;

    vector<int>    Time(N, 0);
    vector<int>    Wait(N + 1, 0);
    for (int i = 0; i < N; ++i)
    {
        cin >> Time[i];
    }
    sort(Time.begin(), Time.end());

    Wait[0] = 0;
    Result += Time[0];

    for (int i = 1; i < N; ++i)
    {
        Wait[i] = Wait[i - 1] + Time[i - 1];
        Result += Wait[i]+Time[i];
    }

    cout << Result;
}