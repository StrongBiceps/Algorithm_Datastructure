#include <vector>
#include <algorithm>
#include <time.h>
#include <Windows.h>
#include <iomanip>
#include <iostream>

//부분집합의 합을 구하는 단계에서 1106번째 재귀에서 처음 중복된 부분문제가 발생하여
//캐시를 통해서 재귀가 줄어든다. 일반적인 집합(작은 크기의 집합)에서는 중복이 발생하지
//않고 어느정도 크기가 있는 집합에서 총 합보다 미세하게 작은 합을 검색하는 경우에 효과가 있을
//것으로 보인다. 만약 미세하게 작은 값이 아니라 6070을 입력으로 넣었을 경우에는 백트래킹과
//메모이제이션의 차이가 2배 차이밖에 나지 않는다.

//아래는 피보나치 계산에서의 메모이제이션 활용이다.
/*R은 재귀가 줄었다는 뜻 Reduce

fib(5)
	memo[5]=fib(4)+fib(3)
		fib(4)
			memo[4]=fib(3)+fib(2)
				fib(3)
					memo[3]=fib(2)+fib(1)
						fib(2)
							memo[2]=fib(1)+fib(0)
						fib(1)
				fib(2)
				return memo[2] - R
		fib(3)
		return memo[3] - R
fib(3)과 fib(2)의 중복 문제에서 재귀를 줄였다.

std::unordered_map<int, int> memo;

int fibonacci_memoization(int n) {
    if (memo.find(n) != memo.end()) {
        return memo[n];
    }

    if (n <= 1) {
        return n;
    }

    memo[n] = fibonacci_memoization(n - 1) + fibonacci_memoization(n - 2);
    return memo[n];
}


메모이제이션에 대해서 분석을 추가하자면,
메모이제이션은 재귀에서 선행 재귀가 후행 재귀의 값을 이용하는 것이고, 타뷸레이션은 후행 재귀가 선행 재귀의 값을 이용하는 것이다.
즉 메모이제이션은 재귀가 깊어지면서 기저 조건을 만나면 테이블에 값이 설정되기 시작한다. 그 값을 선행 재귀가 사용한다.

예를 들어서 set의 크기가 10이고 Target이 100인 문제가 있다고 가정하자, 만약 memo[8][95] = false 일 때 재귀를 진행하다가 해당 경우를
만나게 되면 위 값을 이용할 수 있게 된다. 즉 인덱스 8까지 계산해서 95의 값이 나왔을 때는 더 이상 계산해봤자 Target을 만들 수 없으므로
memo 테이블에 의해서 재귀를 줄일 수 있다. 백 트래킹에서는 테이블을 참조하지 않으므로 8,95의 경우가 중복해서 나와도 계산을 끝까지 하게
되어 있다. 재귀를 거슬러 올라가면서 memo테이블이 채워지게 되면 초기 인덱스 값에 대해서도 재귀를 중단할 수 있다.

또한 append와 ignore에 대해서 분석을 한다면,

append의 경우
인덱스 2에서 sum+set[2]를 만들 수 있다면 인덱스 1에서도 sum을 만들 수 있다. sum+set[2]에서 단순히 인덱스 2의 값을 빼면 만들 수 있다.

ignore의 경우
인덱스 2에서 sum을 만들 수 있다면(인덱스 2의 값을 더하지 않았을 때) 인덱스 1까지에서도 sum을 만들 수 있다. 읽어보면 당연한 소리이다. 

따라서 위 논리에 의해서 후행 재귀의 값이 선행 재귀에서 사용될 수 있는 것이다.

*분석 추가

set.size == 10이고 Target == 100일 때

i -> 인덱스

i = 8일 때

append(9)
ignore(9)

만약 위 2가지 경우에서 100을 만들지 못하면 8까지에서도 100을 만들 수 없다. 따라서 memo[8][sum(8까지 계산된 특정 값)] = false

다음에 memo[8][sum]의 경우가 나오면 이 이상 계산해도 100을 만들 수 없으므로 재귀 취소

즉 sum에서 추가로 인덱스 i 이후의 원소들을 계산했을 때 Target을 만들 수 있는지가 memo의 의미가 된다.

*/
#define DEBUG 0

#if DEBUG
#define PRINT(x) cerr << x
#else
#define PRINT(x)
#endif

int RecursionCount = 0;

using namespace std;

const int UNKNOWN = -1;

void GetAllSubsets(vector<int> set, vector<int> subset,
	int index, vector<vector<vector<int>>>& allSubsets)
{
	// 집합 set의 끝에 도달한 경우
	if (index == set.size())
	{
		// 부분집합 크기를 인덱스로 사용하여 부분집합을 allSubsets에 추가
		allSubsets[subset.size()].push_back(subset);
		return;
	}

	// 원소를 추가하지 않고 재귀 호출
	GetAllSubsets(set, subset, index + 1, allSubsets);

	// 원소를 부분집합에 추가한 후 재귀 호출
	subset.push_back(set[index]);
	GetAllSubsets(set, subset, index + 1, allSubsets);
}

bool SubsetSum_BruteForce(vector<int> set, int target)
{
	vector<vector<vector<int>>> allSubsets(set.size() + 1);

	GetAllSubsets(set, {}, 0, allSubsets);

	for (int size = 0; size <= set.size(); size++)
	{
		PRINT("부분집합의 원소 개수: " << size << endl);

		for (auto subset : allSubsets[size])
		{
			PRINT("\t{ ");

			int sum = 0;
			for (auto number : subset)
			{
				sum += number;
				PRINT(number << " ");
			}

			PRINT("} = " << sum << endl);

			if (sum == target)
				return true;
		}
	}

	return false;
}

bool SubsetSum_Backtracking(vector<int> set, int sum, int i)
{
	// 만약 현재 부분집합의 합이 target과 같다면
	if (sum == 0)
	{
		return true;
	}

	// 만약 현재 부분집합의 합이 target보다 크거나, 집합의 끝에 도달했다면
	if (i == set.size() || set[i] > sum)
	{
		return false;
	}

	// Case 1: sum에서 set[i]을 빼서 재귀 호출 (i번째 원소를 부분집합에 추가)
	// Case 2: sum을 그대로 전달하여 재귀 호출 (i번째 원소를 부분집합에 추가하지 않음)

	return SubsetSum_Backtracking(set, sum - set[i], i + 1)
		|| SubsetSum_Backtracking(set, sum, i + 1);
}

//memeo라는 2차원 정수 벡터의 참조를 추가로 가진다.
bool SubsetSum_Memoization(vector<int>& set, int sum, int i,
	vector<vector<int>>& memo)
{
	++RecursionCount;

	//cout << i << ", " << sum << "함수가 호출됨" << endl;
	//기저 조건 처리 코드
	
	// 만약 현재 부분집합의 합이 target과 같다면
	if (sum == 0)
	{
		return true;
	}

	// 만약 현재 부분집합의 합이 target보다 크거나, 집합의 끝에 도달했다면
	if (i == set.size() || set[i] > sum)
	{
		//cout << "끝에 도달함" << endl;
		return false;
	}

	// 현재 상태가 캐시에 있는지 확인
	if (memo[i][sum] == UNKNOWN)
	{
		// 현재 상태에 대한 솔루션을 구하여 캐시에 저장
		bool append = SubsetSum_Memoization(set, sum - set[i], i + 1, memo);
		bool ignore = SubsetSum_Memoization(set, sum, i + 1, memo);

		memo[i][sum] = append || ignore;
		//cout << "[" << i << "]" << "[" << sum << "]" <<"이 저장됨" << endl;
		// 캐시에 저장된 값을 반환
		return memo[i][sum];
	}
	else
	{
		//cout << "재귀 수" << RecursionCount << endl;
		//cout << i << ", " << sum << "이 중복됨" << endl;
		// 캐시에 저장된 값을 반환
		return memo[i][sum];
	}

	//// 캐시에 저장된 값을 반환
	//return memo[i][sum];
}

vector<string> types =
{
	"BRUTE FORCE",
	"BACKTRACKING",
	"MEMOIZATION",
	"TABULATION"
};

void GetTime(clock_t& timer, string type)
{
	// 현재 시간에서 timer를 빼서 경과 시간을 계산
	timer = clock() - timer;

	// 화면에 경과 시간 출력
	cout << type << " 방법 경과 시간: ";
	cout << fixed << setprecision(5) << (float)timer / CLOCKS_PER_SEC << endl;

	timer = clock(); // timer를 현재 시간으로 초기화
}

int main()
{
	vector<int> set = { 16, 1058, 22, 13, 46, 55, 3, 92, 47, 7,
					   98, 367, 807, 106, 333, 85, 577, 9, 3059 };
	//int target = 6799;
	int target = 6070;
	int tests = 3;

	sort(set.begin(), set.end());

	for (int i = 0; i < tests; i++)
	{
		bool found = false;

		clock_t timer = clock();

		switch (i)
		{
		case 0:
			found = SubsetSum_BruteForce(set, target);
			break;
		case 1:
			found = SubsetSum_Backtracking(set, target, 0);
			break;
		case 2:
		{
			// 메모이제이션 테이블 초기화
			vector<vector<int>> memo(set.size(), vector<int>(7000, UNKNOWN));

			found = SubsetSum_Memoization(set, target, 0, memo);
			break;
		}
		}

		if (found)
		{
			cout << "원소 합이 " << target << "인 부분집합이 있습니다." << endl;
		}
		else
		{
			cout << "원소 합이 " << target << "인 부분집합이 없습니다." << endl;
		}

		GetTime(timer, types[i]);
		cout << endl;
	}
}
