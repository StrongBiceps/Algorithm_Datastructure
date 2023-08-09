#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

//그래프의 에지를 표현하는 구조체를 정의하고, 에지 리스트로 그래프를 표현하는 Graph 클래스를 정의한다. Edge구조체와 Graph 클래스 정의는
//크루스칼 최소 신장 트리의 코드를 재활용한다.
template<typename T>
struct Edge
{
public:
	//main에서 정점 edge_map에 저장될 때 src는 정점을 의미하고 dst는 src와 연결된 정점이다.
	//둘 다 정점을 의미한다.
	//에지 양쪽 중 한 쪽을 의미하고
	unsigned src;
	//다른 한 쪽을 의미한다
	unsigned dst;
	T weight;

	//Edge 객체 비교는 가중치를 이용 -내림차순 비교
	bool operator<(const Edge<T>& e) const
	{
		return this->weight < e.weight;
	}
	bool operator>(const Edge<T>& e) const
	{
		return this->weight > e.weight;
	}
};

template<typename T>
class Graph
{
public:
	//N개의 정점으로 구성된 그래프
	Graph(unsigned N) :V(N) {}
	//그래프 정점 개수 반환
	auto vertices() const { return V; }
	//전체 에지 리스트 반환
	auto& edges() const { return edge_list; }
	//정점 v에서 나가는 모든 에지를 반환
	//나가는 에지를 반환하려면 에지의 src
	auto edges(unsigned v) const
	{
		vector<Edge<T>> edges_from_v;
		//main에서 Edge를 저장하는 방식을 보면 i.first(기준 정점 = src) j.first(연결된 정점 = dst) j.second(가중치)
		//이므로 Edge중에 src가 1인 Edge들은 1에서부터 연결된 정점을 의미한다. 따라서 src가 v인 모든 Edge들을 반환한다.
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
		//에지 양 끝 정점 ID가 유효한지 검사
		//e.src와 e.dst는 e와 연결된 정점을 의미하는데, 전체 개수인 V보다 큰 정점은 없기 때문에
		//유효한 범위인지 확인하는 작업
		if (e.src >= 1 && e.src <= V && e.dst >= 1 && e.dst <= V)
		{
			edge_list.emplace_back(e);
		}
		else
		{
			cerr << "에러: 유효 범위를 벗어난 정점!" << endl;
		}
	}
	//표준 출력 스트림 지원
	template<typename U>
	friend ostream& operator<<(ostream& os, const Graph<U>& G);
private:
	unsigned V; //정점 개수
	vector<Edge<T>> edge_list;
};

template<typename U>
ostream& operator<<(ostream& os, const Graph<U>& G)
{
	//1~8까지 반복하기 위해 <=를 사용한다. 원래 코드에서처럼 9를 넣으려면 <를 사용하면 되는데
	//원래 8개의 정점인데 9를 넣는 것은 직관적이지 않으므로 내가 바꿨다.
	for (unsigned i = 1; i < G.vertices(); ++i)
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

//해시 맵을 이용하여 그래프 컬러링에 사용할 색상을 정의한다.
unordered_map<unsigned, string> color_map =
{
	{1,"Red"},
	{2,"Blue"},
	{3,"Green"},
	{4,"Yellow"},
	{5,"Black"},
	{6,"White"}
};

//그래프 컬러링 알고리즘을 정의한다.

template<typename T>
auto greedy_coloring(const Graph<T>& G)
{
	auto size = G.vertices();

	//매개변수로 벡터의 크기만 전달했으므로 모두 0으로 초기화한다.
	vector<unsigned> assigned_colors(size);

	//1번 정점부터 차례대로 검사한다.
	for (unsigned i = 1; i < size; ++i)
	{
		//정점 i에서 뻗어나가는 에지들의 모음인 에지 리스트가 반환된다.
		auto outgoing_edges = G.edges(i);

		//1번째 정점과 인접해 있는 정점들의 현재 색상
		//키(정점)는 필요없고 주변 정점의 색만 중요하므로 set을 사용한다.
		set<unsigned> neighbours;

		for (auto& e : outgoing_edges)
		{
			//여기서 e는 i번 정점에서 나가는 엣지들이다. 따라서 이 엣지들의 src는 정점 i를 의미하고
			//dst가 i와 연결된 정점을 의미한다. 따라서 dst가 의미하는 색을 저장한다.
			//처음에는 0이 삽입된다.
			neighbours.insert(assigned_colors[e.dst]);
		}

		//인접한 정점에 칠해지지 않은 색상 중에서 가장 작은 숫자의 색상을 선택
		auto smallest = 1;

		//주변의 정점의 색깔을 저장한 neighbours에서 칠해지지 않은 색상을 검사한다.
		for (; smallest <= color_map.size(); ++smallest)
		{
			//매 반복마다 다른 색깔로 검사하여 없을 때 break한다.
			if (neighbours.find(smallest) == neighbours.end())
				break;
		}
		//for문을 벗어난 시점에서 인덱스i는 칠해지지 않은 색상 중에서 가장 ID가 가장 작은 색을
		//칠한다.
		assigned_colors[i] = smallest;
	}
	//각각 정점의 색을 저장한 assigned_colors를 반환한다.
	return assigned_colors;
}

//그래프 컬러링 결과를 화면에 출력하기 위한 함수를 추가한다.
template<typename T>
void print_colors(vector<T>& colors)
{
	for (auto i = 1; i < colors.size(); ++i)
	{
		cout << i << ": " << color_map[colors[i]] << endl;
	}
}

//main함수에서 그래프를 정의하고, 그래프 컬러링 알고리즘 구현 함수를 호출한다. 그래프
//컬러링이서는 에지 가중치를 사용하지 않기 때문에 그래프 객체 G의 모든 에지 가중치에 0으로 설정한다.
int main()
{
	using T = unsigned;

	//정점 1부터 의미가 있기 때문에 9로 설정해줘야 정점 8까지 취급할 수 있다.
	Graph<T> G(9);

	map<unsigned, vector<pair<unsigned, T>>> edge_map;
	edge_map[1] = { {2,0},{5,0} };
	edge_map[2] = { {1,0},{5,0},{4,0} };
	edge_map[3] = { {4,0},{7,0} };
	edge_map[4] = { {2,0},{3,0},{5,0},{6,0},{8,0} };
	edge_map[5] = { {1,0},{2,0},{4,0},{8,0} };
	edge_map[6] = { {4,0},{7,0},{8,0} };
	edge_map[7] = { {3,0},{6,0} };
	edge_map[8] = { {4,0},{5,0},{6,0} };

	for (auto& i : edge_map)
		for (auto& j : i.second)
			G.add_edge(Edge<T>{i.first, j.first, j.second});

	cout << "[입력 그래프]" << endl;
	cout << G << endl;

	auto colors = greedy_coloring<T>(G);
	cout << "[그래프 컬러링]" << endl;
	print_colors(colors);

	return 0;
}