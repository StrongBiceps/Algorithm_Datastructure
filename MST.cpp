#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

//�� Ŭ�������� ID�� 1���� 8���� �����ȴ�. ������ vector�� index�� 0~7�����̴�.
//���� -1�� ����ؼ� �ε����� �־�� out of range�� ���� �ʴ´�.
//���� �ڵ�� 9�� �ְ� �Ǿ� �־ -1�� �ȵǾ� ������ ���������� �ʾƼ� ���� 8�� �ֱ� ���� �ٲ� ���̴�.
class SimpleDisjointSet
{
private:
	class Node
	{
	public:
		//unsigned int = unsigned
		unsigned id;
		unsigned rank;
		unsigned parent;

		Node(unsigned _id) :id(_id), rank(0), parent(_id) {}

		bool operator!=(const Node& n) const
		{
			//id�� �������� ���Ѵ�.
			return this->id != n.id;
		}
	};
	//���� ó���� �߰��Ǵ� ����� �ڷ�������, Ʈ���� �����Ѵ�.
	vector<Node> nodes;
public:
	SimpleDisjointSet(const unsigned& N)
	{
		nodes.reserve(N);
	}
	void make_set(const unsigned& x)
	{
		nodes.emplace_back(x);
	}
	unsigned find(const unsigned& x)
	{
		auto node_it = find_if(nodes.begin(), nodes.end(),
			[x](auto n) { return n.id == x; });
		unsigned node_id = (*node_it).id;

		while (node_id != nodes[node_id-1].parent)
		{
			node_id = nodes[node_id-1].parent;
		}
		return node_id;
	}
	void union_set(unsigned x, unsigned y)
	{
		auto root_x = find(x);
		auto root_y = find(y);

		//���� x�� y�� ���� Ʈ���� �ִٸ� �״�� ����
		if (root_x == root_y)
			return;

		//���� ��ũ�� Ʈ���� ū ��ũ�� Ʈ�� ������ ����
		//ó���� �Ű� ������ ���޹��� �� �� �� ���� �޾Ƶ��̴� ��������� ������ �ʰ�
		//�� �� ��ũ�� ū ���� ��Ʈ�� �ȴ�. �Ʒ� �� �ڵ尡 x�� parent�� y�� parent�� �ٲٱ� ������
		//���⼭ swap�� �ؼ� �� ū ��ũ�� parent�� ���Եǰ� �Ѵ�.
		//���� root_x���� root_y�� ��ũ�� �� ũ�ٸ� �׳� �Ʒ� �ڵ�ó�� �����ϸ� �ȴ�.
		if (nodes[root_x-1].rank > nodes[root_y-1].rank)
			swap(root_x, root_y);

		//�Ʒ� ���� ���� ��ũ�� ���ų� root_y�� ��ũ�� �� ū ����̴�.
		//root_x�� �Ʒ��� ���� ����̰�, root_y�� �޾Ƶ��̴� ��Ʈ ����̴�.
		nodes[root_x-1].parent = nodes[root_y-1].parent;

		//�ڽ��� �ϳ� �� �þ����Ƿ� ��ũ�� �߰��Ѵ�.
		nodes[root_y-1].rank++;
	}
};

//������Ʈ �� �ڷᱸ���� ���������� ���� �׷��� �ڷ� ������ �����Ѵ�. 
//Edge list�� �̿��Ͽ� �����Ѵ�.
//���� ����ü�� ���ø����� �����߱� ������ <�����ڿ� >�����ڸ� �����ϴ� ��� ������ Ÿ���� ���� ����ġ�� ����� �� �ִ�.
//������ �ܼ��� ���� �����ϴ� ���� �ƴ϶� ����� ���� ������ ����ġ���� �����Ѵ�.
template<typename T>
struct Edge
{
public:
	//main���� ���� edge_map�� ����� �� src�� ������ �ǹ��ϰ� dst�� src�� ����� �����̴�.
	//�� �� ������ �ǹ��Ѵ�.
	//���� ���� �� �� ���� �ǹ��ϰ�
	unsigned src;
	//�ٸ� �� ���� �ǹ��Ѵ�
	unsigned dst;
	T weight;

	//Edge ��ü �񱳴� ����ġ�� �̿� -�������� ��
	bool operator<(const Edge<T>& e) const
	{
		return this->weight < e.weight;
	}
	bool operator>(const Edge<T>& e) const
	{
		return this->weight > e.weight;
	}
};

//�׷��� �ڷ� ������ ������ graph Ŭ������ �����Ѵ�. graphŬ������ << �����ڸ� �̿��Ͽ� �׷��� ������ ����� �� �ִ�.
template<typename T>
class Graph
{
public:
	//N���� �������� ������ �׷���
	Graph(unsigned N) :V(N) {}
	//�׷��� ���� ���� ��ȯ
	auto vertices() const { return V; }
	//��ü ���� ����Ʈ ��ȯ
	auto& edges() const { return edge_list; }
	//���� v���� ������ ��� ������ ��ȯ
	//������ ������ ��ȯ�Ϸ��� ������ src
	auto edges(unsigned v) const
	{
		vector<Edge<T>> edges_from_v;
		//main���� Edge�� �����ϴ� ����� ���� i.first(���� ���� = src) j.first(����� ���� = dst) j.second(����ġ)
		//�̹Ƿ� Edge�߿� src�� 1�� Edge���� 1�������� ����� ������ �ǹ��Ѵ�. ���� src�� v�� ��� Edge���� ��ȯ�Ѵ�.
		for (const auto& e : edge_list)
		{
			if (e.src == v)
			{
				edges_from_v.emplace_back(e);
			}
		}
		return edges_from_v;
	}
	void add_edge(Edge<T>&& e)
	{
		//���� �� �� ���� ID�� ��ȿ���� �˻�
		//e.src�� e.dst�� e�� ����� ������ �ǹ��ϴµ�, ��ü ������ V���� ū ������ ���� ������
		//��ȿ�� �������� Ȯ���ϴ� �۾�
		if (e.src >= 1 && e.src <= V && e.dst >= 1 && e.dst <= V)
		{
			edge_list.emplace_back(e);
		}
		else
		{
			cerr << "����: ��ȿ ������ ��� ����!" << endl;
		}
	}
	//ǥ�� ��� ��Ʈ�� ����
	template<typename U>
	friend ostream& operator<<(ostream& os, const Graph<U>& G);

private:
	unsigned V; //���� ����
	vector<Edge<T>> edge_list;
};

template<typename U>
ostream& operator<<(ostream& os, const Graph<U>& G)
{
	//1~8���� �ݺ��ϱ� ���� <=�� ����Ѵ�. ���� �ڵ忡��ó�� 9�� �������� <�� ����ϸ� �Ǵµ�
	//���� 8���� �����ε� 9�� �ִ� ���� ���������� �����Ƿ� ���� �ٲ��.
	for (unsigned i = 1; i <= G.vertices(); ++i)
	{
		os << i << ":\t";
		auto edges = G.edges(i);
		for (auto& e : edges)
		{
			os << "{" << e.dst << ": " << e.weight << "},";
		}
		os << endl;
	}
	return os;
}

//ũ�罺Į �ּ� ���� Ʈ�� �˰����� �����Ѵ�.
template<typename T>
Graph<T> minimum_spanning_tree(const Graph<T>& G)
{
	//���� ����ġ�� �̿��� �ּ� �� ����
	//Edge<T>�� �����ϰ�, vector�� �����Ǿ� ������, greater�� ����Ͽ� �ּ� ���� �����Ѵ�.
	//less�� ����ϸ� �ִ� ���� �ȴ�.
	priority_queue<Edge<T>, vector<Edge<T>>, greater<Edge<T>>> edge_min_heap;

	for (auto& e : G.edges())
	{
		edge_min_heap.push(e);
	}

	//���� ������ �ش��ϴ� ũ���� ������Ʈ-�� �ڷ� ���� ���� �� �ʱ�ȭ
	auto N = G.vertices();
	SimpleDisjointSet dset(N);
	//ID�� 1���� �����ϱ� ���� 1���� N���� �ݺ��� ������.
	for (unsigned i = 1; i <= N; ++i)
	{
		dset.make_set(i);
	}

	//������Ʈ �� �ڷᱸ���� �̿��Ͽ� �ּ� ���� Ʈ�� ���ϱ�
	Graph<T> MST(N);
	while (!edge_min_heap.empty())
	{
		//�ּ� ������ �ּ� ����ġ ������ ����
		auto e = edge_min_heap.top();
		edge_min_heap.pop();

		//������ ������ ����Ŭ�� �������� ������ �ش� ������ MST�� �߰�
		if (dset.find(e.src) != dset.find(e.dst))
		{
			MST.add_edge(Edge<T>{e.src, e.dst, e.weight});
			dset.union_set(e.src, e.dst);
		}
	}
	return MST;
}

int main()
{
	using T = unsigned;

	//�׷��� ��ü ����
	Graph<T> G(8);

	map<unsigned, vector<pair<unsigned, T>>> edge_map;
	//edge_map�� �ε����� ������ �ǹ��Ѵ�.
	//pair�� unsigned�� ������ �ǹ��Ѵ� .T�� ����ġ�� �ǹ��Ѵ�.
	//edge_map[1]�� {5,3}�� ���� ���
	//Edge(1,5,3)�� �� ���̴�. �� �ǹ̴� ���� 1�� �������� ����� ������ 5�� �� ����ġ�� 3�̶�� ����.
	edge_map[1] = { {2,2},{5,3} };
	edge_map[2] = { {1,2},{5,5},{4,1} };
	edge_map[3] = { {4,2},{7,3} };
	edge_map[4] = { {2,1},{3,2},{5,2},{6,4},{8,5} };
	edge_map[5] = { {1,3},{2,5},{4,2},{8,3} };
	edge_map[6] = { {4,4},{7,4},{8,1} };
	edge_map[7] = { {3,3},{6,4} };
	edge_map[8] = { {4,5},{5,3},{6,1} };

	for (auto& i : edge_map)
	{
		for (auto& j : i.second)
		{
			G.add_edge(Edge<T>{i.first, j.first, j.second});
		}
	}
	cout << "[�Է� �׷���]" << endl;
	cout << G << endl;

	Graph<T> MST = minimum_spanning_tree(G);
	cout << "[�ּ� ���� Ʈ��]" << endl;
	cout << MST;
}