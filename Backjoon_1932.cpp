#include <iostream>
#include <vector>
using namespace std;

int N;

vector<vector<int>> arr(500, vector<int>());

int main()
{
    cin >> N;

    for (size_t i = 1; i <= N; ++i)
    {
        for (size_t j = 0; j < i; ++j)
        {
            int number = 0;
            cin >> number;
            arr[i - 1].push_back(number);
        }
    }

    for (int i = N - 2; i >= 0; --i)
    {
        for (size_t j = 0; j < arr[i].size(); ++j)
        {
            arr[i][j] = max(arr[i + 1][j] + arr[i][j], arr[i + 1][j + 1] + arr[i][j]);
        }
    }

    cout << arr[0][0];
}