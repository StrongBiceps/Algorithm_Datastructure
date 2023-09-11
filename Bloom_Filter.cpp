#include <iostream>
#include <vector>

class bloom_filter
{
	std::vector<bool> data;
	int nBits;
	
	//������ ��쿡�� 3������ �ؽ� ����� ����Ѵ�.
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
	* lookup�Լ� ������ �ſ� �����ϴ�. �� �Լ��� �ʿ��� ��� ��Ʈ�� 1�� �����Ǿ� �ִ����� �˻��Ѵ�.
	���� ���� ������ �ؽ� �Լ��� ����Ѵٸ�, ������ �ؽ� �Լ��� ������ ��Ʈ�� ��� 1�� �����Ǿ�
	�ִ����� �ݺ����� ���ؼ� Ȯ���ϸ� �ȴ�. Ư�� Ű�� ���� �� �����̶�� ����ϴ�
	������ ����-������ �߻��� �� �ֱ� �����̴�. �ݸ鿡 result���� 0�� ��쿡�� �Է� Ű��
	������ Ȯ���ϱ� ������ ���� ������ ����Ѵ�.
	*/
	void lookup(int key)
	{
		bool result = data[hash(0, key)] & data[hash(1, key)] & data[hash(2, key)];

		if (result)
		{
			std::cout << key << ": ���� �� ����" << std::endl;
		}
		else
		{
			std::cout << key << ": ���� ����" << std::endl;
		}
	}

	void insert(int key)
	{
		data[hash(0, key)] = true;
		data[hash(1, key)] = true;
		data[hash(2, key)] = true;
		std::cout << key << "��(��) ����: ";

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
