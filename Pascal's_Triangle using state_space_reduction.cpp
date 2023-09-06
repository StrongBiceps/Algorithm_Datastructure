#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

int main()
{
	map<pair<int, int>, int> results;

	vector<pair<int, int>> queries;

	int q;

	cin >> q;

	int maxRow = 0;

	for (int i = 0; i < q; ++i)

	{

		int N, M;

		cin >> N >> M;

		//�˻��� ���Ҹ� queries�� �����Ѵ�.

		queries.push_back({ N,M });

		if (M * 2 > N)

			M = N - M + 1;

		//result�� DP���̺� �ش��Ѵ�.	

		results[{N, M}] = -1;

		//maxRow�� �Էµ� ���� �߿��� ���� ū �� ���� �����ϴ� ���̴�.

		//�׷��� �Ʒ� �ڵ忡�� �ش� ����� ���̺��� ������Ʈ�� ���̴�.

		//�� ���ϰ��� �ϴ� �� ������ ���̺��� ������� �����Ƿ� ������Ʈ

		//���� �ʴ´�.

		maxRow = max(maxRow, N);

	}

	vector<int> prev = { 0,1 };

	for (int row = 1; row <= maxRow; ++row)

	{

		int width = (row / 2) + (row % 2);

		vector<int> curr(width + 2);

		for (int col = 1; col <= width; ++col)

		{

			//1�࿡ ���ؼ� curr[1]������ ����ȴ�.

			//curr[1] = prev[0] + prev[1] -> 1

			//�Ľ�Į �ﰢ�������� ���� ��� ���� ���� ���� ������� ������ ����.

			curr[col] = prev[col - 1] + prev[col];

			//���� �˻��ϰ��� �ϴ� ���Ҷ�� ���̺��� ������Ʈ�Ѵ�.

			if (results.find({ row,col }) != results.end())

			{

				results[{row, col}] = curr[col];

			}

		}

		if (row % 2 == 0)

		{

			curr[width + 1] = curr[width];

		}

		//����� ���� ���� ���� ���� �ݺ����� ���� �� prev�� ����ϱ� ���ؼ� move�� ����ؼ� �����Ѵ�.

		prev = move(curr);

	}

	for (auto query : queries)

	{

		int N = query.first, M = query.second;

		if (M * 2 > N)

			M = N - M + 1;

		cout << results[{N, M}] << endl;

	}
}