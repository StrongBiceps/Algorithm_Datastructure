#include <iostream>
#include <climits>
#include <fstream>
#include <vector>

using namespace std;

struct Edge
{
	int src;
	int dst;
	int weight;
};

const int UNKNOWN = INT_MAX;

bool ReadTestCase(string filename, int& N, vector<Edge>& edges)
{
	ifstream infile(filename);

	if (!infile.is_open())
	{
		cout << "테스트 케이스 파일을 열 수 없습니다!" << endl;
		return false;
	}

	infile >> N;

	for (int i = 0; i < N * N - 1; i++)
	{
		string directions;
		int power;

		//파일에서 방향과 전력을 받아온다.
		infile >> directions >> power;

		//해당 정점과 연결되어 있는 정점의 ID를 의미한다.
		int next = i;

		for (auto d : directions)
		{

			switch (d)
			{
			case 'N': next = i - N; break;
			case 'E': next = i + 1; break;
			case 'S': next = i + N; break;
			case 'W': next = i - 1; break;
			}

			//에지를 추가한다.
			// power 값의 부호를 바꿔서 에지 가중치로 사용
			edges.push_back(Edge{ i, next, -power });
		}
	}

	return true;
}

vector<int> BellmanFord(vector<Edge> edges, int V, int start)
{
	vector<int> distance(V, UNKNOWN);
	distance[start] = 0;

	// (V - 1)번 반복
	for (int i = 0; i < V - 1; i++)
	{
		// 전체 에지에 대해 반복
		for (auto& e : edges)
		{
			// 에지의 시작 정점의 거리 값이 UNKNOWN이면 스킵
			if (distance[e.src] == UNKNOWN)
				continue;

			// 인접한 정점의 거리 값이 새로운 경로에 의한 거리 값보다 크면
			// 거리 값을 업데이트함.
			if (distance[e.dst] > distance[e.src] + e.weight)
			{
				distance[e.dst] = distance[e.src] + e.weight;
			}
		}
	}

	// 음수 가중치 사이클이 있는 지 검사
	for (auto& e : edges)
	{
		if (distance[e.src] == UNKNOWN)
			continue;

		if (distance[e.dst] > distance[e.src] + e.weight)
		{
			//cout << "음수 가중치 사이클 발견!" << endl;
			return {};
		}
	}

	return distance;
}

int main()
{
	//N*N 행렬 그래프를 의미한다.
	int N;
	vector<Edge> edges;     // 에지 리스트

	// testcase1~5.txt 파일로부터 테스트 입력을 받아 결과 확인
	if (ReadTestCase("testcase1.txt", N, edges))
	{
		vector<int> distance = BellmanFord(edges, N * N, 0);

		//만약 마지막 정점으로 가는 길이 없는 그래프는 마지막 정점의 거리가 UNKNOWN이므로 
		//해당 경우에도 탐색을 중단한다.
		//distance가 비어있는 경우는 음수 사이클이 존재하여 빈 벡터를 반환하는 경우이다.
		if (distance.empty() || distance[N * N - 1] == UNKNOWN)
			cout << "탐색 중단" << endl;
		//power를 음수로 바꿨으므로 마지막 정점의 거리를 다시 양수로 바꿔줘야 한다.
		else
			cout << -1 * distance[N * N - 1] << endl;
	}
}