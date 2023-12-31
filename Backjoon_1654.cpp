#include <iostream>
#include <algorithm>

using namespace std;

unsigned int ans;
unsigned int N, K;
unsigned int list[10000];

/*
* 4개의 랜선을 가지고 있고, 11개로 만들 것이다. 최대 길이는?

위에서의 관찰대로라면, 문제의 답은 1~802중에 있습니다.

우리는 left를 1로 right를 802로 설정하여, mid를 계산한 후, mid가 정답인지를 고려하여, left, right를 적절히 옮길 수 있습니다.

 

그렇다면 mid가 정답인지는 어떻게 고려할까요?

바로, 802, 743, 457, 539를 mid로 나누어, 몫의 합이 11보다 크거나 같은지 검사하면됩니다.

주의할 점은 mid가 11보다 크거나 같다고, 바로 최대값이 나오지 않을 수 있습니다.

따라서,

mid가 11보다 크거나 같다면, left를 mid보다 한 칸 다음으로 옮겨, 가능한지 검사하고 (더 긴 길이로도 11개를 만들 수 있는지?)

mid가 11보다 작다면, right를 mid보다 한 칸 전으로 옮겨, 가능한지 검사하면 됩니다. (더 짧은 길이라면 11개를 만들 수 있는지?)

 

위의 mid가 정답인지 고려하는 것은, 이분 탐색의 핵심이 되는 부분입니다.

처음에는 당연히 접근이 어렵겠지만, 고민과 연습으로 한 단계 더 나아가시길 바랍니다.

 

이렇게 검사하다 보면, left가 right보다 커지는 순간이 올텐데, 이때 검사를 중단하고 답을 출력해주면 됩니다.
*/

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);

	cin >> K >> N;

	unsigned int maxi = 0;

	for (int i = 0; i < K; i++)
	{
		cin >> list[i];
		maxi = max(maxi, list[i]);
	}

	unsigned int left = 1, right = maxi, mid;

	while (left <= right)
	{
		// mid 연산
		mid = (left + right) / 2;

		// 몫의 합을 저장하는 변수
		unsigned int now = 0;

		for (int i = 0; i < K; i++)
		{
			//mid로 나눈 몫을 저장
			now += list[i] / mid;
		}

		if (now >= N)
		{
			// 현재 mid로 나눈 값이 N보다 크거나 같다면,
			// left를 움직여 길이가 더 긴 경우는 가능한지 검사
			left = mid + 1;

			// N개를 만들 수 있을 때, 답을 더 큰 값으로 계속 갱신
			ans = max(ans, mid);
		}
		else
		{
			// 현재 mid로 나눈 값이 N보다 작다면,
			// right 움직여 길이가 더 짧은 경우는 가능한지 검사
			right = mid - 1;
		}
	}

	cout << ans << '\n';
}