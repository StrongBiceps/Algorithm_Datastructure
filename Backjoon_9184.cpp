#include <iostream>
using namespace std;

//int DP[101][101][101];
//int a, b, c;
//bool    Done = false;
//
//int Function()
//{
//	int Result = 0;
//
//	for (size_t i = 0; i <= 100; ++i)
//	{
//		for (size_t j = 0; j <= 100; ++j)
//		{
//			for (size_t k = 0; k <= 100; ++k)
//			{
//				if (i <= 50 || j <= 50 || k <= 50)
//				{
//					DP[i][j][k] = 1;
//				}
//
//				else if (i > 70 || j > 70 || k > 70)
//				{
//					DP[i][j][k] = DP[70][70][70];
//				}
//
//
//				else if (i < j && j < k)
//				{
//					DP[i][j][k] = DP[i][j][k - 1] + DP[i][j - 1][k - 1] - DP[i][j - 1][k];
//				}
//
//				else
//					DP[i][j][k] = DP[i - 1][j][k] + DP[i - 1][j - 1][k] + DP[i - 1][j][k - 1] - DP[i - 1][j - 1][k - 1];
//
//				if (((i - 50) == a) && ((j - 50) == b) && ((k - 50) == c))
//				{
//					Result = DP[i][j][k];
//					Done = true;
//					break;
//				}
//			}
//
//			if (Done == true)
//				break;
//		}
//
//		if (Done == true)
//			break;
//	}
//
//	return Result;
//}
//
//int main()
//{
//	while (true)
//	{
//		cin >> a >> b >> c;
//
//		if (a == -1 && b == -1 && c == -1)
//		{
//			cout << "w(" << a << ", " << b << ", " << c << ") = " << Function() << '\n';
//			break;
//		}
//		else
//		{
//			cout << "w(" << a << ", " << b << ", " << c << ") = " << Function() << '\n';
//		}
//		Done = false;
//	}
//}

//오답 타뷸레이션 사용 -> 시간 초과
//하지만 전수 조사 방식가 필요한 상황에서는 빠를 것으로 보임

int memo[101][101][101] = { 0 };
int a, b, c;

int memoization(int _a,int _b,int _c)
{
	if (memo[_a][_b][_c] != 0)
		return memo[_a][_b][_c];

	if (_a <= 50 || _b <= 50 || _c <= 50)
		memo[_a][_b][_c] = 1;
	else if (_a > 70 || _b > 70 || _c > 70)
		memo[_a][_b][_c] = memoization(70, 70, 70);
	else if (_a < _b && _b < _c)
		memo[_a][_b][_c] = memoization(_a, _b, _c - 1) + memoization(_a, _b - 1, _c - 1) - memoization(_a, _b - 1, _c);
	else
		memo[_a][_b][_c] = memoization(_a - 1, _b, _c) + memoization(_a - 1, _b - 1, _c) + memoization(_a - 1, _b, _c - 1) - memoization(_a - 1, _b - 1, _c - 1);

	return memo[_a][_b][_c];
}

int main()
{
	while (true)
	{
		cin >> a >> b >> c;

		if (a == -1 && b == -1 && c == -1)
		{
			break;
		}
		else
		{
			cout << "w(" << a << ", " << b << ", " << c << ") = " << memoization(a+50, b+50, c+50) << '\n';
		}
	}
}