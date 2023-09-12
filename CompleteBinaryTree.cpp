#include <iostream>
#include <vector>

//template<typename Elem>
//class Node
//{
//	Elem elt; //Element
//	Node* par; //parent Node
//	Node* left; //Left Node
//	Node* Right; //Right Node
//	Node() :elt(), par(NULL), left(NULL), Right(NULL) {} //constructor
//};
//
//template<typename E>
//class Position
//{
//private:
//	Node<E>* v;
//public:
//	Position(Node<E>* _v = NULL) :v(_v) {} //constructor
//	E& operator*()
//	{
//		return v -> elt; //���Ҹ� ��ȯ
//	}
//	Position left() const
//	{
//		return Position(v->left); //���� ����� Position�� ��ȯ
//	}
//	Position Right() const
//	{
//		return Position(v->Right); //������ ����� Positino�� ��ȯ
//	}
//	Position parent() const
//	{
//		return Position(v->par); //�θ� ����� Position�� ��ȯ
//	}
//	bool isRoot() const
//	{
//		return v->par == NULL; //�ش� ��尡 �θ� ������� Ȯ��(��Ʈ ���� �θ� ��尡 NULL)
//	}
//	bool isExternal() const
//	{
//		return v->left == NULL && v->Right == NULL; //�ܺ� ������� Ȯ��
//	}
//	friend class CompleteBinaryTree; //Ʈ���� ������ �� �ְ� �Ѵ�.
//};

//������ ���Ϳ� ������ ���̱� ������ Position ��ü�� ������� �ʰ� ���� �ݺ��ڸ� Positionó�� ����Ѵ�.
//���� �ܼ��� ���Ϳ� ���Ҹ� �����ϱ� ������ Node ��ü ���� ������� �ʴ´�.
//�ε��� 0�� ������� �ʱ� ������ �����ڿ��� ������ ũ�⸦ 1�� Ȯ���� ��
//push_back�ϸ� �ε��� 1���� ���Եȴ�.(ù ��° ������ ��Ʈ)

//const_iterator version
//template<typename E>
//class CompleteBinaryTree
//{
//private:
//	std::vector<E> V; //Ʈ�� ����
//public:
//	typedef typename std::vector<E>::const_iterator Position; // Ʈ�� ��ġ
////protected:
//	Position pos(int i) const// �ε����� ��ġ�� ����
//	{
//		return V.begin() + i;
//	}
//	int idx(const Position& p) const //��ġ�� �ε����� ����
//	{
//		return p - V.begin();
//	}
//public:
//	//Position<E> Pos;
//	//������ ũ�⸦ 1 Ȯ��
//	CompleteBinaryTree() :V(1) {}//constructor
//	int size() const
//	{
//		return V.size();
//	}
//	Position left(const Position& p) const
//	{
//		return pos(2 * idx(p));
//	}
//	Position Right(const Position& p) const
//	{
//		return pos(2 * idx(p) + 1);
//	}
//	Position parent(const Position& p) const
//	{
//		return pos(idx(p) / 2);
//	}
//	bool hasLeft(const Position& p) const
//	{
//		return 2 * idx(p) <= size();
//	}
//	bool hasRight(const Position& p) const
//	{
//		return 2 * idx(p) + 1 <= size();
//	}
//	bool isRoot(const Position& p) const
//	{
//		return idx(p) == 1;
//	}
//	Position root() const
//	{
//		return pos(1);
//	}
//	Position last() const
//	{
//		return pos(size());
//	}
//	void addLast(const E& e)
//	{
//		V.push_back(e);
//	}
//	void removeLast()
//	{
//		V.pop_back();
//	}
//	void swap(const Position& p, const Position& q)
//	{
//		E e = *q;
//		*q = *p;
//		*p = e;
//	}
//};

//Normal iterator version
template<typename E>
class CompleteBinaryTree
{
private:
	std::vector<E> V; //Ʈ�� ����
public:
	typedef typename std::vector<E>::iterator Position; // Ʈ�� ��ġ
//protected:
	//pos �Լ��� const�� �����ϸ� �ȵȴ�. �ϴ� Position�� ���� ������ iterator�̰�,
	//return�� ���� iterator�̴�. ���� const�Լ��� �����Ѵٸ� begin�� const_iterator�� �ǰ�
	//Position�� ���縦 �ؾ� �ϴµ� const_iterator�� iterator ���� ȣȯ�� ���� �ʱ� ������ ������ �߻��Ѵ�.
	
	//�̷��� ���� ������ pos�� non_const �Լ��� �����ߴ�. ���� right,left,parent�Լ��� const�� �����Ѵٸ�
	//non_const�Լ��� pos�� ȣ���� �� ��� ������ �߻��Ѵ�.
	Position pos(int i)// �ε����� ��ġ�� ����
	{
		return V.begin() + i;
	}
	int idx(const Position& p) const //��ġ�� �ε����� ����
	{
		//���⼭�� V.begin()�� const_iterator�� �Ǿ ��� ����. ��ȯ���� int���̱� ������
		//���糪 �̵��� �� �ʿ䰡 ��� ȣȯ ������ �Ű澲�� �ʾƵ� �ȴ�.
		return p - V.begin();
	}
public:
	//Position<E> Pos;
	//������ ũ�⸦ 1 Ȯ��
	CompleteBinaryTree() :V(1) {}//constructor
	int size() const
	{
		return V.size();
	}
	Position left(const Position& p)
	{
		return pos(2 * idx(p));
	}
	Position Right(const Position& p)
	{
		return pos(2 * idx(p) + 1);
	}
	Position parent(const Position& p)
	{
		return pos(idx(p) / 2);
	}
	bool hasLeft(const Position& p) const
	{
		return 2 * idx(p) <= size();
	}
	bool hasRight(const Position& p) const
	{
		return 2 * idx(p) + 1 <= size();
	}
	bool isRoot(const Position& p) const
	{
		return idx(p) == 1;
	}
	Position root()
	{
		return pos(1);
	}
	Position last()
	{
		return pos(size());
	}
	void addLast(const E& e)
	{
		V.push_back(e);
	}
	void removeLast()
	{
		V.pop_back();
	}
	void swap(const Position& p, const Position& q)
	{
		E e = *q;
		*q = *p;
		*p = e;
	}
};


int main()
{
	CompleteBinaryTree<int> CBT;
	std::cout << "10 �߰�" << std::endl;
	CBT.addLast(10);
	std::cout << "20 �߰�" << std::endl;
	CBT.addLast(20);
	std::cout << "30 �߰�" << std::endl;
	CBT.addLast(30);
	std::cout << "40 �߰�" << std::endl;
	CBT.addLast(40);

	std::cout << "��Ʈ ���: "<<*(CBT.root()) << std::endl;
	auto Pos1 = CBT.pos(1);
	std::cout << "1��° ���� ��Ʈ �ΰ�? : "<< CBT.isRoot(Pos1) << std::endl;

	std::cout << "1��° ���� ���� ��带 ������ �ִ°�?"<< CBT.hasLeft(Pos1) << std::endl;
	
	std::cout << "1��° ����� ���� ���: " << *(CBT.left(Pos1))<<std::endl;

	std::cout << "1��° ���� ������ ��带 ������ �ִ°�?"<< CBT.hasLeft(Pos1) << std::endl;
	CBT.hasRight(Pos1);
	std::cout << "1��° ����� ������ ���: " << *(CBT.Right(Pos1));
	return 0;
}