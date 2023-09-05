#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
* ������ ����
3

���� 
8 4 10

����
10 20 11

���� �ִ� ����
18


<i = 1 �� ��>

cw = 8
cv = 10

*totalw = 7 ������ totalw < currentw �̰�
DP[0][0~7] = 0�̹Ƿ� 

DP[1][0~7] = DP[i-1][0~7] = 0

-���ݱ����� ���������δ� ���� �� ���� ���Ե��̴�.


*total = 8�� ��

DP[1][8] = max(DP[0][8],DP[0][0]+cv) 
	 = 10

-ù ��° �������� �߰����� ����̴�.


*total = 9 ���ĺ��ʹ� ������ �� ���� �������� ������ �����ȴ�.

DP[1][9~18] = max(DP[0][9~18],DP[0][1~10]+cv)
���� 10���� �����ȴ�.

-�� ���Ե��� ù ��° �����۸� ������� ��쿡�� ù ��° �����۸����� ä������ ���Ե��̴�.
�� ���濡 ������ ��ǰ�� ���� ������� ä���� ���ϴ� ���Ե��� ������ ������ ��ǰ���� �ִ�� ä���� �����
�������� ������Ʈ �Ǵ� �ǹ��̴�.

<i = 2�� ��>

cw = 4
cv = 20

*totalw = 3������ totalw < currentw �̰�
DP[1][0~3] = 0�̹Ƿ� 

DP[2][0~3] = DP[1][0~3]
	   = 0

-�� ��° �����۱��� ������� ��쿡�� ���� �� ���� ���Ե��̴�.


*totalw=4 �� ��

DP[2][4] = max(DP[1][4],DP[1][0]+cv)
	=20

-�� ��° �����۱��� ������� ��� �� ��° �������� �߰����� �ʾ��� ���� �߰����� ��츦 ���Ѵ�.


*totalw=5~7 ������ ������ �� ���� �����̰�
DP[1][5~7] = 0�̴�. �� DP[1][5~7 - 4 = 1~3]+cv -> DP[1][1~3]+cv�̹Ƿ� ���̺��� 20���� ������Ʈ�� ���̴�.

DP[2][5~7] = 20

*totalw=8 �� ��

DP[2][8] = max(DP[1][8],DP[1][4]+cv)
	=20


*totalw=9~11 ������ ������ �� ���� �����̴�.
DP[2][9~11] = max(DP[1][9~11],DP[1][5~7]+cv) 

DP[2][9~11] =max(10,20)
	   =20


*totalw=12 �� ��

DP[2][12] = max(DP[1][12],DP[1][8]+cv)
	  = 30


*totalw = 13���ʹ� ������ �� ���� �����̴�.

DP[2][13~18] = max(DP[1][13~18],DP[1][9~14]+cv)
	    =max(10,30)

DP[2][13~18] = 30


<i = 3�� ��>

cw = 10
cv = 11

*totalw = 9������ DP[2][0~9]�� ����� ���̴�.

DP[3][0~9] = DP[2][0~9]

DP[3][4] = DP[2][4]
	 = 20

DP[3][8] = DP[2][8]
	 = 20


*totalw = 10�� ��

DP[3][10] = max(DP[2][10],DP[2][0]+cv)
	  = 20


*totalw = 11 ~ 13 

DP[3][11~13] = max(DP[2][11~13],DP[2][1~3]+cv)

DP[3][11] = max(DP[2][11],DP[2][1]+cv)
	  = max(20,11)
	  = 20

DP[3][12] = max(DP[2][12],DP[2][2]+cv)
	  = max(30,11)
	  = 30

DP[3][13] = max(DP[2][13],DP[2][3]+cv)
	  = max(30,11)
	  = 30

DP[3][14] = max(DP[2][14],DP[2][4]+cv)
	  = max(30,31)
	  = 31

DP[3][15] ~ DP[3][18] ������ 31�� �����ȴ�.


�� �ڵ带 �м��غ��� �� �������� ������� ��쿡�� ��� ���Կ� ���ؼ� ���̺� ������Ʈ�Ѵ�. ���� ���� ��
���� �����̰ų� ���濡 ������� ä���� ���ϴ� ���Կ� ���ؼ��� 0�� ��������� �ִ� ���Է� ������Ʈ�ȴ�.
�� �� ���Կ� ���ؼ� ���� �����ۺ��� ū total ���Կ� ���ؼ��� ���� �������� �߰��� ���� �߰����� ����
��츦 ���Ͽ� ū ���� �����Ѵ�. ���δ� ���������� ��ǰ��� ������ ������ ���� ��ǰ�� �߰��� ���ݺ���
Ŭ ��찡 �ִ�. �� ���� ���濡 ���������� ��ǰ�� + ���� ��ǰ�� �ƴ϶� total���Կ��� ���� ��ǰ�� ���ԵǾ�
�� ���� ���ϴ� ���̴�. ��

���� ��ǰ��� �̷� ���� ���� == ���� ��ǰ�� ���� ��ǰ�� ���ؼ� �̷� ���� ����
�� �߿��� � ���� �� ��� �������� üũ�ϴ� ���̴�.

���� ���� ���԰� total ���Ժ��� ũ�ٸ� ���� �������� total ���Կ� ���Ե� �� ����. ���� ����
�������� �߰��ϴ� ���� ������ �� ����. �׷��Ƿ� �ᱹ ���� �����۱��� ���յ� ������ �� ���̴�.

DP[i]���� ��� ���Կ� ���Ͽ� ���� �����۰� i���� �������� ��쿡 ���� ��� ����� ������ �� ����Ǿ� �ִ�.
���� index�� �ϳ� ���� DP���� �����ͼ� �����ϴ� ���̴�.

�� ������ SubsetSum using Tabulation �ڵ�� ������ �Ȱ���. else������ 
DP�� ������Ʈ�ϴ� ��ĸ� �ٸ� ���̴�.
*/

int Knapsack_01(int items, int capacity, vector<int> values,
	vector<int> weight)
{
	//DP ���̺��� 2�������� ���� ���̰�, �κ������� �� �������� ����� ���¿� ����� �����ϴ�.
	//�κ������� �տ��� ����� ���̺��� ���, ù ��° ���� ũ��� ���� ũ�⺸�� �ϳ� ũ�� �����߰�,
	//�� ��° ���� ũ��� ���� ��ü ���� �պ��� �ϳ� ũ�� �����ߴ�. 0-1 �賶 ������ ��� ���̺��� ù
	//��° ������ ũ��� (���� ���� + 1)�� �����ϰ�, �� ��° ������ ũ��� (�賶 �뷮 + 1)�� �����Ѵ�.
	vector<vector<int>> DP(items + 1, vector<int>(capacity + 1, 0));

	//������� �� ���� ���Կ� ���ؼ��� 0���� ���̺��� ������Ʈ�� ���̴�.
	for (int i = 1; i <= items; i++)
	{
		int currentWeight = weight[i - 1];
		int currentValue = values[i - 1];

		for (int totalWeight = 1; totalWeight <= capacity; totalWeight++)
		{
			//total_weight�� currentweight���� �۴ٴ� ���� total_weight�� currentweight�� ������ ���԰� �ƴ϶�� ���̴�.
			//�� ���� �������� ���԰� 7�ε� total_weoght�� 5�� ���� ���� �����۱��� ������� ���� ���ۿ� ���ٴ� ���̴�.
			//���� total_weight�� current_weight���� Ŭ ���� ���� �������� �߰��� ���� �߰����� �ʾ��� ��� ���԰� 
			//� ���� �� ū���� �����ؾ� �Ѵ�.
			if (totalWeight < currentWeight)
			{
				cout << i << "��° �������� ����� ���" << endl;

				cout << "totalWeight < currentWeight called" << endl;

				cout << "totalWeight: " << totalWeight << " currentWeight: " << currentWeight<<endl;

				auto temp = DP[i][totalWeight];

				DP[i][totalWeight] = DP[i - 1][totalWeight];

				cout << "DP[" << i << "][" << totalWeight << "]("<<temp <<") = DP[" << i - 1 << "][" << totalWeight << "]("<< DP[i - 1][totalWeight] 
					<<") : " << DP[i][totalWeight] << endl;

				cout << endl;
				cout << endl;
			}
			else
			{
				cout << i << "��° �������� ����� ���" << endl;

				cout << "else called" << endl;

				auto temp = DP[i][totalWeight];

				//DP[i-1][totalWeight]�� ���� �������� �߰����� �ʰ� ���� �����۱����� ��쿡�� totalweight�� ���� �����̴�.
				//�κ������� �� ó�� set[i-1]�� ���ϴ� �Ͱ� ������ �ʴ� ������ �������� ���� �������� �߰����� ���� �߰�����
				//�ʾ��� �� � ����� ������ �� ū ���� �Ǵ��� �� ���� DP���� ������Ʈ�Ѵ�.
				DP[i][totalWeight] = max(DP[i - 1][totalWeight],
					// �κ������� �� �������� i��° �ܰ迡�� 
					//set[i-1]<=sum�� ��� sum-set[i-1]�� ���� �ܰ迡�� ������ �� Ȯ���Ѵ�. �����ϴٸ�
					//set[i-1]�� ���ؼ� sum�� ���� �� �����Ƿ� true�� �����Ѵ�.

					//total_weight�� current_weight���� ũ�ٸ� total_weight���� current_weight�� ���� ��
					//�� ���ݿ� ���� ������ ���� ���� ���� �������� ���濡 �־��� ���� ������ �ǹ��Ѵ�.
					//DP[i-1][totalWeight-currentWeight] �� total_weight���� current_weight�� �� ������ ����
					//�����ε�, �� ���ݿ� currentValue�� ���Ѵٴ� ���� total_weight�� currentWeight�� �߰��� ���¶�� ���̴�.
					//�� ���� �������� �߰����� ����� ������ �ǹ��Ѵ�.

					//�� ������ �ٽ� ���� �� ����� total_weight�� i-1���� ����� ���Կ��� currentweight�� �߰��� ���̴�.
					//���� ���� ����� �Ϸ��� total_weight���� currentweight�� �� �� ���ݿ� ���� �������� ������ �߰��ϴ� ���̴�.
					DP[i - 1][totalWeight - currentWeight] + currentValue);

				cout << "DP[" << i << "][" << totalWeight << "](" << temp << ") = max(DP[" << i - 1 << "][" << totalWeight << "](" << DP[i - 1][totalWeight]
					<< ") , DP[" << i - 1 << "][" << totalWeight - currentWeight << "](" << DP[i - 1][totalWeight - currentWeight] << ") + " << currentValue
					<< ") : "<< DP[i][totalWeight] << endl;

				cout << endl;
				cout << endl;
			}
		}
	}

	return DP[items][capacity];
}

int main()
{
	//�� ���� ������ ���� items�� capacity�� �����ϰ�, ǥ�� �Է����� ���� �����Ѵ�. items�� ��ü ����
	//������ ��Ÿ����, capacity�� �賶�� ���� �뷮�� ��Ÿ����. �׸��� value�� weight ���Ϳ� �� ������ ���ݰ�
	//���� ������ �����Ѵ�.
	int items, capacity;
	cin >> items >> capacity;

	vector<int> values(items), weight(items);

	for (auto& v : values) cin >> v;
	for (auto& w : weight) cin >> w;

	int result = Knapsack_01(items, capacity, values, weight);

	cout << "�賶�� ä�� �� �ִ� ���ǵ��� �ְ� ����: " << result << endl;
}

/*
	8 66
	20 4 89 12 5 50 8 13
	5 23 9 72 16 14 32 4
	returns 180.
*/
