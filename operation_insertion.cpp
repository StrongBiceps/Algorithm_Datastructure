#include <iostream>
using namespace std;

int N;
int Max = -1000000001;
int Min = 1000000001;
int arr[11] = { 0 };
int oper[4] = { 0 };

void sum(int index, int result)
{
    if (index == N)
    {
        if (Max < result)
            Max = result;
        if (Min > result)
            Min = result;

        return;
    }
    for (size_t i = 0; i < 4; ++i)
    {
        if (oper[i] > 0)
        {
            --oper[i];

            if (i == 0)
                sum(index + 1, result + arr[index]);
            else if (i == 1)
                sum(index + 1, result - arr[index]);
            else if (i == 2)
                sum(index + 1, result * arr[index]);
            else
                sum(index + 1, result / arr[index]);
            ++oper[i];
        }
    }
}
int main()
{
    cin >> N;

    for (size_t i = 0; i < N; ++i)
    {
        cin >> arr[i];
    }

    for (size_t i = 0; i < 4; ++i)
    {
        cin >> oper[i];
    }
    sum(1, arr[0]);

    cout << Max << '\n';
    cout << Min;
}