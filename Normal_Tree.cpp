#include <iostream>
#include <vector>
#include <stdio.h>
#include <memory>

using namespace std;

class Function;

//Function class�� ��� �ִ� class(���� ���)
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

//���� ������ ����
using PVariable = shared_ptr<Variable>;

//Ʈ���� ��忡 �ش�
//���� ������ Level�� ������ function�� ���ΰ� ���� �ʰ� Variable�� ���������� ����
class Function
{
public:
	//Variable�� �ּҸ� �����ϴ� ����
	vector<PVariable> v;

	PVariable forward(PVariable v1, PVariable v2)
	{
		//�� ��ü �� ���� ���Ϳ� �����Ѵ�.(�ڽ� 2���� �����)
		v.push_back(v1);
		v.push_back(v2);

		//���ο� variable ���� ������ ��ü�� �����Ѵ�.
		PVariable pv = PVariable(new Variable(0));
		//���ο� variable ��ü�� creator�� �ش� Function��ü�� ����
		//���� ������ variable ��ü�� �ش� Function��ü�� �����Ѵ�.(Function�� ���ΰ� �ִ� Variable)
		pv->creator = this;

		//���� ������ variable ��ü�� ���� �� �ڽ��� ���� ������ ����
		pv->a += v1->a;
		pv->a += v2->a;

		//���� ������ variable ��ü�� ��ȯ
		return pv;
	}
	PVariable forward(PVariable v1)
	{
		//�ϳ��� �ڽ��� �߰�
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
	//�ش� variable ��ü�� creator�� ���ٴ� ���� ������ Level�� �����̶�� ���̴�.
	if (f == NULL)return;

	//f3 -> f2 -> f1 -> v1 -> v2 ��� ����
	for (register int i = 0; i < f->v.size(); ++i)
	{
		traverse(f->v[i]);
	}
}

int main()
{
	/*
	*		v1    v2	//v1 v2�� Function�� ���ΰ� ���� �ʰ� variable��ü ���������� ����
	*		   f1		//f1��ü�� r1��ü�� ���ΰ� �ְ� v1,v2�� �ڽ����� �߰�
	*          f2       //f2��ü�� r1�� �ڽ����� �߰��ǰ� r2�� ���ΰ� �ִ�.
	*          f3       //f3��ü�� r2�� �ڽ����� �߰��ǰ� r3�� ���ΰ� �ִ�.
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