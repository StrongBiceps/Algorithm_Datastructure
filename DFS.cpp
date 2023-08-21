#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <stack>

using namespace std;

//그래프의 Edge와 Graph 클래스는 BFS 코드의 것을 그대로 사용한다.

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
	// N개의 정점으로 구성된 그래프
	Graph(unsigned N) : V(N) {}

	// 그래프의 정점 개수 반환
	auto vertices() const { return V; }

	// 전체 에지 리스트 반환
	auto& edges() const { return edge_list; }

	// 정점 v에서 나가는 모든 에지를 반환
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
		// 에지 양 끝 정점 ID가 유효한지 검사
		if (e.src >= 1 && e.src <= V && e.dst >= 1 && e.dst <= V)
			edge_list.emplace_back(e);
		else
			cerr << "에러: 유효 범위를 벗어난 정점!" << endl;
	}

	// 표준 출력 스트림 지원
	template <typename U>
	friend ostream& operator<< (ostream& os, const Graph<U>& G);

private:
	unsigned V;		// 정점 개수
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

//깊이 우선 탐색을 구현한 함수를 작성한다. 이 함수의 구성은 BFS 코드와 비슷하다. 다만 queue대신 stack을 
//사용한다는 점이 다르다.

template<typename T>
auto depth_first_search(const Graph<T>& G, unsigned start)
{
	stack<unsigned> stack;
	set<unsigned> visited;
	vector<unsigned> visit_order;
	stack.push(start);

	while (!stack.empty())
	{
		auto current_vertex = stack.top();
		stack.pop();

		//현재 정점을 이전에 방문하지 않았다면
		if (visited.find(current_vertex) == visited.end())
		{
			visited.insert(current_vertex);
			visit_order.push_back(current_vertex);

			for (auto& e : G.edges(current_vertex))
			{
				//인접한 정점 중에서 방문하지 않은 정점이 있다면 스택에 추가
				if (visited.find(e.dst) == visited.end())
				{
					stack.push(e.dst);
				}
			}
		}
	}
	return visit_order;
}

int main()
{
	using T = unsigned;

	//그래프 객체 생성
	auto G = create_reference_graph<T>();
	cout << "[입력 그래프]" << endl;
	cout << G << endl;

	//1번 부터 DFS실행 & 방문 순서 출력
	auto dfs_visit_order = depth_first_search(G, 1);
	for (auto v : dfs_visit_order)
		cout << v << endl;
}