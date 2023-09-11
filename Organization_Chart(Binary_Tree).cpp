#include <iostream>
#include <queue>

//���ǻ� �� ������ �ִ� �� ���� ���� ������ �Ŵ��� �� �ִٰ� �����Ѵ�. �ϴ� �̷��� �����ϰ� ���� ���� ȸ��� ����� ���·�
//Ȯ���ϴ� ���� �׷��� ����� ���� ���̴�. �̷��� ������ Ʈ���� ���� Ʈ����� �Ѵ�. ���� Ʈ���� ���� �⺻ ������ �����.
struct node
{
	std::string position;
	node* first;
	node* second;
};

//������ ���� �ٸ� �� ���� ��忡 ���� ��ũ�� ������. �̸� ���� �������� ���� ������ ��Ÿ�� �� �ִ�. ���⼭�� ��忡
//���������� ��å(Position)���� ����������, �̴� �츮�� ���ϴ� ���·� Ȯ���� �� �ִ�. �ش� ��å�� ����� �̸��� �߰��� ���� �ְ�,
//Ȥ�� �ش� �μ��� ��� ���� ������ ��� �ִ� ����ü�� �����Ϳ� ������ ���� �ִ�.

//���⼭ ��Ʈ ���� ȸ�� CEO�� ���Ѵ�.
struct org_tree
{
	node* root;

	//�� �Լ��� ���ο� Ʈ���� ����� ���� �Լ��̴�. ���� Ʈ�� ������ Ȯ���Ű�� ����� �߰��Ѵ�.
	static org_tree create_org_structure(const std::string& pos)
	{
		org_tree tree;
		tree.root = new node{ pos, NULL, NULL };
		return tree;
	}

	//���������� ���� ������ �߰��ϴ� �Լ��� �����. �� �Լ��� ����� ��å �̸��� ���� ������ ��å �̸��� ���ڷ� ������,
	//�� �� ����� ��å�� �̹� Ʈ���� �����Ѵ�. �׷��� �� �Լ��� �����ϱ⿡ �ռ� Ư�� ��å �̸��� �ش��ϴ� ��带 ã�Ƽ� ��ȯ�ϴ�
	//�Լ��� ���� �����.

	//Ư�� ���Ҹ� ã�� ���� Ʈ���� Ž���� ��, �ش� ���Ҵ� ���� ����̰ų� ���� �Ǵ� ������ ����Ʈ���� �ִ�. ���� ���� ��Ʈ ��带
	//�˻��ϰ�, ���� ã���� �ϴ� ���Ұ� �ƴ϶�� ���� ���� Ʈ������ �ٽ� ã������ �õ��Ѵ�. �׷��� �ش� ���Ҹ� ã�� ���Ѵٸ� ������
	//����Ʈ���� �˻��Ѵ�.
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

	//���� ���ο� ���� ������ �߰��ϴ� ���� �Լ��� �����. �� �Լ������� �ռ� ������� find()�Լ��� Ȱ���Ѵ�.
	bool addSubordinate(const std::string& manager, const std::string& subordinate)
	{
		auto managerNode = org_tree::find(root, manager);

		if (!managerNode)
		{
			std::cout << manager << "��(��) ã�� �� �����ϴ�: " << std::endl;
			return false;
		}

		if (managerNode->first && managerNode->second)
		{
			std::cout << manager << " �Ʒ��� " << subordinate << "�� �߰��� �� �����ϴ�." << std::endl;
			return false;
		}

		if (!managerNode->first)
			managerNode->first = new node{ subordinate, NULL, NULL };
		else
			managerNode->second = new node{ subordinate, NULL, NULL };

		std::cout << manager << " �Ʒ��� " << subordinate << "�� �߰��߽��ϴ�." << std::endl;

		return true;
	}
};

int main()
{
	auto tree = org_tree::create_org_structure("CEO");

	tree.addSubordinate("CEO", "�λ���");
	tree.addSubordinate("�λ���", "IT����");
	tree.addSubordinate("�λ���", "�����ú���");
	tree.addSubordinate("IT����", "��������");
	tree.addSubordinate("IT����", "�۰�������");
	tree.addSubordinate("�����ú���", "��������");
	tree.addSubordinate("�����ú���", "ȫ������");
	tree.addSubordinate("�λ���", "�繫����");
}
