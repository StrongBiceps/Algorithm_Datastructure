#include <iostream>
#include <vector>

class bloom_filter
{
	std::vector<bool> data;
	int nBits;
	
	//삽입의 경우에는 3가지의 해싱 방법을 사용한다.
	int hash(int num, int key)
	{
		switch (num)
		{
		case 0: return key % nBits;
		case 1: return (key / 7) % nBits;
		case 2: return (key / 11) % nBits;
		}

		return 0;
	}

public:
	bloom_filter(int n) : nBits(n)
	{
		data = std::vector<bool>(nBits, false);
	}
	/*
	* lookup함수 구현은 매우 간단하다. 이 함수는 필요한 모든 비트가 1로 설정되어 있는지를 검사한다.
	만약 가변 개수의 해시 함수를 사용한다면, 각각의 해시 함수와 연관된 비트가 모두 1로 설정되어
	있는지를 반복문을 통해서 확인하면 된다. 특정 키가 있을 수 있음이라고 출력하는
	이유는 거짓-긍정이 발생할 수 있기 때문이다. 반면에 result값이 0인 경우에는 입력 키가
	없음이 확실하기 때문에 절대 없음을 출력한다.
	*/
	void lookup(int key)
	{
		bool result = data[hash(0, key)] & data[hash(1, key)] & data[hash(2, key)];

		if (result)
		{
			std::cout << key << ": 있을 수 있음" << std::endl;
		}
		else
		{
			std::cout << key << ": 절대 없음" << std::endl;
		}
	}

	void insert(int key)
	{
		data[hash(0, key)] = true;
		data[hash(1, key)] = true;
		data[hash(2, key)] = true;
		std::cout << key << "을(를) 삽입: ";

		for (auto a : data)
			std::cout << a << " ";
		std::cout << std::endl;
	}
};

int main()
{
	bloom_filter bf(7);
	bf.insert(100);
	bf.insert(54);
	bf.insert(82);

	bf.lookup(5);
	bf.lookup(50);
	bf.lookup(20);
	bf.lookup(54);
}
