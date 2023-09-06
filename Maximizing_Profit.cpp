#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

//�� ��ǰ ������ ǥ���� Product ����ü�� �����Ѵ�.
struct Product
{
	//����
	int quantity;
	//����
	int price;
	//����
	int value;

	Product(int q, int c, int v)
		: quantity(q), price(c), value(v) {}
};

int main()
{
	int N, budget, capacity;
	cin >> N >> budget >> capacity;

	vector<Product> products;

	for (int i = 0; i < N; i++)
	{
		int quantity, cost, value;
		cin >> quantity >> cost >> value;

		products.push_back(Product(quantity, cost, value));
	}

	//0-1�賶 �����ʹ� �ٸ��� DP������ 3������ �ȴ�. �� ���¿��� ����ؾ� �� ���� 3���̱� �����̴�.
	
	//0-1�賶 ������ ����ϰ� �� �����ۿ� ���ؼ� ��� cost�� count�� ���� �˻縦 �����ϸ鼭 ���� �� �ִ�
	//��쿡 ���ؼ��� 0�� �ƴ� ������ ���̺��� ������Ʈ�ȴ�.
	vector<vector<vector<int>>> DP(N + 1, vector<vector<int>>(budget + 1, vector<int>(capacity + 1, 0)));

	for (int i = 1; i <= N; i++)
	{
		Product product = products[i - 1];

		for (int cost = 0; cost <= budget; cost++)
		{
			for (int count = 0; count <= capacity; count++)
			{
				//������ ������ ���� ����ϴ� �������� ������ Ŀ�� ���� �������� �߰��Ǿ��� ��츦 ������ �� �ִ�.
				//�� �� �ϳ��� ���� �������� ���� ��ġ�� ���Ѵٸ� ���� �������� �߰��Ǿ��� �Ŷ�� ������ �� ����.
				//���� ���� �������� �ϳ��� �߰��Ǿ��ٸ� �� ���� ��� ���� ������ ������ Ŀ�� �����̱� �����̴�.

				//���� ��� �̷��� ��Ȳ�� ���� �� �ִ�. ���� �������� ������ 10�̰� ������ 5�� �� 
				//���� �������� ������ 5�̰� ������ 15�̶�� �غ���. �׷� cost�� count���� ���� 15 14��� �ϸ�
				//������ �� �������� ��� ���濡 ���� ���� ������, ������ ���� �ʴ�.���� ���� �����۱����� ����� �����
				//����Ǿ�� �Ѵ�.
				if (cost < product.price || count < product.quantity)
				{
					auto temp = DP[i][cost][count];
					DP[i][cost][count] = DP[i - 1][cost][count];

					cout << "if checked" << endl;
					cout << "Product: " << i << " cost: " << cost << " count: " << count << endl;
					cout << "DP[" << i << "][" << cost << "][" << count << "](" << temp << ") = DP[" << i - 1 << "][" << cost << "][" << count << "](" <<
							DP[i - 1][cost][count] << ") : " << DP[i][cost][count] << endl;
					cout << endl;
					
				}
				else
				{

					auto temp = DP[i][cost][count];

					DP[i][cost][count] = max(DP[i - 1][cost][count],
						DP[i - 1][cost - product.price][count - product.quantity] + product.value);

					cout << "else checked" << endl;
					cout << "Product: " << i << " cost: " << cost << " count: " << count << endl;

					cout << "DP[" << i << "][" << cost << "][" << count << "](" << temp << ") "<<endl<<"= max(DP[" << i - 1 << "][" << cost << "][" << count << "](" <<
							DP[i - 1][cost][count] << ") , DP[" << i - 1 << "][" << cost  - product.price << "][" << count  - product.quantity << "]("
							<< DP[i - 1][cost - product.price][count - product.quantity] << " + " << product.value << endl;
					cout << endl;
					
				}
			}
		}
	}

	cout << DP[N][budget][capacity] << endl;
}

/*
5 30 25
6 11 56
13 34 36
11 27 31
9 31 55
11 17 46
-> 102
*/
