#include <iostream>
#include <vector>
using namespace std;

template<typename E>
class CompleteBinaryTree
{
private:
	std::vector<E> V; //Ʈ�� ����
public:
	typedef typename std::vector<E>::iterator Position; // Ʈ�� ��ġ
	Position pos(int i)// �ε����� ��ġ�� ����
	{
		return V.begin() + i;
	}
	int idx(const Position& p) const //��ġ�� �ε����� ����
	{
		return p - V.begin();
	}
public:
	//Position<E> Pos;
	//������ ũ�⸦ 1 Ȯ��
	CompleteBinaryTree() :V(1) {}//constructor
	int size() const
	{
		return V.size()-1;
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

template<typename E,typename C>
class HeapPriorityQueue
{
public:
	int size() const //������ ����
	{
		return T.size();
	}
	bool empty() const //ť�� �����?
	{
		return T.size() == 0;
	}
	void insert(const E& e); //���� ����
	const E& min() //�ּ� ����
	{
		return *(T.root()); //��Ʈ�� ���� ���۷����� ��ȯ
	}
	void removeMin(); //�ּҰ� ����
private:
	CompleteBinaryTree<E> T; //�켱���� ť�� ����
	C isLess; //less-than ����

	typedef typename CompleteBinaryTree<E>::Position Position; //Ʈ�� ��ġ�� ���� ����
};

//up-heap bubbling
template<typename E, typename C>
void HeapPriorityQueue<E, C>::insert(const E& e)
{
	//e�� ���� �߰�
	T.addLast(e);
	//e�� ��ġ
	Position v = T.last();
	
	//��-�� ����
	while (!T.isRoot(v)) //��Ʈ���� �����ϸ� ����
	{
		Position u = T.parent(v);

		//��-���� Ư���� �����Ǹ� ���� ����
		if (!isLess(*v, *u))
			break;

		T.swap(v, u);

		//��ġ �� ���� �� �� ���� ��ȯ
		v = u;
	}
}

//���� Ʈ���� �ϳ��� ��常 �����ٸ� �ܼ��� �� ��带 �����Ѵ�. �׷��� ������, ��Ʈ�� ���Ҹ� Ʈ���� ������ ���ҿ� ��ȯ ��
//������ ���Ҹ� �����Ѵ�. �׷� ����, ��Ʈ���� �ٿ�-�� ������ �����Ѵ�. ���� ��带 u�� �Ҷ�, u�� �� ���� �ڽ��� v�� �ȴ�.
//���� v�� Ű�� u�� Ű���� ������ u�� v�� ���ҵ��� ���� ��ȯ�Ѵ�.
template<typename E, typename C>
void HeapPriorityQueue<E, C>::removeMin()
{
	if (size() == 1) //��尡 �ϳ� ���̸� �ش� ��带 �����Ѵ�.
	{
		T.removeLast();
	}
	else
	{
		Position u = T.root(); //��Ʈ�� ��ġ

		T.swap(u, T.last()); //��Ʈ�� ������ ��带 ��ȯ

		T.removeLast(); // ������ ��带 ����

		//���� ���� ���� Ʈ���̰�, ���� �ڽ��� ������ �ڽ��� ��� ���� ���̴�.
		while (T.hasLeft(u)) //�ٿ� �� ����
		{
			Position v = T.left(u);

			//��� ���� �� ���� ���� ��尡 root�� ���� �ϱ� ������ �� �ڽ��� ���� ���Ѵ�.
			if (T.hasRight(u) && isLess(*(T.Right(u)), *v))
			{
				//���� ���� ��庸�� ������ ��尡 �� ������ ������ ��带 ����
				v = T.Right(u);
			}
			if (isLess(*v, *u))
			{
				//���� ���� root���� �ڽ��� �� ������ ��ȯ
				T.swap(u, v);

				u = v;
			}
			//���� �ڽĺ��� root�� �� �۴ٸ� break;
			else
				break;
		}
	}
}

int main()
{
	HeapPriorityQueue<int,std::less<int>> HQ;

	HQ.insert(10);
	HQ.insert(20);
	HQ.insert(5);
	HQ.insert(4);
	HQ.insert(30);

	cout << HQ.min() << endl;
}