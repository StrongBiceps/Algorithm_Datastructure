#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//Object ��ü�� intŸ������ ���Կ� ���� ������ �����ϰ� �̷κ��� ���� ���Դ� ������ ���Ͽ� double Ÿ������ �����Ѵ�.
struct Object
{
public:
	int id;
	int weight;
	double value;
	double value_per_unit_weight;

	Object(int i, int w, double v) :id(i), weight(w), value(v), value_per_unit_weight(v / w) {}

	//std::sort()���� ���
	bool operator<(const Object& obj) const
	{
		return this->value_per_unit_weight < obj.value_per_unit_weight;
	}

	//�ش� �Լ��� �ܺ��Լ��̴�. Object�� ��� �Լ��� �ƴϴ�.
	//�ܺο��� �Լ��� �����ص� ������ Ŭ���� ���ο� �����ϰ� �Ǹ�
	//inline���� ����Ǿ� ª�� �Լ���� ������带 ���� �� �ִ�.
	friend ostream& operator<<(ostream& os, const Object& obj)
	{
		os << "[" << obj.id << "] ����: " << obj.value << "\t ����: " << obj.weight << "kg\t���� ���� �� ����: " << obj.value_per_unit_weight;
		return os;
	}
};

//���� ���� �賶 ������ �ַ���� ���ϴ� �Լ�
//�� �Լ������� ���� ���Դ� ������ �������� ���ǵ��� �������� ������ ��, �賶 �ִ� �뷮�� �� ������ ������ ä�� �ִ´�.
//���� �賶�� ���� ������ ���� ���� �賶 �ִ� ���Ը� �ʰ��� ��� �������� ���� ������ �Ϻθ� ����� �賶 �ִ� ���Կ� �µ���
//�����Ѵ�.
auto fill_knapsack(vector<Object>& objects, int knapsack_capacity)
{
	vector<Object> knapsack_contents;
	knapsack_contents.reserve(objects.size());

	//������ ������������ ����(���� ���� �� ���� ����)
	//sort�� �⺻������ ������������ ����������
	//reverse�� �������� �ٲ㼭 ������������ �����Ѵ�.
	sort(objects.begin(), objects.end());
	reverse(objects.begin(), objects.end());

	//���� ��ġ�ִ� ���ǵ� ���� �賶�� �߰�
	auto current_object = objects.begin();
	int current_total_weight = 0;
	while (current_total_weight < knapsack_capacity && current_object != objects.end())
	{
		knapsack_contents.push_back(*current_object);

		current_total_weight += current_object->weight;
		++current_object;
	}

	//������ �߰��� ���ǿ� ���� �賶 �ִ� ��� ���԰� �ʰ��� ���
	int weight_of_last_obj_to_remove = current_total_weight - knapsack_capacity;
	Object& last_object = knapsack_contents.back();

	if (weight_of_last_obj_to_remove > 0)
	{
		last_object.weight -= weight_of_last_obj_to_remove;
		last_object.value -= last_object.value_per_unit_weight * weight_of_last_obj_to_remove;
	}
	return knapsack_contents;
}

int main()
{
	vector<Object> objects;
	objects.reserve(7);

	vector<int> weights{1, 2, 5, 9, 2, 3, 4};
	vector<double> values{10, 7, 15, 10, 12, 11, 5};

	for (register int i = 0; i < 7; ++i)
	{
		objects.push_back(Object(i + 1, weights[i], values[i]));
	}

	//����� �� �ִ� ���� ���� ���
	cout << "[����� �� �ִ� ���� ����]" << endl;
	for (const auto& o : objects)
	{
		cout << o << endl;
	}
	cout << endl;

	//���� ���� �賶 ���� �˰��� ����, �賶�� �ִ� ��� ���Դ� 7�� ����
	int knapsack_capacity = 7;
	auto solution = fill_knapsack(objects,knapsack_capacity);

	//�賶�� ���� ���� ���� ���
	cout << "[�賶�� ���� ���ǵ� (�ִ� �뷮 = " << knapsack_capacity << ")]" << endl;
	for (const auto& o : solution)
	{
		cout << o << endl;
	}
	cout << endl;
}