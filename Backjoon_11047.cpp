#include <iostream>
#include <algorithm>
using namespace std;

int N;
int Total = 0;
int Result = 0;

int arr[10] = { 0 };

//그리디 알고리즘을 이용하여 가장 값이 큰 동전부터 빼면 된다.

//가장 값이 큰 동전부터 빼면서 동전의 값보다 작아지면 다음 동전으로 이동한다.

//또한 가장 작은 동전은 무조건 1이므로 반드시 k원을 맞출 수 있다.

//또한 오름차순으로 배열된 수열은 반드시 2배 이상씩 커지므로 무조건 가장 큰 것부터 차례대로 빼 나가는 것이 가장 최소의 

//반복수이다.

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

//모범 답안
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

    //1번째 동전은 무조건 1원짜리이다. 따라서 위

    //반복문에서 두 번째 동전까지 갯수를 계산해서

    //지금까지 만들어진 총 가격과 목표 가격을 뺴면

    //1원으로 만드는 경우이다. 따라서 그 갯수를 더해야

    //한다. 만약 k-sum이 0이면 1원 이후의 동전의 구성

    //으로 이미 목표 가격을 달성했다는 것이므로

    //0이 더해질 것이다.
    ans += k - sum;

    cout << ans;

    return 0;
}