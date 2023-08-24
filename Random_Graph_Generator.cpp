#include <iostream>
#include <climits>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct Edge
{
	int src;
	int dst;
	int weight;
};

const int UNKNOWN = 1e9;

static unsigned long int next_random = 1;

int rand(void)
{
	next_random = next_random * 1103515245 + 12345;
	return (unsigned int)(next_random / 65536) % 32768;
}

void srand(unsigned int seed)
{
	next_random = seed;
}

enum RESULT
{
	VALID,
	INVALID,
	INTERESTING
};

class Graph
{
public:
	int V, E;
	int maxWeight = -UNKNOWN;

	vector<Edge> edges;
	vector<vector<int>> adj;
	vector<vector<int>> weight;

	Graph(int v, int e) : V(v), E(e)
	{
		//두 정점 사이에 이미 에지가 있는지 확인하기 위한 boolean vector
		vector<vector<bool>> used(V, vector<bool>(V, false));

		adj.resize(V);
		weight.resize(V, vector<int>(V, UNKNOWN));

		//생성해야 하는 에지 개수만큼 반복한다.
		while (e)
		{
			// 에지 정보 생성
			int u = rand() % V;
			int v = rand() % V;
			int w = rand() % 100;

			if (rand() % 3 == 0)
			{
				w = -w;
			}

			// 유효한 에지인지 확인
			//유효한 에지가 아니면 반복을 생략
			if (u == v || used[u][v])
				continue;

			// 에지 정보를 추가하고 used 배열 값을 설정
			edges.push_back(Edge{ u, v, w });
			adj[u].push_back(v);
			weight[u][v] = w;
			//그래프의 가장 큰 가중치를 찾기 위함.
			maxWeight = max(maxWeight, w);

			//자기 자신으로 연결되는 것을 방지함과, 두 정점 사이에는 하나의 에지만을
			//허용하는 코드.
			used[u][u] = used[v][v] = used[u][v] = used[v][u] = true;
			e--;
		}

		for (int i = 0; i < V; i++)
		{
			// 유효하지 않은 그래프에 대해 V 값을 -1로 설정
			//아래 값이 참이 된다면 에지가 하나도 없는 정점이 존재한다는 의미.
			if (!used[i][i])
			{
				V = -1;
				break;
			}
		}
	}
};

vector<int> BellmanFord(Graph G)
{
	vector<int> distance(G.V + 1, UNKNOWN);

	//더미 정점을 추가한다.
	int s = G.V;

	for (int i = 0; i < G.V; i++)
	{
		G.edges.push_back(Edge{ s, i, 0 });
	}

	distance[s] = 0;

	// 정점 개수가 V + 1개 이므로 V번 반복
	for (int i = 0; i <= G.V; i++)
	{
		for (auto& e : G.edges)
		{
			if (distance[e.src] == UNKNOWN)
				continue;

			if (distance[e.dst] > distance[e.src] + e.weight)
			{
				distance[e.dst] = distance[e.src] + e.weight;
			}
		}
	}

	for (auto& e : G.edges)
	{
		if (distance[e.src] == UNKNOWN)
			continue;

		if (distance[e.dst] > distance[e.src] + e.weight)
		{
			return {};
		}
	}

	return distance;
}

vector<int> Dijkstra(int src, Graph G)
{
	using State = pair<int, int>;  // {distance, id}

	priority_queue<State, vector<State>, greater<State>> heap;
	vector<bool> visited(G.V, false);
	vector<int> distance(G.V, UNKNOWN);

	heap.push({ 0, src });
	distance[src] = 0;

	while (!heap.empty())
	{
		State top = heap.top();
		heap.pop();

		int dist = top.first;
		int node = top.second;

		visited[node] = true;

		for (auto next : G.adj[node])
		{
			if (visited[next])
			{
				continue;
			}

			if (dist != UNKNOWN && distance[next] > dist + G.weight[node][next])
			{
				distance[next] = dist + G.weight[node][next];

				heap.push({ distance[next], next });
			}
		}
	}

	return distance;
}

RESULT TestGraph(Graph G)
{
	//정점 개수가 -1로 설정되어 있다면 
	//유효하지 않은 그래프
	if (G.V == -1)
		return INVALID;

	//벨만 포드 알고리즘으로 거리를 측정한다.
	vector<int> distance = BellmanFord(G);

	//만약 음수 사이클이 발생한다면 어쨋든 유효한 그래프로 결정.
	if (distance.empty())
		return VALID;

	//가중치 변환 식을 적용한다.
	for (auto& e : G.edges)
	{
		G.weight[e.src][e.dst] += (distance[e.src] - distance[e.dst]);
	}

	double result = 0;

	for (int i = 0; i < G.V; i++)
	{
		vector<int> shortest = Dijkstra(i, G);

		double average = 0;
		int count = 0;

		for (int j = 0; j < G.V; j++)
		{
			//i와 j가 같은 경우는 정점 i에서 i로의 거리를 측정하는 것과 같으므로
			//반복을 생략한다.
			if (i == j || shortest[j] == UNKNOWN)
				continue;

			//가중치 변환 식을 역으로 적용하여 원상복구한다.
			shortest[j] += (distance[j] - distance[i]);
			average += shortest[j];
			//도달 가능한 정점 개수를 카운트
			count++;
		}

		average = average / count;
		result += average;
	}

	//그래프의 총 평균
	result = result / G.V;

	//그래프의 평균 거리가 가중치가 가장 큰 에지의 절반보다 작은 경우 -> 흥미로운 그래프
	double ratio = result / G.maxWeight;
	return (ratio < 0.5) ? INTERESTING : VALID;
}

int main()
{
	long seed;
	int iterations, V, E;

	cin >> seed;
	cin >> iterations;
	cin >> V >> E;

	int invalid = 0;
	int valid = 0;
	int interesting = 0;

	srand(seed);

	while (iterations--)
	{
		Graph G(V, E);

		switch (TestGraph(G))
		{
		case INVALID: invalid++; break;
		case VALID: valid++; break;
		case INTERESTING:
		{
			valid++;
			interesting++;
			break;
		}
		}
	}

	double percentInteresting = (double)interesting / valid * 100;

	cout << "유효하지 않은 그래프 개수: " << invalid << endl;
	cout << "흥미로운 그래프 생성 비율: " << fixed << setprecision(2) << percentInteresting << "%" << endl;

	return 0;
}

/*
42 1000 15 10
유효하지 않은 그래프 개수: 996
흥미로운 그래프 생성 비율: 0.00%

11111 400 5 5
유효하지 않은 그래프 개수: 55
흥미로운 그래프 생성 비율: 0.58%
*/