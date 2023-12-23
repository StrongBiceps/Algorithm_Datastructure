#include <iostream>
#include <algorithm>
using namespace std;

int N;
int Total = 0;
int Result = 0;

int arr[10] = { 0 };

//�׸��� �˰����� �̿��Ͽ� ���� ���� ū �������� ���� �ȴ�.

//���� ���� ū �������� ���鼭 ������ ������ �۾����� ���� �������� �̵��Ѵ�.

//���� ���� ���� ������ ������ 1�̹Ƿ� �ݵ�� k���� ���� �� �ִ�.

//���� ������������ �迭�� ������ �ݵ�� 2�� �̻� Ŀ���Ƿ� ������ ���� ū �ͺ��� ���ʴ�� �� ������ ���� ���� �ּ��� 

//�ݺ����̴�.

void Recur(long long value, int index)
{
    if (value == 0)
        return;

    if (value < arr[index])
        Recur(value, index + 1);
    else
    {
        ++Result;
        Recur(value - arr[index], index);
    }
}

int main()
{
    cin >> N;
    cin >> Total;

    for (int i = 0; i < N; ++i)
    {
        cin >> arr[i];
    }

    sort(arr, arr + N, greater<int>());

    Recur(Total, 0);

    cout << Result;
}

//��� ���
int arr[10];

int main() {
    int n, k, ans = 0;
    int sum = 0;

    cin >> n >> k;

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    for (int i = n - 1; i >= 1; i--) {
        int cnt = (k - sum) / arr[i];

        ans += cnt;
        sum += cnt * arr[i];
    }

    //1��° ������ ������ 1��¥���̴�. ���� ��

    //�ݺ������� �� ��° �������� ������ ����ؼ�

    //���ݱ��� ������� �� ���ݰ� ��ǥ ������ ����

    //1������ ����� ����̴�. ���� �� ������ ���ؾ�

    //�Ѵ�. ���� k-sum�� 0�̸� 1�� ������ ������ ����

    //���� �̹� ��ǥ ������ �޼��ߴٴ� ���̹Ƿ�

    //0�� ������ ���̴�.
    ans += k - sum;

    cout << ans;

    return 0;
}