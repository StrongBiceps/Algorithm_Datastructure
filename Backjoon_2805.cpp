#include <iostream>
#include <algorithm>

using namespace std;

unsigned int ans;
long long N, M;
long long list[1000001] = { 0 };

//1654���� ������ ������ �����̴�.

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);

	cin >> N >> M;

	long long maxi = 0;

	for (int i = 0; i < N; i++)
	{
		cin >> list[i];
		maxi = max(maxi, list[i]);
	}

	unsigned int left = 1, right = maxi, mid;

	while (left <= right)
	{
		// mid ����
		mid = (left + right) / 2;

		// ���� ���� �����ϴ� ����
		long long now = 0;

		for (int i = 0; i < N; i++)
		{
			//mid�� ���� ���� ����
			auto Delta = list[i] - mid;

			if (Delta < 0)
				Delta = 0;

			now += Delta;
		}

		if (now >= M)
		{
			// ���� mid�� ���� ���� N���� ũ�ų� ���ٸ�,
			// left�� ������ ���̰� �� �� ���� �������� �˻�
			left = mid + 1;

			// N���� ���� �� ���� ��, ���� �� ū ������ ��� ����
			ans = max(ans, mid);
		}
		else
		{
			// ���� mid�� ���� ���� N���� �۴ٸ�,
			// right ������ ���̰� �� ª�� ���� �������� �˻�
			right = mid - 1;
		}
	}

	cout << ans << '\n';
}