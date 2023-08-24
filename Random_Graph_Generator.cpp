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
		//�� ���� ���̿� �̹� ������ �ִ��� Ȯ���ϱ� ���� boolean vector
		vector<vector<bool>> used(V, vector<bool>(V, false));

		adj.resize(V);
		weight.resize(V, vector<int>(V, UNKNOWN));

		//�����ؾ� �ϴ� ���� ������ŭ �ݺ��Ѵ�.
		while (e)
		{
			// ���� ���� ����
			int u = rand() % V;
			int v = rand() % V;
			int w = rand() % 100;

			if (rand() % 3 == 0)
			{
				w = -w;
			}

			// ��ȿ�� �������� Ȯ��
			//��ȿ�� ������ �ƴϸ� �ݺ��� ����
			if (u == v || used[u][v])
				continue;

			// ���� ������ �߰��ϰ� used �迭 ���� ����
			edges.push_back(Edge{ u, v, w });
			adj[u].push_back(v);
			weight[u][v] = w;
			//�׷����� ���� ū ����ġ�� ã�� ����.
			maxWeight = max(maxWeight, w);

			//�ڱ� �ڽ����� ����Ǵ� ���� �����԰�, �� ���� ���̿��� �ϳ��� ��������
			//����ϴ� �ڵ�.
			used[u][u] = used[v][v] = used[u][v] = used[v][u] = true;
			e--;
		}

		for (int i = 0; i < V; i++)
		{
			// ��ȿ���� ���� �׷����� ���� V ���� -1�� ����
			//�Ʒ� ���� ���� �ȴٸ� ������ �ϳ��� ���� ������ �����Ѵٴ� �ǹ�.
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

	//���� ������ �߰��Ѵ�.
	int s = G.V;

	for (int i = 0; i < G.V; i++)
	{
		G.edges.push_back(Edge{ s, i, 0 });
	}

	distance[s] = 0;

	// ���� ������ V + 1�� �̹Ƿ� V�� �ݺ�
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
	//���� ������ -1�� �����Ǿ� �ִٸ� 
	//��ȿ���� ���� �׷���
	if (G.V == -1)
		return INVALID;

	//���� ���� �˰������� �Ÿ��� �����Ѵ�.
	vector<int> distance = BellmanFord(G);

	//���� ���� ����Ŭ�� �߻��Ѵٸ� ��¶�� ��ȿ�� �׷����� ����.
	if (distance.empty())
		return VALID;

	//����ġ ��ȯ ���� �����Ѵ�.
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
			//i�� j�� ���� ���� ���� i���� i���� �Ÿ��� �����ϴ� �Ͱ� �����Ƿ�
			//�ݺ��� �����Ѵ�.
			if (i == j || shortest[j] == UNKNOWN)
				continue;

			//����ġ ��ȯ ���� ������ �����Ͽ� ���󺹱��Ѵ�.
			shortest[j] += (distance[j] - distance[i]);
			average += shortest[j];
			//���� ������ ���� ������ ī��Ʈ
			count++;
		}

		average = average / count;
		result += average;
	}

	//�׷����� �� ���
	result = result / G.V;

	//�׷����� ��� �Ÿ��� ����ġ�� ���� ū ������ ���ݺ��� ���� ��� -> ��̷ο� �׷���
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

	cout << "��ȿ���� ���� �׷��� ����: " << invalid << endl;
	cout << "��̷ο� �׷��� ���� ����: " << fixed << setprecision(2) << percentInteresting << "%" << endl;

	return 0;
}

/*
42 1000 15 10
��ȿ���� ���� �׷��� ����: 996
��̷ο� �׷��� ���� ����: 0.00%

11111 400 5 5
��ȿ���� ���� �׷��� ����: 55
��̷ο� �׷��� ���� ����: 0.58%
*/