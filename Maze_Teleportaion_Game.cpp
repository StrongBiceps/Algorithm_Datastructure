#include <stack>
#include <algorithm>
#include <iostream>
#include <climits>
#include <fstream>
#include <vector>

//���ÿ� ���� �������� ���� ���� ���� ��Ұ� ���� ���̴�. 
//�׷����� ���� ���� ���(3�� �̻��� �������� �����)�� 2�� �̻� �����ϴ���
//������ ���� ���� ���� ��Ұ� ���� ���� ���ÿ� ���� ������ �ʾҴٸ�
//���ÿ� ���� ���� �ʴ´�. �ֳ��ϸ� DFS�������� �ٸ� ���� ��ҷ� �̵��� �� �ֱ� �����̴�.

//�ڻ���� �������� ����ߵ��� ���� ���� ���� ���� �ϳ�������� ���� ��Ҹ� �Ǻ��� �� ����.
//�� �������� ���� ��Ҹ� �Ǻ��ϴ� ����� componentIndex�� Ȱ���ϴ� ���̴�. isStuck�� false�� �����ϴ�
//������ ������ �׷������� �ش� �������� ����� ������ false�� �������ִ� ���̴�. �� node�� ���� ������
//next�� componentIndex�� �ٸ� ��� node�� �������� next�� false�� �����ϴ� ���̴�. ���� ���� ����
//���� ���ó�� ������ �׷������� �ٸ� ������ ���� ���� ��ҷ� �̵��� �� ���� ������ ���� ���� ��Ҹ� false��
//�������� �� ���� ������ ���� ���� �Ǻ��� �� �ִ� ���̴�. ���⼭ ���� ������ ���� ��Ұ� ���� ����
//���ÿ� ���� �Ͱ��� ���谡 ����.

//���� IsStuck�� ���� ������ �ٷ�� ���� �ƴ϶� component����(���� ���� ��� ����)�� �ٷ��. �� ���� ���� ���� ��Ҵ�
//�ش� ���� ��ҷ� ������ ����� componentIndex�� �ٸ� ���� ��Ұ� ���� ������ false�� �������� �ʴ´�. ������ ������ ����
//���� ��Ҵ� �ش� ���� ��ҷ� ������ ����� �ٸ� ���� ��Ұ� �ֱ� ������ isStuck�� false�� �����ȴ�. �ڻ���� �ڵ忡���� �׷�����
//�Է����� �����غ��� 2456�� 837 ���� ��ҿ� ���� false�� �����ȴ�. ���� 837�� ���� ����� ���´�.
using namespace std;

//���� Ŭ����
class Edge
{
public:
	int src;
	int dst;
	int weight;
};

//�� ������ �������� ���� ���带 ��ģ���� �ش� �������� � ������ ���� ���� �Ÿ��� �ٸ� ����(������)�� �̵��� �� �ִ����� �ܷ�� ����

const int UNKNOWN = INT_MAX;

bool ReadTestCase(string filename, int& V, vector<Edge>& edges)
{
	ifstream infile(filename);

	if (!infile.is_open())
	{
		cout << "�׽�Ʈ ���̽� ������ �� �� �����ϴ�!" << endl;
		return false;
	}

	int E;
	infile >> V >> E;

	for (int i = 0; i < E; i++)
	{
		int u, v, w;
		infile >> u >> v >> w;

		edges.push_back(Edge{ u, v, w });
	}

	return true;
}

void FillStack(int node, vector<bool>& visited,
	vector<vector<int>>& adj, stack<int>& stack)
{
	visited[node] = true;

	for (auto next : adj[node])
	{
		if (!visited[next])
		{
			FillStack(next, visited, adj, stack);
		}
	}
	//���ÿ� ����Ǵ� ������ ���� ���� ����� ��¹�
	cout << " FillStack" << endl << node << endl;
	stack.push(node);
}

//���� ���� ��Ҹ� �����ϴ� �迭
vector<bool> isStuck;
vector<int> inComponent;
int componentIndex;

void CollectConnectedComponents(int node, vector<bool>& visited,
	vector<vector<int>>& adj, vector<int>& component)
{
	visited[node] = true;
	component.push_back(node);

	//inComponent�� �ش� ��尡 � ���� ���� ��ҿ� �����ִ��� Ȯ���ϴ� �迭�̰�,
	//componentIndex�� ���� ���� ��Ҹ� �����ϴ� Index�̴�.
	//���� ���ϰ� ����� �������� ���� index�� ���� �����ϱ� ���ؼ���.
	inComponent[node] = componentIndex;

	//� ������ � ���� ��� �ε����� �����Ǿ����� Ȯ���ϱ� ���� ����� ��¹�
	cout << "index:" << componentIndex << " node:" << node << endl;
	for (auto next : adj[node])
	{
		if (!visited[next])
		{
			//��ġ�� �׷������� �ش� node�� �� �� �ִ� ������ �ִ� �� Ȯ���ϴ� ��¹�
			cout << "has child" << endl;
			CollectConnectedComponents(next, visited, adj, component);
		}
		//vector<Edge> edges = { {0,1,0},{1,2,0},{2,3,0},{3,0,0} } �̷� ������ ��� ������ ����Ǿ� �ִ� �׷����� ����
		//�ش� for������ ���� ������ �����ٰ� ������ �� �ִµ�, �ڵ带 �� ���� 0->3->2->1 ������ �湮�ϴٰ� 1���� �ٽ� 0���� �湮�� ���̴�.
		//0�� �̹� visited�� true�� ��Ȳ�̹Ƿ� CollectConnectedComponents�� �ٽ� ȣ������ �ʴ´�. ���� else if������ ���� �ǰ� else if��
		//���ǵ� ���� �����Ƿ� 1�� for���� ������. ��͸� ���� �ö󰡸� for���� �����ϹǷ� ���� ������ ������ �ʴ´�.
		else if (inComponent[node] != inComponent[next])
		{
			//isStuck�� false�� �����Ǵ� ������ ���� ���� ����� ��¹�
			cout << "isStuck: " << next << endl;
			isStuck[inComponent[next]] = false;
		}
	}
}

vector<vector<int>> Transpose(int V, vector<vector<int>> adj)
{
	vector<vector<int>> transpose(V);

	for (int i = 0; i < V; i++)
	{
		for (auto next : adj[i])
		{
			transpose[next].push_back(i);
		}
	}

	return transpose;
}

vector<vector<int>> Kosaraju(int V, vector<vector<int>> adj)
{
	isStuck.resize(V, true);
	inComponent.resize(V, UNKNOWN);
	componentIndex = 0;

	vector<bool> visited(V, false);
	stack<int> stack;

	for (int i = 0; i < V; i++)
	{
		if (!visited[i])
		{
			FillStack(i, visited, adj, stack);
		}
		cout << "Fillstack next" << endl;
	}

	////�� � ������ ��ȸ�ص� ���� ���� ���� ��Һ��� ���ÿ� ����.
	//for (int i = 6; i < V; ++i)
	//{
	//	if (!visited[i])
	//	{
	//		FillStack(i, visited, adj, stack);
	//	}
	//}
	//for (int i = 5; i >= 0; --i)
	//{
	//	if (!visited[i])
	//	{
	//		FillStack(i, visited, adj, stack);
	//	}
	//}

	vector<vector<int>> transpose = Transpose(V, adj);

	fill(visited.begin(), visited.end(), false);

	vector<vector<int>> connectedComponents;

	while (!stack.empty())
	{
		int node = stack.top();
		stack.pop();

		if (!visited[node])
		{
			vector<int> component;

			CollectConnectedComponents(node, visited, transpose, component);
			connectedComponents.push_back(component);
			//Index�� ����� ������ ���� ���� ����� �ڵ�
			cout << "componentIndex++" << endl;
			componentIndex++;
		}
	}

	return connectedComponents;
}

bool HasNegativeCycle(const vector<Edge>& edges, vector<int> distance)
{
	for (auto& e : edges)
	{
		if (distance[e.src] == UNKNOWN)
			continue;

		if (distance[e.dst] > distance[e.src] + e.weight)
			return true;
	}

	return false;
}

int BellmanFord(vector<Edge> edges, int V, int start)
{
	vector<int> distance(V, UNKNOWN);
	distance[start] = 0;

	// (V - 1)�� �ݺ�
	for (int i = 0; i < V - 1; i++)
	{
		// ��ü ������ ���� �ݺ�
		for (auto& e : edges)
		{
			// ������ ���� ������ �Ÿ� ���� UNKNOWN�̸� ��ŵ
			if (distance[e.src] == UNKNOWN)
				continue;

			// ������ ������ �Ÿ� ���� ���ο� ��ο� ���� �Ÿ� ������ ũ��
			// �Ÿ� ���� ������Ʈ��.
			if (distance[e.dst] > distance[e.src] + e.weight)
			{
				distance[e.dst] = distance[e.src] + e.weight;
			}
		}
	}

	// ���� ����ġ ����Ŭ�� ������ UNKNOWN ��ȯ
	if (HasNegativeCycle(edges, distance))
	{
		return UNKNOWN;
	}

	int result = UNKNOWN;

	for (int i = 0; i < V; i++)
	{
		if (i == start) continue;

		result = min(result, distance[i]);
	}

	//���� ���带 ������ �׷������� ���� ���� �Ÿ� ���� �����Ѵ�.
	return result;
}

int main()
{
	//�ڻ���� �ڵ忡�� ����� ���� ��Ұ� ������ ���޾� ���� ������ �ʴ´ٴ� ����
	//Ȯ���ϴ� �ڵ�
	/*int V=6;
	vector<Edge> edges = { {0,1,0},{1,2,0},{2,3,0},{2,4,0},{1,5,0} };*/

	//��� ������ ����� �ϳ��� ���� ���� ��ҷ� �̷���� ���� �׷����� ���
	int V = 4;
	vector<Edge> edges = { {0,1,0},{1,2,0},{2,3,0},{3,0,0} };

	//�ڻ���� �ڵ��� �׷���
	/*int V=9;
	vector<Edge> edges = { {0,1,0},{0,3,0},{1,4,0},{1,2,0},{2,3,0},{2,5,0},{3,7,0},{4,2,0},{5,4,0},{5,6,0},{6,7,0},{6,2,0},{7,8,0},{8,3,0} };*/

	//ReadTestCase("testcase4_maze.txt", V, edges);


	vector<vector<int>> adj(V);

	for (auto& e : edges)
	{
		adj[e.src].push_back(e.dst);
	}

	//�� ������ �������� ���� ���带 ��ģ �ּ� �Ÿ��� �����ϴ� �迭
	vector<int> results;

	for (int i = 0; i < V; i++)
	{
		if (adj[i].empty())
		{
			results.push_back(UNKNOWN);
			continue;
		}

		int shortest = BellmanFord(edges, V, i);

		//���� ����Ŭ �߻� ���
		if (shortest == UNKNOWN)
		{
			cout << "��ȿ���� ���� �̷�" << endl;
			return 0;
		}

		//�� ���� �ε����� ���� ���� �Ÿ� ���� �ִ´�.
		results.push_back(shortest);
	}

	//�� � �������ε� �̵��� �� ���� ������ ���� ���̶�� �ϰ� ����Ѵ�.
	for (int i = 0; i < V; i++)
	{
		if (results[i] == UNKNOWN)
			cout << i << ": ���� ��" << endl;
		else
			cout << i << ": " << results[i] << endl;
	}

	//���� ���� ��Ұ� �����ϴ��� �˻��ϴ� Kosaraju Algorithm
	auto components = Kosaraju(V, adj);
	

	//�ش� component�� Stuck�������� Ȯ���ϴ� ���̴�.
	//component�� ������ ��ұ��� push�� �� �� �� ��++�Ǳ� ������ -1��ŭ�� �ݺ��Ѵ�.
	for (int i=0;i<componentIndex;++i)
	{
		cout <<"component index: "<< i <<" "<<  isStuck[i] << endl;
	}
	cout << endl;

	for (int i = 0; i < components.size(); i++)
	{
		//isStuck�� �ش� ������ ���� ���� ��ҿ� ���� �ִ����� Ȯ���ϴ� ���̴�.
		if (isStuck[i])
		{
			for (auto node : components[i])
			{
				cout << node << " ";
			}

			cout << endl;
		}
	}

	//��� ���� ���� ��Ҹ� ����ϴ� �ڵ�
	for (int i = 0; i < components.size(); ++i)
	{
		cout << "components[" << i << "]: ";
		for (int j = 0; j < components[i].size(); ++j)
		{
			cout << components[i][j] << endl;
		}
	}
}