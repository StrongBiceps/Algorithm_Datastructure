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

		//검색할 원소를 queries에 저장한다.

		queries.push_back({ N,M });

		if (M * 2 > N)

			M = N - M + 1;

		//result는 DP테이블에 해당한다.	

		results[{N, M}] = -1;

		//maxRow는 입력된 원소 중에서 가장 큰 행 값을 저장하는 것이다.

		//그래야 아래 코드에서 해당 행까지 테이블을 업데이트할 것이다.

		//즉 구하고자 하는 행 이후의 테이블은 사용하지 않으므로 업데이트

		//하지 않는다.

		maxRow = max(maxRow, N);

	}

	vector<int> prev = { 0,1 };

	for (int row = 1; row <= maxRow; ++row)

	{

		int width = (row / 2) + (row % 2);

		vector<int> curr(width + 2);

		for (int col = 1; col <= width; ++col)

		{

			//1행에 대해서 curr[1]까지만 실행된다.

			//curr[1] = prev[0] + prev[1] -> 1

			//파스칼 삼각형에서는 이전 행과 다음 행의 원소 관계식은 다음과 같다.

			curr[col] = prev[col - 1] + prev[col];

			//만약 검색하고자 하는 원소라면 테이블을 업데이트한다.

			if (results.find({ row,col }) != results.end())

			{

				results[{row, col}] = curr[col];

			}

		}

		if (row % 2 == 0)

		{

			curr[width + 1] = curr[width];

		}

		//계산이 끝난 현재 행을 다음 반복에서 이전 행 prev로 사용하기 위해서 move를 사용해서 전달한다.

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