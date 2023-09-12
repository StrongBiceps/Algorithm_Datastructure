#include <iostream>
#include <vector>
using namespace std;

template<typename E>
class CompleteBinaryTree
{
private:
	std::vector<E> V; //트리 내용
public:
	typedef typename std::vector<E>::iterator Position; // 트리 위치
	Position pos(int i)// 인덱스를 위치로 매핑
	{
		return V.begin() + i;
	}
	int idx(const Position& p) const //위치를 인덱스로 매핑
	{
		return p - V.begin();
	}
public:
	//Position<E> Pos;
	//벡터의 크기를 1 확보
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
	int size() const //원소의 개수
	{
		return T.size();
	}
	bool empty() const //큐가 비었나?
	{
		return T.size() == 0;
	}
	void insert(const E& e); //원소 삽입
	const E& min() //최소 원소
	{
		return *(T.root()); //루트에 대한 레퍼런스를 반환
	}
	void removeMin(); //최소값 삭제
private:
	CompleteBinaryTree<E> T; //우선순위 큐의 내용
	C isLess; //less-than 비교자

	typedef typename CompleteBinaryTree<E>::Position Position; //트리 위치에 대한 정의
};

//up-heap bubbling
template<typename E, typename C>
void HeapPriorityQueue<E, C>::insert(const E& e)
{
	//e를 힙에 추가
	T.addLast(e);
	//e의 위치
	Position v = T.last();
	
	//업-힙 버블링
	while (!T.isRoot(v)) //루트까지 도달하면 종료
	{
		Position u = T.parent(v);

		//힙-순서 특성이 만족되면 루프 종료
		if (!isLess(*v, *u))
			break;

		T.swap(v, u);

		//위치 값 또한 한 층 위로 교환
		v = u;
	}
}

//만약 트리가 하나의 노드만 가진다면 단순히 그 노드를 제거한다. 그렇지 않으면, 루트의 원소를 트리의 마지막 원소와 교환 후
//마지막 원소를 제거한다. 그런 다음, 루트부터 다운-힙 버블링을 실행한다. 현재 노드를 u라 할때, u의 더 작은 자식은 v가 된다.
//만약 v의 키가 u의 키보다 작으면 u와 v의 원소들을 서로 교환한다.
template<typename E, typename C>
void HeapPriorityQueue<E, C>::removeMin()
{
	if (size() == 1) //노드가 하나 뿐이면 해당 노드를 삭제한다.
	{
		T.removeLast();
	}
	else
	{
		Position u = T.root(); //루트의 위치

		T.swap(u, T.last()); //루트와 마지막 노드를 교환

		T.removeLast(); // 마지막 노드를 삭제

		//힙은 완전 이진 트리이고, 왼쪽 자식이 없으면 자식이 모두 없는 것이다.
		while (T.hasLeft(u)) //다운 힙 버블링
		{
			Position v = T.left(u);

			//모든 노드들 중 가장 작은 노드가 root로 가야 하기 때문에 두 자식의 값을 비교한다.
			if (T.hasRight(u) && isLess(*(T.Right(u)), *v))
			{
				//만약 왼쪽 노드보다 오른쪽 노드가 더 작으면 오른쪽 노드를 선택
				v = T.Right(u);
			}
			if (isLess(*v, *u))
			{
				//만약 현재 root보다 자식이 더 작으면 교환
				T.swap(u, v);

				u = v;
			}
			//만약 자식보다 root가 더 작다면 break;
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