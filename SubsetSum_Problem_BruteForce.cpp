#include <iostream>
#include <vector>
#include <algorithm>

/*
Set size = 4

-false�� ���� �߰����� �ʰ� ��� ȣ��
-true�� ���� �߰��� �� ��� ȣ��
-if push�� if�� �ȿ����� push

GetAllSubsets(0) - Start
	GetAllSubsets(1) - false
		GetAllSubsets(2) - false
			GetAllSubsets(3) - false
				GetAllSubsets(4) - false
					if-push allSubset[0]={}
				push subset[0]=Set[3]
				GetAllSubsets(4) - true
					if-push allSubset[1]={{Set[3]]}
			push subset[0] = Set[2]
			GetAllSubsets(3) -true
				GetAllSubsets(4) - false
					if push allSubset[1] ={{Set[2]},{Set[3]}}
				push subset[1]=Set[3]
				GetAllSubsets(4) - true
					if-push allSubset[2] = {{Set[2],Set[3]}}
		push subset[0] = Set[1]
		GetAllSubsets(2) - true
			GetAllSubsets(3) - false
				GetAllSubsets(4) - false
					if-push allSubset[1] = {{Set[3]},{Set[1]},{Set[2]}}
				push subset[1] = Set[3]
				GetAllSubsets(4) - true
					if-push allSubset[2] = {{Set[2],Set[3]},{Set[1],Set[3]}}
			push subset[1] = Set[2]
			GetAllSubsets(3) - true
				GetAllSubsets(4) - false
					if - push allSubset[2] = {{Set[2],Set[3]},{Set[1],Set[3]},{Set[1],Set[2]}}
				push subset[2] = Set[3]
				GetAllSubsets(4) - true
					if - push allSubset[3] = {{Set[1],Set[2],Set[3]}}
	push subset[0] = Set[0]
	GetAllSubsets(1) - true
		GetAllSubsets(2) - false
			GetAllSubsets(3) - false
				GetAullSubsets(4) - false
					if-push allSubset[1]={{Set[3]},{Set[1]},{Set[2]},{Set[0]}}
				push subset[1] = Set[3]
				GetAllSubsets(4) - true
					if-push allSubset[2] = {{Set[2],Set[3]},{Set[1],Set[3]},{Set[1],Set[2]},{Set[0],Set[3]}}
			push subset[1] = Set[2]
			GetAllSubsets(3) - true
				GetAllSubsets(4) - false
					if-push allSubset[2] = {{Set[2],Set[3]},{Set[1],Set[3]},{Set[1],Set[2]},{Set[0],Set[3]},{Set[0],Set[2]}}
				push subset[2] = Set[3]
				GetAllSubsets(4) - true
					if-push allSubset[3] = {{Set[1],Set[2],Set[3]},{Set[0],Set[2],Set[3]}}
		push subset[1] = Set[1]
		GetAllSubsets(2) - true
			GetAllSubsets(3) -false
				GetAllSubsets(4) - false
					if-push allSubsets[2] = {{Set[2],Set[3]},{Set[1],Set[3]},{Set[1],Set[2]},{Set[0],Set[3]},{Set[0],Set[1]}}
				push subsets[2] = Set[3]
				GetAllSubsets(4) - true
					if-push allSubsets[3] ={{Set[1],Set[2],Set[3]},{Set[0],Set[2],Set[3]},{Set[0],Set[1],Set[3]}}
			push subset[2] = Set[2]
			GetAllSubsets(3) - true
				GetAllSubsets(4) - false
					if-push allSubsets[3] = {{Set[1],Set[2],Set[3]},{Set[0],Set[2],Set[3]},{Set[0],Set[1],Set[3]},{Set[0],Set[1],Set[2]}}
				push subsets[3] = Set[3]
				GetAllSubsets(4) - true
					if-push allSubsets[4] = {{Set[0],Set[1],Set[2],Set[3]}}


�м�:
GetAllSubsets(1) - false �� ����Ʈ���� ����� ���̴�.
GetAllSubsets(1) - true�� ����Ʈ���� ����� ���̴�.


vector<int> Subset�� ���� ���� ȣ���̹Ƿ� �ٸ� ���� ��ͷ� ȸ���ϸ� ���� ��Ϳ��� ������Ʈ�Ǿ��� subset�� ������ٴ� ����� �����϶�.
������ allSubset�� �����̹Ƿ� ��� ��������� ����ȴ�.

GetAllSubsets(4)�� ó�� ȣ��� �� allSubsets[0]={} ���°� �ȴ�.
���� ���� Ʈ�������� subset�� ����ִ� ����̴�.
�� GetAllSubsets(4)������ allSubset�� push�ȴ�.

���� Ʈ���� GetAllSubsets(2) - false������ �������� Set[3],Set[2]�� allSubset[0],[1],[2]�� ���յǾ ����ȴ�.
���� Ʈ���� GetAllSubsets(2) - true������ �������� Set[1],Set[2],Set[3]�� allSubset[1],[2],[3]�� ���յǾ ����ȴ�.
���� Ʈ���� GetAllSubsets(1) - false������ �������� Set[1],Set[2],Set[3]�� ���յǾ� ����ȴ�.

���� Ʈ���� GetAllSubsets(2) - false������ �������� Set[0],Set[3],Set[2]�� allSubset[1],[2],[3]�� ���յǾ ����ȴ�.
���� Ʈ���� GetAllSubsets(2) - true������ �������� Set[0],Set[1],Set[2],Set[3]�� allSubset[2],[3],[4]�� ���յǾ ����ȴ�.
���� Ʈ���� GetAllsubsets(1) - true������ �������� Set[0],Set[1],Set[2],Set[3]�� ���յǾ ����ȴ�.

GetAllSubSets(4) ������ subset�� ���Ұ� �� �������� ���� push allSubsets�� �ε����� �����ȴ�. ���� ����Ʈ�������� �ƹ��͵� �����Ƿ� ���� ó���� [0]�� ����.
�� GetAllSubsets(3)~(4)������ Set[2],Set[3]�� ���յȴ�. �� �ƹ��͵� ������ ���� �ε����� [0],[1],[2]�� �� ���̰� Set[2],Set[3]�� ���յȴ�.
�׸��� �ϳ��� �߰��Ǿ��� ���� Set[1],Set[2],Set[3]�� ���յǾ �ε��� [1],[2],[3]�� ����� ���̴�.

2 3 ���� allSubset�ε��� 0 1 2
1 2 3 ���� allSubset �ε��� 1 2 3
0 2 3 ���� allSubset �ε��� 1 2 3
0 1 2 3 ���� �� ������ ���յȴ�. allSubset �ε��� 2 3 4

�� allSubset�� �ߺ��� ��찡 ���� �ʴ°� �����غ���, �� ������ ������ �̷�����µ�, ��� �ٸ� �����̰�, 2 3�� ����ؼ� ����������,
1 2 3���ʹ� allSubset�� �ε����� ������ 1�̻��̹Ƿ�(0�� �� �տ��� ���� ������) �ε��� 1�� �ߺ��Ǿ �� ���� ����.

������ ���� ������ �ڼ��� ������ �ƴϴ�. ������ �ڼ��� ������ ��� Ʈ���� ���󰡺��� �� �� �ִ�. �� �� ��͸��� �ٸ� ������ �߻��� �� �ۿ� ����.
*/
//�ΰ����� ������� DEBUG��� ��ó���� ����� PRINT��� ��ũ�� �Լ��� �����ϰ�, DEBUG�� 0�� �ƴ� ��쿡�� stderr ����� �����ϵ��� �����Ѵ�.
#define DEBUG 1

#if DEBUG
#define PRINT(x) cerr << x
#else
#define PRINT(x)
#endif

using namespace std;

//������ ��� �κ������� ���ϴ� GetAllSubsets()�Լ��� �����Ѵ�. �� �Լ��� �� ���� ���� ���� Set�� Subset, ���� index,
//�׸��� ��� �κ������� ������ 3���� ���� ���� allSubsets�� ���ڷ� �޴´�. �̶� allSubsets�� ������ �����Ѵ�. �� �Լ���
//��� ȣ���� �̿��Ͽ� set�� ��� �κ������� �����Ѵ�.
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

//�� �Լ��� �Է� ������ ǥ���ϴ� ���� ���� set�� �κ������� ���� ��Ÿ���� ���� target�� ���ڷ� �ް�,bool ���� ��ȯ�Ѵ�. 
//�� �Լ��� �պκп��� ��ü �κ������� ������ allSubsets�� �����ϰ� GetAllSubsets()�Լ��� ȣ���Ѵ�.
bool SubsetSum_BruteForce(vector<int> set, int target)
{
	//set.size()+1�� �ϴ� ������ set���հ� ���� ũ���� �κ� ������ �ϳ� �����ϱ� ������
	//�ش� �ε����� ����ؾ� �ϱ� �����̴�.
	vector<vector<vector<int>>> allSubsets(set.size() + 1);

	GetAllSubsets(set, {}, 0, allSubsets);

	//�� �κ������� ���� ���� target�� ���ϰ�, ���� ��ġ�ϸ� true�� ��ȯ�Ѵ�. ���� �κ������� ���� target�� ���� ��찡 �߻����� ������
	//false�� ��ȯ�Ѵ�.
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

int main()
{
	vector<int> set = { 13, 79, 45, 29 };
	int target = 58;

	bool found = SubsetSum_BruteForce(set, target);

	if (found)
	{
		cout << "���� ���� " << target << "�� �κ������� �ֽ��ϴ�." << endl;
	}
	else
	{
		cout << "���� ���� " << target << "�� �κ������� �����ϴ�." << endl;
	}
}