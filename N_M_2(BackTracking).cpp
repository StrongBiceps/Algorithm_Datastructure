#include <iostream>
using namespace std;

#define MAX 9
int n, m;
int arr[MAX] = { 0 };
bool visited[MAX] = { false };

void Dfs(int cnt)
{
    if (cnt == m)
    {
        for (size_t i = 0; i < m; ++i)
        {
            cout << arr[i] << " ";
        }
        cout << '\n';
    }
    for (size_t i = 1; i <= n; ++i)
    {
        if (!visited[i])
        {
            if (cnt > 0)
            {
                if (arr[cnt - 1] > i)
                    continue;
            }

            arr[cnt] = i;
            visited[i] = true;
            Dfs(cnt + 1);
            visited[i] = false;
        }
    }
}

int main()
{
    cin >> n >> m;

    Dfs(0);
}