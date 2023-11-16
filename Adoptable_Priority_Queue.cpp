#include <iostream>
#include <vector>
#include <list>
using namespace std;

//미구현으로 남겨진 코드는 먼저 구현한 우선순위 큐 코드와 비슷하다.

template<typename E,typename C>
class AdaptPriorityQueue
{
protected:
	typedef list<E> ElementList; //원소들의 리스트
public:

public:
	int size() const; //원소의 개수
	bool empty() const; //큐가 비었나?
	const E& min() const; //최소 원소
	Position insert(const E& e); //원소 삽입
	void removeMin(); //최소 원소 삭제
	void remove(const Position& p); //위치 p의 원소 삭제
	Position replace(const Position& p, const E& e); //위치 p의 원소 교체
private:
	ElementList L; //우선순위 큐 내용
	C isLess; //less than 비교자
};

//주어진 키 값을 초과하는 키를 가진 첫 번째 엔트리 p를 찾은 다음 이 엔트리의 바로 앞에 e를 삽입한다. p 바로 앞에 삽입된 이 엔트리를 가리키는
//위치를 생성하여 반환한다.
template<typename E, typename C>
Position AdaptPriorityQueue<E, C>::insert(const E& e)
{
	auto p = L.begin();

	while (p != L.end() && !isLess(e, *p)) ++p; //키 값인 e보다 더 큰 원소를 탐색

	L.insert(p, e);

	Position pos;
	pos.q = --p;

	return pos;
}

template<typename E, typename C>
void AdaptPriorityQueue<E, C>::remove(const Position& p)
{
	L.erase(p.q);
}

template<typename E, typename C>
Position AdaptPriorityQueue<E, C>::replace(const Position& p, const E& e)
{
	L.erase(p.q);
	return insert(e);
}




