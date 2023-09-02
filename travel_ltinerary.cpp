#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

//32비트로 표현할 수 있는 범위를 벗어날 수 있으므로 결과 저장을 위해 long long형을 LL로 선언
typedef long long LL;

//MOD연산이 적용되었다면 마지막 출력 값에서 원래의 값을 다시 얻는 것은 일반적으로 불가능하다.왜냐하면 모듈러 연산을
//수행하면 원래의 정보 일부가 손실되기 때문이다.
//예를 들어, 만약 10을 7로 나누면 나머지는 3이 된다.
//그런데 3이라는 값만 가지고 원래의 숫자가 10인지, 아니면 다른 어떤 숫자(예: 17, 24 등)인지 알아낼 수 없다.이것은 모듈러 연산의 특성으로, 
//나머지만으로는 원래의 값을 복구할 수 없다.
//따라서 문제에서 요구하는 것이 모듈러 연산된 결과를 출력하는 것이라면,
//그 결과값을 통해 원래의 값을 정확하게 복구하는 것은 불가능하다.

const LL MOD =  1000000007;

//재귀 반복식을 구현하기 위해 먼저 distance배열을 역순으로 변환한다. 이로써 목적지 위치부터 계산을 수행할 수 있다.
//여기에는 여러 가지 이유가 있지만 가장 주된 이유는 현재 상태의 결과로부터 미래 상태를 계산하는 것과는 반대로 이전 상태의 결과
//를 이용하여 현재 상태를 계산하기 위함이다. 의사 코드에 기술한 로직도 올바른 결과를 생성할 수 있지만, 보통 이전 상태 해답을 이용하여
//중간 단계 상태를 구하는 상향식 로직을 사용하는 것이 바람직하다.
LL TravelItinerary(int n, vector<int> distance)
{
	//거리는 지점 ID+distance가 n을 넘어가지 않게 주어진다.
	reverse(distance.begin(), distance.end());

	vector<LL> DP(n + 1, 0);

	vector<LL> sums(n + 2, 0);

	DP[0] = sums[1] = 1;

	for (int i = 1; i <= n; i++)
	{
		cout << endl;
		cout << i << "번째 반복-> "<<n+1-i<<"번 지점에서 목적지까지 계산" << endl;

		int dist = distance[i - 1];
		cout << "dist["<<i-1<<"]: " << dist << endl;

		//i에서 목적지까지 가는 경로의 수에 i-dist 지점에서 목적지까지 가는 경로의 수를 뺀다.
		LL sum = sums[i] - sums[i - dist];
		cout << "sum: sums[" << i << "] - sums[" << i - dist << "] : " << sum << endl;
		cout << n-i+1 << "번 지점에서 " << n+1-(i - dist) << "번 지점까지의 경우의 수: "<<sum << endl;

		DP[i] = (DP[i] + sum) % MOD;
		cout << "DP[" << i << "] = DP[" << i << "] + " << sum<<" : "<<DP[i] << endl;

		sums[i + 1] = (sums[i] + DP[i]) % MOD;
		cout << "sums[" << i + 1 << "] = sums[" << i << "] + DP[" << i << "]: " << sums[i + 1] << endl;
		//cout << sums[i + 1] << endl;
	}

	//나머지 연산에 의해 높은 인덱스 값이  낮은 인덱스 원소 값보다 작아지는 경우가 있다. 이로 인해 sums 뺄셈 연산을 할 때
	//DP값이 음수가 되는 경우가 있다. 다음 코드를 적용하면 음수가 반환되는 경우를 없앨 수 있다.
	if (DP[n] < 0)
	{
		cout << "음수 반환" << endl;
	}

	return (DP[n] < 0) ? DP[n] + MOD : DP[n];
}

vector<int> Generate(int n)
{
	vector<int> distance(n);
	LL val = 1;

	for (int i = 0; i < n; i++)
	{
		val = (val * 1103515245 + 12345) / 65536;
		val %= 32768;

		distance[i] = ((val % 10000) % (n - i)) + 1;
	}

	return distance;
}

int main()
{
	int n;
	cin >> n;

	vector<int> distance(n);

	if (n == 1e7)
	{
		distance = Generate(n);
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			cin >> distance[i];
		}

		cout << endl;
	}

	LL result = TravelItinerary(n, distance);
	cout<<endl << result << endl;
}

/*
 3
 1 1 1
 = 1

 6
 1 2 3 2 2 1
 = 9

 15
 1 2 5 3 4 2 1 3 6 1 2 1 2 2 1
 = 789

 40
 8 5 9 9 11 3 10 9 9 5 1 6 13 3 13 9 8 5 11 8 4 5 10 3 11 4 10 4 12 11 8 9 3 7 6 4 4 3 2 1
 = 47382972

 100
 39 79 34 76 12 28 51 60 53 7 30 48 45 61 66 24 50 64 18 47 7 19 16 72 8 55 72 26 43 57 45 26 68 23 52 28 35 54 2 57 29 59 6 57 8 47 6 44 43 35 50 41 45 4 43 39 44 43 42 26 40 39 32 37 31 20 9 33 30 27 30 29 28 27 26 25 24 23 22 15 20 19 18 17 1 15 14 2 12 11 1 6 8 7 6 5 4 3 2 1
 = 790903754

 10000000
 = 318948158
 */