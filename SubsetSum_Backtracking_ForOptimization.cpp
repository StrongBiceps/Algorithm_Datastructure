#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <iomanip>

/*
top-down solution을 작성한다.

두 개의 기저 처리를 if1,if2(end,low)로 칭한다. end는 집합의 끝이고 low는 set[i] > sum 인 경우
SubsetSum_Backtracking에서 값을 빼는 것을 y 빼지 않는 것을 n라고 칭한다.
SubsetSum_Backtracking을 SB라고 축약한다.
(false,true)는 해당 재귀에서 || 가 성공인지 실패인지를 알려주는 것이다.

sort 결과
3 7 9 13 16 22 46 47 55 85 92 98 106 333 367 577 807 1058 3059

SB(6076,0) - start
	SB(6073,1) - y
		SB(6066,2) - y
			SB(6057,3) - y
				SB(6044,4) - y
					SB(6028,5) - y
						SB(6006,6) - y
							SB(5960,7) - y
								SB(5913,8) - y
									SB(5858,9) - y
										SB(5773,10) - y
											SB(5681,11) - y
												SB(5583,12) - y
													SB(5477,13) - y (false)
														SB(5144,14) - y (false)
															SB(4777,15) - y (false)
																SB(4200,16) - y	(false)																						SB(3393,17) - y (false)
																		SB(2335,18) - y
																		if2(low) - return false
																		SB(3393,18) - n
																		if2(end) - return false
																	SB(4200,17) - n (false)
																		SB(3142,18) - y
																		if2(end) - return false
																		SB(4200,18) - n
																		if2(end) - return false
																SB(4777,16) - n (false)
																	SB(3970,17) - y (false)
																		SB(2912,18) - y
																			if2(end) - return false
																		SB(3970,18) - n
																			if2(end) - return false
																	SB(4777,17) - n (false)
																		SB(3719,18) - y
																			if2(end) - return false
																		SB(4777,18) - n
																			if2(end) - return false
															SB(5144,15) - n (false)
																SB(4567,16) - y (false)
																	SB(3760,17) - y (false)
																		SB(2702,18) - y
																		if2(end) - return false
																		SB(3760,18) - n
																		if2(end) - return false
																	SB(4567,17) - n (false)
																		SB(3509,18) - y
																		if2(end) - return false
																		SB(4567,18) - n
																		if2(end) - return false
																SB(5144,16) - n (false)
																	SB(4337,17) - y (false)
																		SB(3279,18) - y
																		if2(end) - return false
																		SB(4337,18) - n
																		if2(end) - return false
														SB(5477,14) - n (false)
															SB(5110,15) - y (false)
																SB(4533,16) - y (false)
																	SB(3726,17) - y (false)
																		SB(2668,18) - y
																		if2(end) - return false
																		SB(3726,18) - n
																		if2(end) - return false
																	SB(4533,17) - n (false)
																		SB(3457,18) - y
																		if2(end) - return false
																		SB(4533,18) - n
																		if2(end) - return false
																SB(5110,16) - n (false)
																	SB(4304,17) - y (false)
																		SB(3245,18) - y
																		if2(end) - return false
																		SB(4304,18) - n
																		if2(end) - return false
													SB(5583,13) - n
														SB(5250,14) - y
															SB(4883,15) - y (false)
																SB(4306,16) - y (false)
																	SB(3499,17) - y (false)
																		SB(...18) - y
																		if2(end) - return false
																		SB(...18) - n
																		if2(end) - return false
																	SB(4306,17) - n (false)
																		SB(3248,18) - y
																		if2(end) - return false
																		SB(...18) - n
																		if2(end) - return false
																SB(5250,16) - n
																	SB(4443,17) - y
																		SB...




13 29 45 79

SB(58,0) - start
	SB(45,1) - y (true)
		SB(16,2) - y
		if2(low) - return false
		SB(45,2) - n (true)
			SB(0,3) - y
			Success - return true

집합을 오름차순으로 정렬한 후 하나씩 빼면서 target인 58을 만들 수 있는 조합을 찾는다.
기저 조건에 의해서 추가 재귀를 취소한다.
기저 조건에 걸리는 재귀를 취소해 가면서 가능한 모든 집합의 조합을 탐색할 수 있다.
단, BruteForce와 다른 점은 모든 경우의 수를 탐색하는 것이 아니라. 기저 조건을 통해서
재귀의 수를 현저히 줄인 것이다.
*/
//디버깅 전용 전처리기
#define DEBUG 0

#if DEBUG
#define PRINT(x) cerr << x
#else
#define PRINT(x)
#endif

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
	//아래 if문은 기저 조건에 대한 처리를 나타낸다.
	
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

	//매 단계마다 sum에 현재 배열 원소를 더하거나 또는 sum값을 그대로 유지하면서 검사를 반복한다.
	//이 두 가지 경우를 다음과 같이 하나의 코드로 표현할 수 있다.

	// Case 1: sum에서 set[i]을 빼서 재귀 호출 (i번째 원소를 부분집합에 추가)
	// Case 2: sum을 그대로 전달하여 재귀 호출 (i번째 원소를 부분집합에 추가하지 않음)

	return SubsetSum_Backtracking(set, sum - set[i], i + 1)
		|| SubsetSum_Backtracking(set, sum, i + 1);
}

//부분집합 합 문제 풀이 방법에 대한 구분
vector<string> types =
{
	"BRUTE FORCE",
	"BACKTRACKING",
	"MEMOIZATION",
	"TABULATION"
};

//clock_t 객체의 참조와 문자열을 인자로 받아 경과 시간을 출력한다.
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
	int target = 6076;
	int tests = 2;

	//우선 집합 set을 정렬한다.(sort는 기본적으로 오름차순 정렬)
	sort(set.begin(), set.end());

	for (const auto& i : set)
		std::cout << i << " ";

	std::cout << endl;

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