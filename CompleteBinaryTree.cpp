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
//		return v -> elt; //원소를 반환
//	}
//	Position left() const
//	{
//		return Position(v->left); //왼쪽 노드의 Position을 반환
//	}
//	Position Right() const
//	{
//		return Position(v->Right); //오른쪽 노드의 Positino을 반환
//	}
//	Position parent() const
//	{
//		return Position(v->par); //부모 노드의 Position을 반환
//	}
//	bool isRoot() const
//	{
//		return v->par == NULL; //해당 노드가 부모 노드인지 확인(루트 노드는 부모 노드가 NULL)
//	}
//	bool isExternal() const
//	{
//		return v->left == NULL && v->Right == NULL; //외부 노드인지 확인
//	}
//	friend class CompleteBinaryTree; //트리에 접근할 수 있게 한다.
//};

//노드들을 벡터에 저장할 것이기 때문에 Position 객체를 사용하지 않고 벡터 반복자를 Position처럼 사용한다.
//또한 단순히 벡터에 원소를 저장하기 때문에 Node 객체 또한 사용하지 않는다.
//인덱스 0은 사용하지 않기 때문에 생성자에서 벡터의 크기를 1로 확보한 후
//push_back하면 인덱스 1부터 삽입된다.(첫 번째 삽입이 루트)

//const_iterator version
//template<typename E>
//class CompleteBinaryTree
//{
//private:
//	std::vector<E> V; //트리 내용
//public:
//	typedef typename std::vector<E>::const_iterator Position; // 트리 위치
////protected:
//	Position pos(int i) const// 인덱스를 위치로 매핑
//	{
//		return V.begin() + i;
//	}
//	int idx(const Position& p) const //위치를 인덱스로 매핑
//	{
//		return p - V.begin();
//	}
//public:
//	//Position<E> Pos;
//	//벡터의 크기를 1 확보
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
	std::vector<E> V; //트리 내용
public:
	typedef typename std::vector<E>::iterator Position; // 트리 위치
//protected:
	//pos 함수를 const로 정의하면 안된다. 일단 Position이 쓰기 가능한 iterator이고,
	//return값 또한 iterator이다. 만약 const함수로 정의한다면 begin은 const_iterator가 되고
	//Position에 복사를 해야 하는데 const_iterator와 iterator 끼리 호환이 되지 않기 때문에 오류가 발생한다.
	
	//이러한 이유 때문에 pos를 non_const 함수로 정의했다. 만약 right,left,parent함수를 const로 선언한다면
	//non_const함수인 pos를 호출할 수 없어서 오류가 발생한다.
	Position pos(int i)// 인덱스를 위치로 매핑
	{
		return V.begin() + i;
	}
	int idx(const Position& p) const //위치를 인덱스로 매핑
	{
		//여기서는 V.begin()이 const_iterator가 되어도 상관 없다. 반환값이 int형이기 때문에
		//복사나 이동을 할 필요가 없어서 호환 문제를 신경쓰지 않아도 된다.
		return p - V.begin();
	}
public:
	//Position<E> Pos;
	//벡터의 크기를 1 확보
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
	std::cout << "10 추가" << std::endl;
	CBT.addLast(10);
	std::cout << "20 추가" << std::endl;
	CBT.addLast(20);
	std::cout << "30 추가" << std::endl;
	CBT.addLast(30);
	std::cout << "40 추가" << std::endl;
	CBT.addLast(40);

	std::cout << "루트 노드: "<<*(CBT.root()) << std::endl;
	auto Pos1 = CBT.pos(1);
	std::cout << "1번째 노드는 루트 인가? : "<< CBT.isRoot(Pos1) << std::endl;

	std::cout << "1번째 노드는 왼쪽 노드를 가지고 있는가?"<< CBT.hasLeft(Pos1) << std::endl;
	
	std::cout << "1번째 노드의 왼쪽 노드: " << *(CBT.left(Pos1))<<std::endl;

	std::cout << "1번째 노드는 오른쪽 노드를 가지고 있는가?"<< CBT.hasLeft(Pos1) << std::endl;
	CBT.hasRight(Pos1);
	std::cout << "1번째 노드의 오른쪽 노드: " << *(CBT.Right(Pos1));
	return 0;
}