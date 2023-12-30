#include <iostream>
#include <map>
using namespace std;

#define MOD	1000000007LL

map<long long, long long> Table;
long long N;

long long Fib(long long n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;
	if (n == 2)	return 1;

	//이미 테이블에 Fib(n)이 기록되었다면,
	if (Table.count(n) > 0)
		return Table[n];

	if (n % 2 == 0)
	{
		long long m = n / 2;
		long long Temp1 = Fib(m - 1);
		long long Temp2 = Fib(m);
		Table[n] = ((2LL * Temp1 + Temp2) * Temp2) % MOD;
		return Table[n];
	}
	long long m = (n + 1) / 2;
	long long Temp1 = Fib(m);
	long long Temp2 = Fib(m - 1);
	Table[n] = (Temp1*Temp1 + Temp2 * Temp2) % MOD;
	return Table[n];
}

int main()
{
	cin >> N;
	cout << Fib(N);
}