#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

int n, bead, x, weight[31];
bool dp[31][15001];

void solve(int i, int w)
{
	if (i > n || dp[i][w]) return;
	dp[i][w] = true;

	//구슬이 없는 저울에 추를 올리는 경우이다. 이 경우는 구슬쪽에 추를 올리지 않고 무게를 맞추는 경우이다.
	solve(i + 1, w + weight[i]);

	//구슬이 있는 쪽에 추를 올리는 경우이다.
	//예를 들어 무게 추가 1,4 가 있고 3을 알아본다고 하자, 그럼 DP[0][1]에서 DP[1][1-4 = 3] 두 번째 재귀가 true로 설정될 것이다.
	//즉 4g과 1g의 차이는 곧 3g인데, 1+3 = 4로 3g인지를 알아볼 수 있다. 즉, 추들의 차이가 구슬의 무게가 될 수 있다.
	solve(i + 1, abs(w - weight[i]));

	//추를 올리지 않고 무게를 측정하는 방법이다. 예를 들어 구슬의 무게가 3이고, 추가 1,2,6이라고 하자, 
	//그러면 DP[1][3] == true일 때, 추를 계속 올리지 않고 재귀가 깊어져 기저 조건(i>n)에서 return하게 되면,
	//추를 1,2만 올리면 3을 만드는 경우가 된다.
	solve(i + 1, w);
}

int main()
{
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		cin >> weight[i];
	}
	solve(0, 0);

	cin >> bead;

	for (int i = 0; i < bead; i++)
	{
		cin >> x;

		if (x > 15000) cout << "N ";
		else if (dp[n][x]) cout << "Y ";
		else cout << "N ";
	}
}