#include <iostream>
#include <vector>
#include <stdio.h>
#include <memory>

using namespace std;

class Function;

//Function class가 담고 있는 class(값을 담당)
class Variable
{
public:
	float a = 0;

	Function* creator = NULL;

	Variable(float a)
	{
		this->a=a;
	}
};

//공유 포인터 선언
using PVariable = shared_ptr<Variable>;

//트리의 노드에 해당
//가장 마지막 Level의 노드들은 function이 감싸고 있지 않고 Variable만 독립적으로 존재
class Function
{
public:
	//Variable의 주소를 저장하는 벡터
	vector<PVariable> v;

	PVariable forward(PVariable v1, PVariable v2)
	{
		//값 객체 두 개를 벡터에 저장한다.(자식 2개가 생긴다)
		v.push_back(v1);
		v.push_back(v2);

		//새로운 variable 공유 포인터 객체를 선언한다.
		PVariable pv = PVariable(new Variable(0));
		//새로운 variable 객체의 creator를 해당 Function객체로 정의
		//새로 생성된 variable 객체는 해당 Function객체가 소유한다.(Function이 감싸고 있는 Variable)
		pv->creator = this;

		//새로 생성된 variable 객체의 값은 두 자식의 값의 합으로 정의
		pv->a += v1->a;
		pv->a += v2->a;

		//새로 생성된 variable 객체를 반환
		return pv;
	}
	PVariable forward(PVariable v1)
	{
		//하나의 자식을 추가
		v.push_back(v1);

		PVariable pv = PVariable(new Variable(0));
		pv->creator = this;

		pv->a += v1->a;

		return pv;
	}
};

void traverse(PVariable v)
{
	cout << v->a << endl;

	Function* f = v->creator;
	//해당 variable 객체의 creator가 없다는 말은 마지막 Level의 노드들이라는 것이다.
	if (f == NULL)return;

	//f3 -> f2 -> f1 -> v1 -> v2 재귀 순서
	for (register int i = 0; i < f->v.size(); ++i)
	{
		traverse(f->v[i]);
	}
}

int main()
{
	/*
	*		v1    v2	//v1 v2는 Function이 감싸고 있지 않고 variable객체 독립적으로 존재
	*		   f1		//f1객체는 r1객체를 감싸고 있고 v1,v2가 자식으로 추가
	*          f2       //f2객체는 r1이 자식으로 추가되고 r2를 감싸고 있다.
	*          f3       //f3객체는 r2가 자식으로 추가되고 r3를 감싸고 있다.
	*/
	PVariable v1 = PVariable(new Variable(1));
	PVariable v2 = PVariable(new Variable(1));
	Function* f1 = new Function();
	Function* f2 = new Function();
	Function* f3 = new Function();

	PVariable r1 = f1->forward(v1, v2);
	PVariable r2= f2->forward(r1);
	PVariable r3 = f3->forward(r2);

	traverse(r3);

	return 0;

}