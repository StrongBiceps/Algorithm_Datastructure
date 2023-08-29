#include <stack>
#include <algorithm>
#include <iostream>
#include <climits>
#include <fstream>
#include <vector>

//스택에 가장 마지막에 들어가는 강한 연결 요소가 고립된 방이다. 
//그래프에 강한 연결 요소(3개 이상의 정점으로 연결된)가 2개 이상 존재하더라도
//무조건 고립된 강한 연결 요소가 가장 먼저 스택에 들어가고 고립되지 않았다면
//스택에 먼저 들어가지 않는다. 왜냐하면 DFS과정에서 다른 연결 요소로 이동할 수 있기 때문이다.

//코사라주 예제에서 언급했듯이 가장 먼저 들어가는 성질 하나가지고는 고립된 요소를 판별할 수 없다.
//이 예제에서 고립된 요소를 판별하는 방법은 componentIndex를 활용하는 것이다. isStuck을 false로 설정하는
//원리는 역방향 그래프에서 해당 정점으로 연결된 정점이 false로 설정해주는 것이다. 즉 node가 인접 정점인
//next와 componentIndex가 다를 경우 node를 기준으로 next를 false로 설정하는 것이다. 따라서 고립된 강한
//연결 요소처럼 역방향 그래프에서 다른 정점이 고립된 연결 요소로 이동할 수 없기 때문에 고립된 연결 요소를 false로
//설정해줄 수 없기 때문에 고립된 것을 판별할 수 있는 것이다. 여기서 사용된 원리는 고립된 요소가 가장 먼저
//스택에 들어가는 것과는 관계가 없다.

//또한 IsStuck은 정점 단위로 다루는 것이 아니라 component단위(강한 연결 요소 단위)로 다룬다. 즉 고립된 강한 연결 요소는
//해당 연결 요소로 역방향 연결된 componentIndex가 다른 연결 요소가 없기 때문에 false로 설정되지 않는다. 하지만 고립되지 않은
//연결 요소는 해당 연결 요소로 역방향 연결된 다른 연결 요소가 있기 때문에 isStuck이 false로 설정된다. 코사라주 코드에서의 그래프를
//입력으로 실험해보면 2456은 837 연결 요소에 의해 false로 설정된다. 따라서 837만 고립된 결과로 나온다.
using namespace std;

//에지 클래스
class Edge
{
public:
	int src;
	int dst;
	int weight;
};

//각 정점을 기준으로 벨만 포드를 거친다음 해당 정점에서 어떤 정점이 가장 작은 거리로 다른 정점(무작위)로 이동할 수 있는지를 겨루는 게임

const int UNKNOWN = INT_MAX;

bool ReadTestCase(string filename, int& V, vector<Edge>& edges)
{
	ifstream infile(filename);

	if (!infile.is_open())
	{
		cout << "테스트 케이스 파일을 열 수 없습니다!" << endl;
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
	//스택에 저장되는 과정을 보기 위한 디버깅 출력문
	cout << " FillStack" << endl << node << endl;
	stack.push(node);
}

//강한 연결 요소를 판정하는 배열
vector<bool> isStuck;
vector<int> inComponent;
int componentIndex;

void CollectConnectedComponents(int node, vector<bool>& visited,
	vector<vector<int>>& adj, vector<int>& component)
{
	visited[node] = true;
	component.push_back(node);

	//inComponent는 해당 노드가 어떤 강한 연결 요소에 속해있는지 확인하는 배열이고,
	//componentIndex는 강한 연결 요소를 구분하는 Index이다.
	//서로 강하게 연결된 정점들을 같은 index로 묶어 관리하기 위해서다.
	inComponent[node] = componentIndex;

	//어떤 노드들이 어떤 연결 요소 인덱스로 설정되었는지 확인하기 위한 디버깅 출력문
	cout << "index:" << componentIndex << " node:" << node << endl;
	for (auto next : adj[node])
	{
		if (!visited[next])
		{
			//전치된 그래프에서 해당 node가 갈 수 있는 정점이 있는 지 확인하는 출력문
			cout << "has child" << endl;
			CollectConnectedComponents(next, visited, adj, component);
		}
		//vector<Edge> edges = { {0,1,0},{1,2,0},{2,3,0},{3,0,0} } 이런 형태의 모든 정점이 연결되어 있는 그래프일 때는
		//해당 for문에서 무한 루프에 빠진다고 착각할 수 있는데, 코드를 잘 보면 0->3->2->1 순으로 방문하다가 1에서 다시 0으로 방문할 것이다.
		//0은 이미 visited가 true인 상황이므로 CollectConnectedComponents를 다시 호출하지 않는다. 따라서 else if문으로 가게 되고 else if의
		//조건도 맞지 않으므로 1의 for문이 끝난다. 재귀를 따라 올라가며 for문을 종료하므로 무한 루프에 빠지지 않는다.
		else if (inComponent[node] != inComponent[next])
		{
			//isStuck이 false로 설정되는 과정을 보기 위한 디버깅 출력문
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

	////그 어떤 순서로 순회해도 고립된 강한 연결 요소부터 스택에 들어간다.
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
			//Index의 상승을 눈으로 보기 위한 디버깅 코드
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

	// 음수 가중치 사이클이 있으면 UNKNOWN 반환
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

	//벨만 포드를 수행한 그래프에서 가장 작은 거리 값을 리턴한다.
	return result;
}

int main()
{
	//코사라주 코드에서 언급한 고립된 요소가 무조건 연달아 먼저 들어가지는 않는다는 것을
	//확인하는 코드
	/*int V=6;
	vector<Edge> edges = { {0,1,0},{1,2,0},{2,3,0},{2,4,0},{1,5,0} };*/

	//모든 정점이 연결된 하나의 강한 연결 요소로 이루어진 유향 그래프일 경우
	int V = 4;
	vector<Edge> edges = { {0,1,0},{1,2,0},{2,3,0},{3,0,0} };

	//코사라주 코드의 그래프
	/*int V=9;
	vector<Edge> edges = { {0,1,0},{0,3,0},{1,4,0},{1,2,0},{2,3,0},{2,5,0},{3,7,0},{4,2,0},{5,4,0},{5,6,0},{6,7,0},{6,2,0},{7,8,0},{8,3,0} };*/

	//ReadTestCase("testcase4_maze.txt", V, edges);


	vector<vector<int>> adj(V);

	for (auto& e : edges)
	{
		adj[e.src].push_back(e.dst);
	}

	//각 정점을 기준으로 벨만 포드를 거친 최소 거리를 저장하는 배열
	vector<int> results;

	for (int i = 0; i < V; i++)
	{
		if (adj[i].empty())
		{
			results.push_back(UNKNOWN);
			continue;
		}

		int shortest = BellmanFord(edges, V, i);

		//음수 사이클 발생 경우
		if (shortest == UNKNOWN)
		{
			cout << "유효하지 않은 미로" << endl;
			return 0;
		}

		//각 정점 인덱스에 가장 작은 거리 값을 넣는다.
		results.push_back(shortest);
	}

	//그 어떤 정점으로도 이동할 수 없는 정점을 고립된 방이라고 하고 출력한다.
	for (int i = 0; i < V; i++)
	{
		if (results[i] == UNKNOWN)
			cout << i << ": 고립된 방" << endl;
		else
			cout << i << ": " << results[i] << endl;
	}

	//강한 연결 요소가 존재하는지 검사하는 Kosaraju Algorithm
	auto components = Kosaraju(V, adj);
	

	//해당 component가 Stuck상태인지 확인하는 것이다.
	//component는 마지막 요소까지 push한 후 한 번 더++되기 때문에 -1만큼을 반복한다.
	for (int i=0;i<componentIndex;++i)
	{
		cout <<"component index: "<< i <<" "<<  isStuck[i] << endl;
	}
	cout << endl;

	for (int i = 0; i < components.size(); i++)
	{
		//isStuck은 해당 정점이 강한 연결 요소에 속해 있는지를 확인하는 것이다.
		if (isStuck[i])
		{
			for (auto node : components[i])
			{
				cout << node << " ";
			}

			cout << endl;
		}
	}

	//모든 강한 연결 요소를 출력하는 코드
	for (int i = 0; i < components.size(); ++i)
	{
		cout << "components[" << i << "]: ";
		for (int j = 0; j < components[i].size(); ++j)
		{
			cout << components[i][j] << endl;
		}
	}
}