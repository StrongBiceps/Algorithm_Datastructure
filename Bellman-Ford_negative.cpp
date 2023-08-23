#include <vector>
#include <iostream>
#include <climits>

using namespace std;

//에지 클래스는 시작 정점인 src와 도착 정점인 dst, 그리고 가중치로 구성된다.
class Edge
{
public:
	int src;
	int dst;
	int weight;
};

//무한대를 표현하기 위해 상수 UNKNOWN을 정의한다. UNKNOWN은 정수 상수 값으로, 그래프 에지 가중치의 합보다 충분히
//큰 정수로 지정한다. 여기서는 정수 최대값인 INT_MAX로 정의했고, INT_MAX는 climits> 파일에 정의되어 있다.

const int UNKNOWN = INT_MAX;

//이제 벨만 포드 알고리즘을 구현한 BellmanFord() 함수를 구현한다. 이 함수는 그래프를 표현하는 에지 리스트
//edges, 정점 개수 V, 출발 정점 번호 Start를 인자로 받고, 거리 값 배열을 반환한다. 이 함수 내부에서는 V개 크기의
//거리 값 배열 distance를 사용하고, 이 배열의 초깃값은 UNKNOWN으로 지정한다. 다만 출발 정점에 대해서는 distance값은
//0으로 설정한다.

vector<int> BellmanFord(vector<Edge> edges, int V, int start)
{
	vector<int> distance(V, UNKNOWN);
	distance[start] = 0;

	//알고리즘의 대부분은 다음 단계에서 수행한다. 이 단계에서는 (V-1)번 반복되는 루프를 정의하고, 각 루프에서는
	//전체 에지를 검토하면서 각 정점의 거리 값을 업데이트한다. 구체적으로 설명하면 각각의 에지 중에서 시작 정점의 
	//거리 값이 UNKNOWN이 아닌 경우에 대해서만 거리 값을 업데이트하며, 이때(시작 정점 거리 값+에지 가중치) 계산 결과가
	//목적지 정점의 거리 값보다 작으면 목적지 정점의 거리 값을 (시작 정점 거리 값+ 에지 가중치)로 교체한다.

	//(V-1)번 반복
	//각 에지를 V-1번 반복하면서 거리를 업데이트하는 것이다.
	//즉 각 에지를 V-1번 
	for (int i = 0; i < V - 1; ++i)
	{
		cout << "outter" << endl;
		//전체 에지에 대해 반복
		for (auto& e : edges)
		{
			//에지의 시작 정점이 UNKNOWN값이면 스킵
			//즉 한 번이라도 거리가 업데이트 된 정점일 때에만 다시 거리 업데이트를 진행한다.
			//거리가 무한인 정점에 대해서도 거리를 바로 업데이트 해버리면 의도치 않은 상황이 발생한다.
			//예를들어 1->2->3->4<-5 의 그래프가 있다고 하자. 3->4까지는 정상적으로 업데이트가 이루어진다.
			//만약 5(무한대)->4의 거리가 업데이트 되어 버리면 1->5->4가 가능하다는 상황이 된다. 하지만
			//1에서 바로 5로 갈 수는 없다. 즉 거리가 한 번이라도 업데이트 된 상태라는 것은 해당 정점까지
			//경로가 이어져 있고, 거리가 계산된 상태라는 것이다.
			if (distance[e.src]==UNKNOWN)
			{
				cout << "continue" << endl;
				continue;
			}
			//에지의 시작 정점의 거리 값이 새로운 경로에 의한 거리 값보다 크면
			//거리 값을 업데이트함
			if (distance[e.dst] > distance[e.src] + e.weight)
			{
				cout << "update" << endl;
				distance[e.dst] = distance[e.src] + e.weight;
			}
		}
	}

	//V-1번의 반복이 완료되었음에도 거리가 업데이트되는 경우가 발생한다면 사이클인 것이다.
	for (auto& e : edges)
	{
		if (distance[e.src] == UNKNOWN)
			continue;

		if (distance[e.dst] > distance[e.src] + e.weight)
		{
			cout << "음수 가중치 사이클 발견" << endl;
			return {};
		}
	}

	return distance;
}

int main()
{
	int V = 6;              // 정점 개수
	vector<Edge> edges;     // 에지 포인터의 벡터

	vector<vector<int>> edge_map{ // {시작 정점, 목표 정점, 가중치}
		{0, 1, 3},
		{1, 3, -8},
		{2, 1, 3},
		{2, 5, 5},
		{3, 2, 3},
		{2, 4, 2},
		{4, 5, -1},
		{5, 1, 8}
	};

	for (auto& e : edge_map)
	{
		edges.emplace_back(Edge{ e[0], e[1], e[2] });
	}

	int start = 0;
	vector<int> distance = BellmanFord(edges, V, start);

	if (!distance.empty())
	{
		cout << "[" << start << "번 정점으로부터 최소 거리]" << endl;

		for (int i = 0; i < distance.size(); i++)
		{
			if (distance[i] == UNKNOWN)
				cout << i << "번 정점: 방문하지 않음!" << endl;
			else
				cout << i << "번 정점: " << distance[i] << endl;
		}
	}
}