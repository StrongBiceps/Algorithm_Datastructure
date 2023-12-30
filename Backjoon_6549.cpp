#include<iostream>
#include<algorithm>
#include<memory.h>
#include<vector>
using namespace std;

int N;
long long ans, h[100002];
vector<int> v;

int main()
{

	while (true)
	{
		cin >> N;

		if (N == 0) break;

		for (int i = 1; i <= N; i++) cin >> h[i];

		v.push_back(0);
		for (int i = 1; i <= N + 1; i++)
		{
			while (!v.empty() && h[v.back()] > h[i])
			{
				int check = v.back();
				v.pop_back();
				ans = max(ans, h[check] * (i - v.back() - 1));
			}
			v.push_back(i);
		}

		cout << ans << '\n';

		// ÃÊ±âÈ­
		v.clear();
		ans = 0;
		memset(h, 0, 100000);
	}

}