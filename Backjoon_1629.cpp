#include <iostream>
using namespace std;

long long A, B, C;

long long power(long long b)
{
    if (b == 0)
        return 1;

    if (b == 1)
    {
        return A % C;
    }

    long long D = power(b / 2) % C;

    if (b % 2 == 0)
        return D * D % C;
    else
        return D * D % C * A % C;
}

int main()
{

    cin >> A >> B >> C;

    cout << power(B);
}