#include <iostream>
#include <vector>
using namespace std;

//������ 2���� ��, 5���� ����� ����� ���� DP[3]�� ���� ���̴�. 3���� ����� ����� ���� 2���� ���ϸ� �Ǳ� �����̴�.

//���� ù ��° ������ 2���̸�, DP[2]���� �ʱ�ȭ�ȴ�. DP[3]�� 2������ ���� �� ����. �� DP[1]�� 0�̱� ������ DP[3]�� 0�� �ȴ�.

int main() {
	int n, k;
	cin >> n >> k;
	vector<int> arr(n);
	vector<int> dp(k + 1);
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	dp[0] = 1;	// �ƹ� ������ �������� ���� ���
	for (int i = 0; i < n; i++) { //�� ������ ����
		for (int j = arr[i]; j <= k; j++) {
			dp[j] += dp[j - arr[i]];
		}
	}

	cout << dp[k] << endl;
	return 0;
}