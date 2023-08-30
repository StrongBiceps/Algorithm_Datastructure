#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <iomanip>

/*
top-down solution�� �ۼ��Ѵ�.

�� ���� ���� ó���� if1,if2(end,low)�� Ī�Ѵ�. end�� ������ ���̰� low�� set[i] > sum �� ���
SubsetSum_Backtracking���� ���� ���� ���� y ���� �ʴ� ���� n��� Ī�Ѵ�.
SubsetSum_Backtracking�� SB��� ����Ѵ�.
(false,true)�� �ش� ��Ϳ��� || �� �������� ���������� �˷��ִ� ���̴�.

sort ���
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

������ ������������ ������ �� �ϳ��� ���鼭 target�� 58�� ���� �� �ִ� ������ ã�´�.
���� ���ǿ� ���ؼ� �߰� ��͸� ����Ѵ�.
���� ���ǿ� �ɸ��� ��͸� ����� ���鼭 ������ ��� ������ ������ Ž���� �� �ִ�.
��, BruteForce�� �ٸ� ���� ��� ����� ���� Ž���ϴ� ���� �ƴ϶�. ���� ������ ���ؼ�
����� ���� ������ ���� ���̴�.
*/
//����� ���� ��ó����
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
	// ���� set�� ���� ������ ���
	if (index == set.size())
	{
		// �κ����� ũ�⸦ �ε����� ����Ͽ� �κ������� allSubsets�� �߰�
		allSubsets[subset.size()].push_back(subset);
		return;
	}

	// ���Ҹ� �߰����� �ʰ� ��� ȣ��
	GetAllSubsets(set, subset, index + 1, allSubsets);

	// ���Ҹ� �κ����տ� �߰��� �� ��� ȣ��
	subset.push_back(set[index]);
	GetAllSubsets(set, subset, index + 1, allSubsets);
}

bool SubsetSum_BruteForce(vector<int> set, int target)
{
	vector<vector<vector<int>>> allSubsets(set.size() + 1);

	GetAllSubsets(set, {}, 0, allSubsets);

	for (int size = 0; size <= set.size(); size++)
	{
		PRINT("�κ������� ���� ����: " << size << endl);

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
	//�Ʒ� if���� ���� ���ǿ� ���� ó���� ��Ÿ����.
	
	// ���� ���� �κ������� ���� target�� ���ٸ�
	if (sum == 0)
	{
		return true;
	}

	// ���� ���� �κ������� ���� target���� ũ�ų�, ������ ���� �����ߴٸ�
	if (i == set.size() || set[i] > sum)
	{
		return false;
	}

	//�� �ܰ踶�� sum�� ���� �迭 ���Ҹ� ���ϰų� �Ǵ� sum���� �״�� �����ϸ鼭 �˻縦 �ݺ��Ѵ�.
	//�� �� ���� ��츦 ������ ���� �ϳ��� �ڵ�� ǥ���� �� �ִ�.

	// Case 1: sum���� set[i]�� ���� ��� ȣ�� (i��° ���Ҹ� �κ����տ� �߰�)
	// Case 2: sum�� �״�� �����Ͽ� ��� ȣ�� (i��° ���Ҹ� �κ����տ� �߰����� ����)

	return SubsetSum_Backtracking(set, sum - set[i], i + 1)
		|| SubsetSum_Backtracking(set, sum, i + 1);
}

//�κ����� �� ���� Ǯ�� ����� ���� ����
vector<string> types =
{
	"BRUTE FORCE",
	"BACKTRACKING",
	"MEMOIZATION",
	"TABULATION"
};

//clock_t ��ü�� ������ ���ڿ��� ���ڷ� �޾� ��� �ð��� ����Ѵ�.
void GetTime(clock_t& timer, string type)
{
	// ���� �ð����� timer�� ���� ��� �ð��� ���
	timer = clock() - timer;

	// ȭ�鿡 ��� �ð� ���
	cout << type << " ��� ��� �ð�: ";
	cout << fixed << setprecision(5) << (float)timer / CLOCKS_PER_SEC << endl;

	timer = clock(); // timer�� ���� �ð����� �ʱ�ȭ
}

int main()
{
	vector<int> set = { 16, 1058, 22, 13, 46, 55, 3, 92, 47, 7,
					   98, 367, 807, 106, 333, 85, 577, 9, 3059 };
	int target = 6076;
	int tests = 2;

	//�켱 ���� set�� �����Ѵ�.(sort�� �⺻������ �������� ����)
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
			cout << "���� ���� " << target << "�� �κ������� �ֽ��ϴ�." << endl;
		}
		else
		{
			cout << "���� ���� " << target << "�� �κ������� �����ϴ�." << endl;
		}

		GetTime(timer, types[i]);
		cout << endl;
	}
}