#include <iostream>
#include <list>
using namespace std;
int main()
{
	//초깃값을 갖는 리스트를 생성하고, 새로운 원소를 몇 개 추가한다.
	list<int> list1 = { 1,2,3,4,5 };
	list1.push_back(6); //{1,2,3,4,5,6}
	list1.insert(next(list1.begin()), 0); //{1,0,2,3,4,5,6}
	list1.insert(list1.end(), 7); //{1,0,2,3,4,5,6,7}

	//이 코드에서는 push_back()함수를 이용하여 리스트 맨 뒤에 6을 삽입했다.
	//그 다음 라인에서는 insert()함수와 next()코드를 이용하여 리스트 맨 처음 원소 다	//음 위치에 0을 삽입했다. 마지막 줄에서는 list1.end()코드를 이용하여 리스트 맨 	//뒤에 7을 추가했다.
	//이번에는 pop_back()함수를 이용하여 리스트 맨 뒤 원소를 제거한다.
	list1.pop_back(); //{1,0,2,3,4,5,6}
	cout << "삽입 & 삭제 후 리스트 : ";
	for (auto i : list1)
		cout << i << " ";
}
//지금까지 작성한 프로그램을 실행하면 다음과 같은 결과가 나타난다.
//삽입& 삭제 후 리스트 : 1 0 2 3 4 5 6
//이중 연결 리스트는 포인터가 두 개이므로 forward_list보다 연산이 두 배 더 필요하다.
//remove(), remove_if(), sort(), unique(), reverse() 등의 함수도 list에서 제공되며, forward_list와 같은 형태로 동작한다.