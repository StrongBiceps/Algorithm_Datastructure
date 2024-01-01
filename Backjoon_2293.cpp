#include <iostream>
#include <vector>
using namespace std;

//동전이 2원일 때, 5원을 만드는 경우의 수는 DP[3]을 더한 값이다. 3원을 만드는 경우의 수에 2원을 더하면 되기 때문이다.

//만약 첫 번째 동전이 2원이면, DP[2]부터 초기화된다. DP[3]은 2원으로 만들 수 없다. 즉 DP[1]은 0이기 때문에 DP[3]도 0이 된다.

int main() {
	int n, k;
	cin >> n >> k;
	vector<int> arr(n);
	vector<int> dp(k + 1);
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	dp[0] = 1;	// 아무 동전도 선택하지 않은 경우
	for (int i = 0; i < n; i++) { //각 동전에 대해
		for (int j = arr[i]; j <= k; j++) {
			dp[j] += dp[j - arr[i]];
		}
	}

	cout << dp[k] << endl;
	return 0;
}