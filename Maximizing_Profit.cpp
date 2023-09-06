#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

//각 상품 정보를 표현할 Product 구조체를 정의한다.
struct Product
{
	//수량
	int quantity;
	//가격
	int price;
	//이익
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

	//0-1배낭 문제와는 다르게 DP차원이 3차원이 된다. 각 상태에서 고려해야 할 값이 3개이기 때문이다.
	
	//0-1배낭 문제와 비슷하게 각 아이템에 대해서 모든 cost와 count에 대해 검사를 진행하면서 만들 수 있는
	//경우에 대해서만 0이 아닌 값으로 테이블이 업데이트된다.
	vector<vector<vector<int>>> DP(N + 1, vector<vector<int>>(budget + 1, vector<int>(capacity + 1, 0)));

	for (int i = 1; i <= N; i++)
	{
		Product product = products[i - 1];

		for (int cost = 0; cost <= budget; cost++)
		{
			for (int count = 0; count <= capacity; count++)
			{
				//수량과 가격이 현재 고려하는 아이템의 값보다 커야 현재 아이템이 추가되었을 경우를 생각할 수 있다.
				//둘 중 하나라도 현재 아이템의 값에 미치지 못한다면 현재 아이템이 추가되었을 거라고 생각할 수 없다.
				//만약 현재 아이템이 하나라도 추가되었다면 두 값이 모두 현재 아이템 값보다 커야 정상이기 때문이다.

				//예를 들어 이러한 상황이 있을 수 있다. 이전 아이템의 수량이 10이고 가격이 5일 때 
				//현재 아이템의 수량이 5이고 가격이 15이라고 해보자. 그럼 cost와 count값이 각각 15 14라고 하면
				//수량은 두 아이템이 모두 가방에 있을 때와 같지만, 가격은 같지 않다.따라서 이전 아이템까지만 고려한 결과가
				//저장되어야 한다.
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
