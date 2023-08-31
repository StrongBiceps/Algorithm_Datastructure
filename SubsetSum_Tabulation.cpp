#include <vector>
#include <algorithm>
#include <time.h>
#include <iomanip>
#include <iostream>

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

	// Case 1: sum���� set[i]�� ���� ��� ȣ�� (i��° ���Ҹ� �κ����տ� �߰�)
	// Case 2: sum�� �״�� �����Ͽ� ��� ȣ�� (i��° ���Ҹ� �κ����տ� �߰����� ����)

	return SubsetSum_Backtracking(set, sum - set[i], i + 1)
		|| SubsetSum_Backtracking(set, sum, i + 1);
}

bool SubsetSum_Memoization(vector<int>& set, int sum, int i,
	vector<vector<int>>& memo)
{
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

	// ���� ���°� ĳ�ÿ� �ִ��� Ȯ��
	if (memo[i][sum] == UNKNOWN)
	{
		// ���� ���¿� ���� �ַ���� ���Ͽ� ĳ�ÿ� ����
		bool append = SubsetSum_Memoization(set, sum - set[i], i + 1, memo);
		bool ignore = SubsetSum_Memoization(set, sum, i + 1, memo);

		memo[i][sum] = append || ignore;
	}

	// ĳ�ÿ� ����� ���� ��ȯ
	return memo[i][sum];
}

//�� �Լ��� ���� ���� set�� ���ڷ� �ް�, 2���� �ο��� ���͸� ��ȯ�Ѵ�,
vector<vector<bool>> SubsetSum_Tabulation(vector<int>& set)
{
	int maxSum = 0;

	for (int i = 0; i < set.size(); i++)
	{
		maxSum += set[i];
	}

	//DP��� �̸��� 2���� �ο��� ���͸� �����Ͽ� ����Ѵ�. dp�� ù ��° ���� ũ��� �Է� ������ ũ��� ����, �� ��° ������ ũ���
	//�Է� ������ ��� ���� �պ��� 1��ŭ ũ�� �����Ѵ�. dp�� ��� ���Ҵ� false�� �ʱ�ȭ�ϵ�, �κ������� ���� 0�� ���� ���ǿ� ���ؼ�
	//�� true�� �����Ѵ�.

	//ù ��° ������ �ε����� �ǹ��ϰ� �� ��° ������ �κ������� ���� �ǹ��Ѵ�.
	vector<vector<bool>> DP(set.size() + 1, vector<bool>(maxSum + 1, 0));

	//�� ������ ���� ������ �ε��� 0�� true�� �����Ѵ�.
	for (int i = 0; i < set.size(); i++)
	{
		DP[i][0] = true;
	}

	//DP ���̺� ���� ���� �����ϱ� ���� ���� for�ݺ����� ����Ѵ�.

	//3 7 9 13 16 22 46 47 55 85 92 98 106 333 367 577 807 1058 3059


	//i������ i-1 �ε��������� ������ sum�� ���� �� �ִٸ� i������ sum�� ���� �� �ִ�.
	//if-else�� ��찡 ������ ������ sum���� set[i-1]���� ���ų� ũ�ٸ� i-1 ���� �ܰ迡�� �̹� sum����
	//������� �� �ִ� ��쵵 ������, i-1���� ���Ҹ� ��� ���ص� sum������ ���� ��찡 �ִ�. 
	//���� 9 ������ ��츦 �����غ��� �ȴ�. 7 �������� 3,7�� ���� ���� ������ 10�� 7�� ���ؾ� ���� �� �ִ�.
	//���� 7�� ���� �� ������� �� �ִ°��� ���� ���̴�. ���� ������� �� �ִٸ� 7�� ���ϸ� 9������ �ش� ���� 
	//���� �� �ְ� �ȴ�. DP[i-1][sum]�� �����ϴ� ���� set[i-1]�� �������� �ʾ��� ��츸 �����ϱ� ������ if-else�� ������.
	//���� ��� ���� 7�϶� 7�� ������� �� �ִ� ���� ������� �ʴ´�. �׻� �ڽ� ���� ���ҵ��� ������ ��츸 true�� �����Ѵ�.
	//���� i �ε������� i-1������ �պ��� sum�� ũ�ٸ� DP[i][sum]=false�� �� ���̴�.
	
	//���� �ε��� i=set.size�� ���� i������ ���� ���� ���ϳ� ��� ���� �� �ִµ�, ������ ũ�Ⱑ size+1�̰� ������ ���ҿ� ����
	//����� DP[size+1][sum]�� ����ȴ�.
	for (int i = 1; i <= set.size(); i++)
	{
		for (int sum = 1; sum <= maxSum; sum++)
		{
			//�ε��� i=1�� ���� Set[0] = 3 �̹Ƿ� 2���� ù ��° if���� ����ȴ�.
			if (sum < set[i - 1])
			{
				//���� �ʱ⿡�� sum=1�̰�, i�� 1�̴�.
				//DP[1][1]=DP[0][1]�� �ȴ�.
				//DP[1][1]=false�� �ȴ�. DP[0][1]�� false�̴�.

				//�ε��� i=1������
				//DP[1][1~MAX] = DP[0][MAX]�� �ȴ�.
				DP[i][sum] = DP[i - 1][sum];
			}
			else // sum >= set[i-1]
			{
				//i=1�� �� sum�� 3�� �Ǹ� �ش� �ڵ尡 ����ȴ�.
				//DP[1][3]=DP[0][3] || DP[0][0] �� �ȴ�.

				//�� �ڵ带 �м��غ���, �ε��� i���� �κ������� �� sum >= set[i]�� ��
				//DP[i-1][sum] = true �� �ϳ� ���� �ε������� �ش� sum���� ���� �� �ִٸ�
				//i������ sum�� ���� �� �ִ�.

				//i�� ����Ű�� ���� 92�� ���� ���� ���
				//i->92�� �� sum�� 86�̶�� ����. �׷��� i->85�� �� 86�� �ϼ��� �� �ִ��� ����� ���̴�.
				//���� false��� �� ��° �������� �Ѿ��. 
				//�� ��° ������ i->85���� 86-85=1�� ���� �� �ִ°��� ����� ���̴�.

				//i�� ����Ű�� ���� 9������ �� �Լ��� ���� ��Ȳ�� ����غ���.
				//���� DP[1]���� 3�� true�� ������ ���̴�.
				//i�� 2�� �Ǹ� DP[2]���� 3 7 10�� true�� ������ ���̴�.
				//10�� true�� �����Ǵ� ������ DP[1][10]�� �Ұ����ϹǷ� 
				//DP[1][3]���� �Ѿ��. �׷��� ������ DP[1][3]�� true�̹Ƿ� DP[2][10]�� true�� �����ȴ�.
				//���� sum < set[i-1]�� ���� set[i-1]�� ������ ����� ������ �ʿ� ���� set[i-1]���� sum�� ������� �� �ִ�����
				//Ȯ���ؾ� �Ѵ�. ������ set[i-1] <= sum�� ���� set[i-1]�� ������ ����� ������ �غ��� �Ѵ�. ���� set[i-1]����
				//sum���� set[i-1]�� ������ �� ���� ������� �� �ִٸ� i������ set[i-1]�� ���ؼ� sum�� ���� �� �ְ� �ȴ�.
				//�׷��� ���� set[i-1]�� ���� ���� sum�� ������� �� ���ٸ� �̹� �������� sum-set[i-1]�� ������� �� �����Ƿ�
				//sum�� i���� ������� �� ����. �ݺ��� �����ϸ鼭 DP[1]�� 3�� true�� �����ǰ� DP[2]�� 3,7,10�� true�� �����ǹǷ�
				//index i������ sum-set[i-1]������ ��� ����� ���� true�� �ٲ�Ƿ� i�ܰ迡���� sum-set[i-1]�� ������� �� �ִ�����
				//Ȯ���ϸ� �ȴ�. i������ ��츦 ���� �ٽ� ����ؼ� sum-set[i-1]�� �������� üũ���� �ʾƵ� �ȴ�.
				DP[i][sum] = DP[i - 1][sum]
					|| DP[i - 1][sum - set[i - 1]];
			}
		}
	}

	return DP;
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
	int target = 6800;
	int tests = 4;

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
			// �޸������̼� ���̺� �ʱ�ȭ
			vector<vector<int>> memo(set.size(), vector<int>(7000, UNKNOWN));

			found = SubsetSum_Memoization(set, target, 0, memo);
			break;
		}
		case 3:
		{
			int total = 0;
			for (auto number : set)
				total += number;

			vector<vector<bool>> DP = SubsetSum_Tabulation(set);
			found = DP[set.size()][target];

			vector<int> subsetSums;
			for (int sum = 1; sum <= total; sum++)
			{
				if (DP[set.size()][sum])
				{
					subsetSums.push_back(sum);
				}
			}

			cout << "������ ���� " << subsetSums.size() << "������ �κ������� ���� �����մϴ�:" << endl;

			for (auto sum : subsetSums)
				cout << sum << " ";
			cout << endl;

			break;
		}
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