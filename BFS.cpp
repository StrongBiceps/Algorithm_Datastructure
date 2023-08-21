#include <iostream>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <vector>
using namespace std;

//�׷��� ������ �ǹ��ϴ� EdgeŬ�����̴�. ����� ���⿡ ��Ÿ�� EdgeŬ���� ���� �ڵ��
//ũ�罺Į MST �ڵ�� ���� ������, �� ������ �����ε��� ������� �ʾƼ� �������� �ʾҴ�.
template<typename T>
class Edge
{
public:
	unsigned src;
	unsigned dst;
	T Weight;
};

//������ �׷����� ǥ���ϴ� Graph Ŭ���� �����̴�. �� Ŭ������ ���� ����Ʈ�� �̿��Ͽ� �׷����� ǥ���ϰ�
//ǥ�� ��Ʈ�� ����� �����Ѵ�. ����� ���⿡ ��Ÿ�� Graph Ŭ���� ���� �ڵ�� ũ�罺Į MST �ڵ�� ������ ����.
template <typename T>
class Graph
{
public:
	// N���� �������� ������ �׷���
	Graph(unsigned N) : V(N) {}

	// �׷����� ���� ���� ��ȯ
	auto vertices() const { return V; }

	// ��ü ���� ����Ʈ ��ȯ
	auto& edges() const { return edge_list; }

	// ���� v���� ������ ��� ������ ��ȯ
	auto edges(unsigned v) const
	{
		vector<Edge<T>> edges_from_v;
		for (auto& e : edge_list)
		{
			if (e.src == v)
				edges_from_v.emplace_back(e);
		}

		return edges_from_v;
	}

	void add_edge(Edge<T>&& e)
	{
		// ���� �� �� ���� ID�� ��ȿ���� �˻�
		if (e.src >= 1 && e.src <= V && e.dst >= 1 && e.dst <= V)
			edge_list.emplace_back(e);
		else
			cerr << "����: ��ȿ ������ ��� ����!" << endl;
	}

	// ǥ�� ��� ��Ʈ�� ����
	template <typename U>
	friend ostream& operator<< (ostream& os, const Graph<U>& G);

private:
	unsigned V;		// ���� ����
	vector<Edge<T>> edge_list;
};

template <typename T>
ostream& operator<< (ostream& os, const Graph<T>& G)
{
	for (unsigned i = 1; i < G.vertices(); i++)
	{
		os << i << ":\t";

		auto edges = G.edges(i);
		for (auto& e : edges)
			os << "{" << e.dst << ": " << 0 << "}, ";

		os << endl;
	}

	return os;
}

//�׷����� �����ϰ� ��ȯ�ϴ� �Լ��� �ۼ��Ѵ�.
template <typename T>
auto create_reference_graph()
{
	Graph<T> G(9);

	map<unsigned, vector<pair<unsigned, T>>> edge_map;
	edge_map[1] = { {2, 0}, {5, 0} };
	edge_map[2] = { {1, 0}, {5, 0}, {4, 0} };
	edge_map[3] = { {4, 0}, {7, 0} };
	edge_map[4] = { {2, 0}, {3, 0}, {5, 0}, {6, 0}, {8, 0} };
	edge_map[5] = { {1, 0}, {2, 0}, {4, 0}, {8, 0} };
	edge_map[6] = { {4, 0}, {7, 0}, {8, 0} };
	edge_map[7] = { {3, 0}, {6, 0} };
	edge_map[8] = { {4, 0}, {5, 0}, {6, 0} };

	for (auto& i : edge_map)
		for (auto& j : i.second)
			G.add_edge(Edge<T>{ i.first, j.first, j.second });

	return G;
}

//�ʺ� �켱 Ž�� �˰����� ������ ���� �����Ѵ�.
template<typename T>
auto breadth_first_search(const Graph<T>& G, unsigned start)
{
	queue<unsigned> queue;
	set<unsigned> visited; //�湮�� ����
	vector<unsigned> visit_order; //�湮 ����
	queue.push(start);

	while (!queue.empty())
	{
		auto current_vertex = queue.front();
		queue.pop();

		//���� ������ ������ �湮���� �ʾҴٸ�
		if (visited.find(current_vertex) == visited.end())
		{
			visited.insert(current_vertex);
			visit_order.push_back(current_vertex);

			for (auto& e : G.edges(current_vertex))
			{
				//������ ���� �߿��� �湮���� ���� ������ �ִٸ� ť�� �߰�
				if (visited.find(e.dst) == visited.end())
				{
					queue.push(e.dst);
				}
			}
		}
	}
	return visit_order;
}

//BFS�˰����� �����Ѵ�. ���� ������ ���Ƿ� 1������ �����Ѵ�.
int main()
{
	using T = unsigned;

	//�׷��� ��ü ����
	auto G = create_reference_graph<T>();
	cout << "[�Է� �׷���]" << endl;
	cout << G << endl;

	auto bfs_visit_order = breadth_first_search(G, 1);
	for (const auto& v : bfs_visit_order)
		cout << v << endl;
}