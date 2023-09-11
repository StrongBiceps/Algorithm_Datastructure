#include <string>
#include <iostream>
#include <forward_list>

/*
main함수를 작성하고, forward_list를 사용하여 몇몇 시민 정보를 초기화한다.
나중에 다시 초기화하는 것을 피하기 위해 복사본을 만들어 둔다. 
또한 나이 정보를 이용하여 투표권이 없는 시민을 리스트에서 제거한다.
remove_if()함수는 주어진 조건에 대해 참을 만족하는 원소를 모두 제거한다.
이 예제에서는 조건이 간단하므로 람다 표현식을 사용한다. 
복잡한 조건이라면 리스트에 저장된 원소를 인자로 받아서 bool값을 반환하는 일반 함수를 사용해도 된다.
또한 내년에 새로 투표권이 생기는 사람을 알아본다.
*/
struct citizen
{
	std::string name;
	int age;
};

std::ostream& operator<<(std::ostream& os, const citizen& c)
{
	return (os << "[" << c.name << ", " << c.age << "]");
}

int main()
{
	std::forward_list<citizen> citizens = {
		{"Kim", 22}, {"Lee", 25}, {"Park", 18}, {"Jin", 16}
	};

	auto citizens_copy = citizens; // 깊은 복사

	std::cout << "전체 시민: ";
	for (const auto& c : citizens)
		std::cout << c << " ";
	std::cout << std::endl;

	citizens.remove_if([](const citizen& c) {
		// 나이가 19세보다 작으면 리스트에서 제거합니다.
		return (c.age < 19);
		});

	std::cout << "투표권이 있는 시민: ";
	for (const auto& c : citizens)
		std::cout << c << " ";
	std::cout << std::endl;

	citizens_copy.remove_if([](const citizen& c) {
		return (c.age != 18);
		});

	std::cout << "내년에 투표권이 생기는 시민: ";
	for (const auto& c : citizens_copy)
		std::cout << c << " ";
	std::cout << std::endl;
}
