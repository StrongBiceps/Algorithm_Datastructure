#include <iostream>
#include <vector>
#include <algorithm>

/*
Set size = 4

-false는 원소 추가하지 않고 재귀 호출
-true는 원소 추가한 뒤 재귀 호출
-if push는 if문 안에서의 push

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


분석:
GetAllSubsets(1) - false 를 상위트리로 취급할 것이다.
GetAllSubsets(1) - true가 하위트리로 취급할 것이다.


vector<int> Subset은 값에 의한 호출이므로 다른 상위 재귀로 회귀하면 하위 재귀에서 업데이트되었던 subset은 사라진다는 사실을 인지하라.
하지만 allSubset은 참조이므로 모든 변경사항이 저장된다.

GetAllSubsets(4)가 처음 호출될 때 allSubsets[0]={} 상태가 된다.
가장 상위 트리에서는 subset이 비어있는 경우이다.
또 GetAllSubsets(4)에서만 allSubset에 push된다.

상위 트리의 GetAllSubsets(2) - false까지의 과정에서 Set[3],Set[2]가 allSubset[0],[1],[2]에 조합되어서 저장된다.
상위 트리의 GetAllSubsets(2) - true까지의 과정에서 Set[1],Set[2],Set[3]이 allSubset[1],[2],[3]에 조합되어서 저장된다.
상위 트리의 GetAllSubsets(1) - false까지의 과정에서 Set[1],Set[2],Set[3]이 조합되어 저장된다.

하위 트리의 GetAllSubsets(2) - false까지의 과정에서 Set[0],Set[3],Set[2]가 allSubset[1],[2],[3]에 조합되어서 저장된다.
하위 트리의 GetAllSubsets(2) - true까지의 과정에서 Set[0],Set[1],Set[2],Set[3]이 allSubset[2],[3],[4]에 조합되어서 저장된다.
하위 트리의 GetAllsubsets(1) - true까지의 과정에서 Set[0],Set[1],Set[2],Set[3]이 조합되어서 저장된다.

GetAllSubSets(4) 이전에 subset에 원소가 몇 개인지에 따라 push allSubsets의 인덱스가 결정된다. 가장 상위트리에서는 아무것도 없으므로 가장 처음에 [0]에 들어간다.
또 GetAllSubsets(3)~(4)에서는 Set[2],Set[3]이 조합된다. 즉 아무것도 없었을 때는 인덱스가 [0],[1],[2]이 될 것이고 Set[2],Set[3]이 조합된다.
그리고 하나가 추가되었을 때는 Set[1],Set[2],Set[3]이 조합되어서 인덱스 [1],[2],[3]에 저장될 것이다.

2 3 조합 allSubset인덱스 0 1 2
1 2 3 조합 allSubset 인덱스 1 2 3
0 2 3 조합 allSubset 인덱스 1 2 3
0 1 2 3 조합 이 순서로 조합된다. allSubset 인덱스 2 3 4

왜 allSubset에 중복된 경우가 들어가지 않는가 생각해보면, 위 순서로 조합이 이루어지는데, 모두 다른 조합이고, 2 3은 계속해서 등장하지만,
1 2 3부터는 allSubset의 인덱스가 무조건 1이상이므로(0이 맨 앞에서 들어갔기 때문에) 인덱스 1에 중복되어서 들어갈 수는 없다.

위에서 적은 조합은 자세한 조합이 아니다. 조합을 자세히 보려면 재귀 트리를 따라가보면 알 수 있다. 또 각 재귀마다 다른 조합이 발생할 수 밖에 없다.
*/
//부가적인 기능으로 DEBUG라는 전처리기 상수와 PRINT라는 매크로 함수를 정의하고, DEBUG가 0이 아닌 경우에만 stderr 출력을 수행하도록 설정한다.
#define DEBUG 1

#if DEBUG
#define PRINT(x) cerr << x
#else
#define PRINT(x)
#endif

using namespace std;

//집합의 모든 부분집합을 구하는 GetAllSubsets()함수를 정의한다. 이 함수는 두 개의 정수 벡터 Set과 Subset, 정수 index,
//그리고 모든 부분집합을 저장할 3차원 정수 벡터 allSubsets를 인자로 받는다. 이때 allSubsets는 참조로 전달한다. 이 함수는
//재귀 호출을 이용하여 set의 모든 부분집합을 생성한다.
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

//이 함수는 입력 집합을 표현하는 정수 벡터 set과 부분집합의 합을 나타내는 정수 target을 인자로 받고,bool 값을 반환한다. 
//이 함수의 앞부분에서 전체 부분집합을 저장할 allSubsets를 선언하고 GetAllSubsets()함수를 호출한다.
bool SubsetSum_BruteForce(vector<int> set, int target)
{
	//set.size()+1을 하는 이유는 set집합과 같은 크기의 부분 집합이 하나 존재하기 때문에
	//해당 인덱스를 사용해야 하기 때문이다.
	vector<vector<vector<int>>> allSubsets(set.size() + 1);

	GetAllSubsets(set, {}, 0, allSubsets);

	//각 부분집합의 원소 합을 target과 비교하고, 만약 일치하면 true를 반환한다. 만약 부분집합의 합이 target과 같은 경우가 발생하지 않으면
	//false를 반환한다.
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

int main()
{
	vector<int> set = { 13, 79, 45, 29 };
	int target = 58;

	bool found = SubsetSum_BruteForce(set, target);

	if (found)
	{
		cout << "원소 합이 " << target << "인 부분집합이 있습니다." << endl;
	}
	else
	{
		cout << "원소 합이 " << target << "인 부분집합이 없습니다." << endl;
	}
}