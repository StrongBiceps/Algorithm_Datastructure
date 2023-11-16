#include <iostream>
#include <vector>
#include <list>
using namespace std;

//�̱������� ������ �ڵ�� ���� ������ �켱���� ť �ڵ�� ����ϴ�.

template<typename E,typename C>
class AdaptPriorityQueue
{
protected:
	typedef list<E> ElementList; //���ҵ��� ����Ʈ
public:

public:
	int size() const; //������ ����
	bool empty() const; //ť�� �����?
	const E& min() const; //�ּ� ����
	Position insert(const E& e); //���� ����
	void removeMin(); //�ּ� ���� ����
	void remove(const Position& p); //��ġ p�� ���� ����
	Position replace(const Position& p, const E& e); //��ġ p�� ���� ��ü
private:
	ElementList L; //�켱���� ť ����
	C isLess; //less than ����
};

//�־��� Ű ���� �ʰ��ϴ� Ű�� ���� ù ��° ��Ʈ�� p�� ã�� ���� �� ��Ʈ���� �ٷ� �տ� e�� �����Ѵ�. p �ٷ� �տ� ���Ե� �� ��Ʈ���� ����Ű��
//��ġ�� �����Ͽ� ��ȯ�Ѵ�.
template<typename E, typename C>
Position AdaptPriorityQueue<E, C>::insert(const E& e)
{
	auto p = L.begin();

	while (p != L.end() && !isLess(e, *p)) ++p; //Ű ���� e���� �� ū ���Ҹ� Ž��

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




