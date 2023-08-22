#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <limits>
#include <string>

using namespace std;

template <typename T>
struct Edge
{
	unsigned src;
	unsigned dst;
	T weight;
};

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

template <typename U>
ostream& operator<< (ostream& os, const Graph<U>& G)
{
	for (unsigned i = 1; i < G.vertices(); i++)
	{
		os << i << ":\t";

		auto edges = G.edges(i);
		for (auto& e : edges)
			os << "{" << e.dst << ": " << e.weight << "}, ";

		os << endl;
	}

	return os;
}

//������ ����ġ�� ���ǵ� �׷����� ��ȯ�Ѵ�.
template <typename T>
auto create_reference_graph()
{
	Graph<T> G(9);

	map<unsigned, vector<pair<unsigned, T>>> edge_map;
	edge_map[1] = { {2, 2}, {5, 3} };
	edge_map[2] = { {1, 2}, {5, 5}, {4, 1} };
	edge_map[3] = { {4, 2}, {7, 3} };
	edge_map[4] = { {2, 1}, {3, 2}, {5, 2}, {6, 4}, {8, 5} };
	edge_map[5] = { {1, 3}, {2, 5}, {4, 2}, {8, 3} };
	edge_map[6] = { {4, 4}, {7, 4}, {8, 1} };
	edge_map[7] = { {3, 3}, {6, 4} };
	edge_map[8] = { {4, 5}, {5, 3}, {6, 1} };

	for (auto& i : edge_map)
		for (auto& j : i.second)
			G.add_edge(Edge<T>{ i.first, j.first, j.second });

	return G;
}

//������ ���κ��� �Ÿ� ������ �����ϱ� ���� ����� Lable ����ü�� �����Ѵ�.
//Lable ��ü �񱳴� �Ÿ� ���� �̿��ϵ��� �� �����ڸ� �����ε��Ѵ�.
template <typename T>
struct Label
{
	unsigned ID;
	T distance;

	// Label ��ü �񱳴� �Ÿ�(distance) ���� �̿�
	inline bool operator> (const Label<T>& l) const
	{
		return this->distance > l.distance;
	}
};


//���� ������������ ����ġ�� ���� ���� �������� �湮�Ѵ�. �Ÿ� ���� ����ġ���� ũ�� ����ġ��
//�������� ������ ���ϹǷ� �Ÿ��� ����ġ�� ������Ʈ�Ѵ�. 
//��� �Ÿ��� ������ ����ġ�� ���ٰ� ���� �ȴ�. �Ÿ��� �߰��ϴ� ���� �ǹ̰� ���� Ʈ���� ��谡 �о��� ������ Ʈ���� ��踦 �����ϴ� ������ �߿���
//���� ����ġ�� ���� ������ �����Ѵٰ� ���� �ȴ�.
template <typename T>
auto prim_MST(const Graph<T>& G, unsigned src)
{
	// �ּ� ��
	//�Ÿ��� ���� ���� ������ Top�� ��ġ�Ѵ�.
	//Label<T> �ڷ����� vector<Label<T>>�����̳ʿ� �����ϰ�, ��ü �񱳿��� greater<Lable<T>> �Լ� ��ü�� ����Ѵ�.
	priority_queue<Label<T>, vector<Label<T>>, greater<Label<T>>> heap;

	// ��� �������� �Ÿ� ���� �ִ�� ����
	vector<T> distance(G.vertices(), numeric_limits<T>::max());

	set<unsigned> visited;	// �湮�� ����
	vector<unsigned> MST;	// �ּ� ���� Ʈ��

	//���� ������ heap�� �ִ´�.
	//priority_queue�� ���Ҹ� ������ ������ �ڵ����� �����Ѵ�.
	heap.emplace(Label<T>{src, 0});

	while (!heap.empty())
	{
		//�Ÿ� ���� ���� ���� ������ ���õȴ�.
		auto current_vertex = heap.top();
		heap.pop();

		//���� ���� ������ �湮�ߴٸ� �ƹ��� �۾��� ���� �ʴ´�.
		//�׷��� ���� ������ ������ �湮���� �ʾҴٸ� ���� �۾��� �����Ѵ�.
		if (visited.find(current_vertex.ID) == visited.end())
		{
			//�湮�� ������ �ּ� ���� Ʈ���� ���� �ִ´�.
			MST.push_back(current_vertex.ID);

			//���� �������� ���� ������ ������ ����Ʈ�� Ȱ���Ͽ� ���� �������� �Ÿ��� �ٽ� �����Ѵ�.
			for (auto& e : G.edges(current_vertex.ID))
			{
				auto neighbor = e.dst;
				auto new_distance = e.weight;

				// ������ ������ �Ÿ� ���� ���ο� ��ο� ���� �Ÿ� ������ ũ��
				// ���� �߰��ϰ�, �Ÿ� ���� ������Ʈ��.
				if (new_distance < distance[neighbor])
				{
					heap.emplace(Label<T>{neighbor, new_distance});
					distance[neighbor] = new_distance;
				}
			}

			//�湮�� ������ ���� ������ �߰��Ѵ�.
			visited.insert(current_vertex.ID);
		}
	}

	for (const auto& i : distance)
	{
		cout << i << " ";
	}
	cout << endl;
	return MST;
}

int main()
{
	using T = unsigned;

	// �׷��� ��ü ����
	auto G = create_reference_graph<T>();
	cout << "[�Է� �׷���]" << endl;
	cout << G << endl;

	auto MST = prim_MST<T>(G, 1);

	cout << "[�ּ� ���� Ʈ��]" << endl;
	for (auto v : MST)
		cout << v << endl;
	cout << endl;
}