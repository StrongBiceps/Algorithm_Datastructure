#include <iostream>
using namespace std;

#define MAX 9

int arr[MAX] = { 0 };
int n, m;
void Dfs(int cnt)
{
    if (cnt == m)
    {
        for (size_t i = 0; i < m; ++i)
        {
            cout << arr[i] << " ";
        }
        cout << '\n';

        return;
    }
    for (size_t i = 1; i <= n; ++i)
    {
        arr[cnt] = i;
        Dfs(cnt + 1);
    }
}

int main()
{
    cin >> n >> m;
    Dfs(0);
}