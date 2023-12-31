#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define INF 1000000000

int T, K;
int sum[501], file[501], dp[501][501];

int main()
{
	cin >> T;

	while (T--)
	{
		cin >> K;
		for (int i = 1; i <= K; i++)
		{
			cin >> file[i];
			sum[i] = sum[i - 1] + file[i];
		}

		for (int i = 1; i <= K; i++)
		{
			for (int j = 1; j <= K - i; j++)
			{
				dp[j][i + j] = INF;
				for (int k = j; k < i + j; k++)
				{
					//sum[i+j] - sum[j-1]은 구간 내의 파일을 모두 합쳤을 때의 비용이다.

					//4~11 구간을 두 구간으로 나누어서 각 구간의 최소비용을 구하고, 두 구간을 더하는

					//비용인 sum[i+j] - sum[j-1]을 더하는 것이다.
					dp[j][i + j] = min(dp[j][i + j], dp[j][k] + dp[k + 1][i + j] + sum[i + j] - sum[j - 1]);
				}
			}
		}

		cout << dp[1][K] << endl;

	}

}