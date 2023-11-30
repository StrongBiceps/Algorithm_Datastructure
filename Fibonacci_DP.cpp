#include <iostream>
using namespace std;

int Count1 = 1;
int Count2 = 0;

int Fibonacci(int i)
{

    if (i == 2 || i ==1)
        return 1;
        
    else
    {
        ++Count1;
        return (Fibonacci(i - 1) + Fibonacci(i - 2));
    }
}

int main()
{
    int N;
    cin >> N;

    Fibonacci(N);

    int F[40];

    F[1] = 1;
    F[2] = 1;

    for (size_t i = 3; i <= N; ++i)
    {
        ++Count2;
        F[i] = F[i - 1] + F[i - 2];
    }

    cout << Count1<<" "<<Count2;
}