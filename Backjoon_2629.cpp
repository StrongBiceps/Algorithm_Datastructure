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

	//������ ���� ���￡ �߸� �ø��� ����̴�. �� ���� �����ʿ� �߸� �ø��� �ʰ� ���Ը� ���ߴ� ����̴�.
	solve(i + 1, w + weight[i]);

	//������ �ִ� �ʿ� �߸� �ø��� ����̴�.
	//���� ��� ���� �߰� 1,4 �� �ְ� 3�� �˾ƺ��ٰ� ����, �׷� DP[0][1]���� DP[1][1-4 = 3] �� ��° ��Ͱ� true�� ������ ���̴�.
	//�� 4g�� 1g�� ���̴� �� 3g�ε�, 1+3 = 4�� 3g������ �˾ƺ� �� �ִ�. ��, �ߵ��� ���̰� ������ ���԰� �� �� �ִ�.
	solve(i + 1, abs(w - weight[i]));

	//�߸� �ø��� �ʰ� ���Ը� �����ϴ� ����̴�. ���� ��� ������ ���԰� 3�̰�, �߰� 1,2,6�̶�� ����, 
	//�׷��� DP[1][3] == true�� ��, �߸� ��� �ø��� �ʰ� ��Ͱ� ����� ���� ����(i>n)���� return�ϰ� �Ǹ�,
	//�߸� 1,2�� �ø��� 3�� ����� ��찡 �ȴ�.
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