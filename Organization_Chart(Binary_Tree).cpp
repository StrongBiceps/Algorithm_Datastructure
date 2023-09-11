#include <iostream>
#include <queue>

//편의상 한 직원은 최대 두 명의 부하 직원을 거느릴 수 있다고 가정한다. 일단 이렇게 구현하고 나면 실제 회사와 비슷한 형태로
//확장하는 것은 그렇게 어렵지 않을 것이다. 이러한 형태의 트리를 이진 트리라고 한다. 이진 트리를 위한 기본 구조를 만든다.
struct node
{
	std::string position;
	node* first;
	node* second;
};

//각각의 노드는 다른 두 개의 노드에 대한 링크를 가진다. 이를 통해 데이터의 계층 구조를 나타낼 수 있다. 여기서는 노드에
//조직도상의 직책(Position)만을 저장했지만, 이는 우리가 원하는 형태로 확장할 수 있다. 해당 직책의 담당자 이름을 추가할 수도 있고,
//혹은 해당 부서의 모든 직원 정보를 담고 있는 구조체를 데이터에 저장할 수도 있다.

//여기서 루트 노드는 회사 CEO를 뜻한다.
struct org_tree
{
	node* root;

	//이 함수는 새로운 트리를 만드는 정적 함수이다. 이제 트리 구조를 확장시키는 기능을 추가한다.
	static org_tree create_org_structure(const std::string& pos)
	{
		org_tree tree;
		tree.root = new node{ pos, NULL, NULL };
		return tree;
	}

	//조직도에서 부하 직원을 추가하는 함수를 만든다. 이 함수는 상사의 직책 이름과 부하 직원의 직책 이름을 인자로 받으며,
	//이 중 상사의 직책은 이미 트리에 존재한다. 그런데 이 함수를 구현하기에 앞서 특정 직책 이름에 해당하는 노드를 찾아서 반환하는
	//함수를 먼저 만든다.

	//특정 원소를 찾기 위해 트리를 탐색할 때, 해당 원소는 현재 노드이거나 왼쪽 또는 오른쪽 서브트리에 있다. 가장 먼저 루트 노드를
	//검사하고, 만약 찾고자 하는 원소가 아니라면 왼쪽 서브 트리에서 다시 찾으려고 시도한다. 그래도 해당 원소를 찾지 못한다면 오른쪽
	//서브트리도 검사한다.
	static node* find(node* root, const std::string& value)
	{
		if (root == NULL)
			return NULL;

		if (root->position == value)
			return root;

		auto firstFound = org_tree::find(root->first, value);

		if (firstFound != NULL)
			return firstFound;

		return org_tree::find(root->second, value);
	}

	//이제 새로운 부하 직원을 추가하는 삽입 함수를 만든다. 이 함수에서는 앞서 만들었던 find()함수를 활용한다.
	bool addSubordinate(const std::string& manager, const std::string& subordinate)
	{
		auto managerNode = org_tree::find(root, manager);

		if (!managerNode)
		{
			std::cout << manager << "을(를) 찾을 수 없습니다: " << std::endl;
			return false;
		}

		if (managerNode->first && managerNode->second)
		{
			std::cout << manager << " 아래에 " << subordinate << "를 추가할 수 없습니다." << std::endl;
			return false;
		}

		if (!managerNode->first)
			managerNode->first = new node{ subordinate, NULL, NULL };
		else
			managerNode->second = new node{ subordinate, NULL, NULL };

		std::cout << manager << " 아래에 " << subordinate << "를 추가했습니다." << std::endl;

		return true;
	}
};

int main()
{
	auto tree = org_tree::create_org_structure("CEO");

	tree.addSubordinate("CEO", "부사장");
	tree.addSubordinate("부사장", "IT부장");
	tree.addSubordinate("부사장", "마케팅부장");
	tree.addSubordinate("IT부장", "보안팀장");
	tree.addSubordinate("IT부장", "앱개발팀장");
	tree.addSubordinate("마케팅부장", "물류팀장");
	tree.addSubordinate("마케팅부장", "홍보팀장");
	tree.addSubordinate("부사장", "재무부장");
}
