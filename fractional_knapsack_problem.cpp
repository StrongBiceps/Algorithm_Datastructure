#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

//Object 객체는 int타입으로 무게와 가격 정보를 저장하고 이로부터 단위 무게당 가격을 구하여 double 타입으로 저장한다.
struct Object
{
public:
	int id;
	int weight;
	double value;
	double value_per_unit_weight;

	Object(int i, int w, double v) :id(i), weight(w), value(v), value_per_unit_weight(v / w) {}

	//std::sort()에서 사용
	bool operator<(const Object& obj) const
	{
		return this->value_per_unit_weight < obj.value_per_unit_weight;
	}

	//해당 함수는 외부함수이다. Object의 멤버 함수가 아니다.
	//외부에서 함수를 정의해도 되지만 클래스 내부에 정의하게 되면
	//inline으로 선언되어 짧은 함수라면 오버헤드를 줄일 수 있다.
	friend ostream& operator<<(ostream& os, const Object& obj)
	{
		os << "[" << obj.id << "] 가격: " << obj.value << "\t 무게: " << obj.weight << "kg\t단위 무게 당 가격: " << obj.value_per_unit_weight;
		return os;
	}
};

//분할 가능 배낭 문제의 솔루션을 구하는 함수
//이 함수에서는 단위 무게당 가격을 기준으로 물건들을 내림차순 정렬한 후, 배낭 최대 용량이 될 때까지 물건을 채워 넣는다.
//만약 배낭에 넣은 물건의 무게 합이 배낭 최대 무게를 초과할 경우 마지막에 넣은 물건의 일부를 덜어내어 배낭 최대 무게에 맞도록
//설정한다.
auto fill_knapsack(vector<Object>& objects, int knapsack_capacity)
{
	vector<Object> knapsack_contents;
	knapsack_contents.reserve(objects.size());

	//물건을 내림차순으로 정렬(단위 무게 당 가격 기준)
	//sort는 기본적으로 오름차순으로 정렬하지만
	//reverse로 역순으로 바꿔서 내림차순으로 정렬한다.
	sort(objects.begin(), objects.end());
	reverse(objects.begin(), objects.end());

	//가장 가치있는 물건들 먼저 배낭에 추가
	auto current_object = objects.begin();
	int current_total_weight = 0;
	while (current_total_weight < knapsack_capacity && current_object != objects.end())
	{
		knapsack_contents.push_back(*current_object);

		current_total_weight += current_object->weight;
		++current_object;
	}

	//마지막 추가한 물건에 의해 배낭 최대 허용 무게가 초과된 경우
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

	//사용할 수 있는 물건 정보 출력
	cout << "[사용할 수 있는 물건 정보]" << endl;
	for (const auto& o : objects)
	{
		cout << o << endl;
	}
	cout << endl;

	//분할 가능 배낭 문제 알고리즘 실행, 배낭의 최대 허용 무게는 7로 설정
	int knapsack_capacity = 7;
	auto solution = fill_knapsack(objects,knapsack_capacity);

	//배낭에 넣은 물건 정보 출력
	cout << "[배낭에 넣은 물건들 (최대 용량 = " << knapsack_capacity << ")]" << endl;
	for (const auto& o : solution)
	{
		cout << o << endl;
	}
	cout << endl;
}