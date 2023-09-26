#include <map>
#include <algorithm>
#include <vector>
#include <iostream>

//벨만 포드 알고리즘과 다른 점은 벨만 포드 알고리즘은 모든 에지에 대해 V-1번 검사를 진행해야 하지만, DP방식의 아래 코드는
//목표 정점부터 시작 정점까지 거슬러 올라가며 모든 경우의 수를 검토하므로 각 에지에 대해 V-1번 검사를 하는 로직과는 다르다
//즉 목표 정점부터 시작 정점까지 연결된 모든 경로의 비용을 검토하여 업데이트하는 방식이다. 따라서 반복문이 아닌 재귀방식이
//사용된다.
/* 아래 코드를{0,1,3}
			  {1,2,2}
			  {2,3,1}
			  {3,1,5}

			  0->1->2->3
				 <------
의 그래프를 입력으로 사용해서 이해해봐라.

전치 그래프는 다음과 같다.

			{1,0,3}
			{2,1,2}
			{3,2,1}
			{1,3,5}

			0<-1<-2<-3
				----->


				그래프 2
			{0,1,3}
			{1,2,2}
			{2,3,1}
			{2,4,4}
			{3,5,2}
			{3,5,1}

			0->1->2->3->5
				   ->4->

			전치 그래프

			0<-1<-2<-3<-5
				   <-4<-

					그래프 3
			{0,1,3}
			{1,2,2}
			{2,3,1}
			{2,4,4}

			0->1->2->3
				   ->4

			전치 그래프

			0<-1<-2<-3
				   <-4
*/

//위에서 마지막 그래프를 입력으로 할 때를 살펴보면, 전치 그래프에서 정점 5에 대해서 재귀를 진행할 때, 0까지 재귀가 깊어진 후
//리턴된 값들이 이전 재귀에 사용되고 있다. 이 방법은 하향식 방법이다. 현재 값이 다음 재귀에 영향을 주는 상향식하고는 다른 방법이다.
//또한 위 그래프에서 메모이제이션에서의 중복 계산 방지가 나타날 수 있다. 3,4에서 출발한다고 하면, 2로 갈 때 깊이와 노드가 같은 중복 계산이 발생한다.
//따라서 3이 먼저 호출되므로 4에서 memo[{2,3}]을 중복 값으로 사용하게 된다. 즉 3에서 이미 2까지의 거리는 계산이 끝났으므로 4에서는 2부터 출발 지점까지의
//거리를 계산할 필요가 없다. 같은 경로이기 때문이다. 따라서 2이후의 재귀는 방지된다.
using namespace std;

const int UNKNOWN = 1e9;

//정점 개수를 나타내는 V와 E를 전역 변수로 선언한다. 또한 인접 리스트를 나타내는 adj와 에지 가중치를 저장할
//weight를 2차원 정수 벡터 자료형으로 선언한다. 마지막으로 메모이제이션 테이블을 저장할 memo를 선언한다.
//이때 map을 사용하여 이미 키가 존재하는지, 그리고 값이 UNKNOWN인지를 확인한다.
int V, E;
vector<vector<int>> weight;
vector<vector<int>> adj;

//ex)SP(1,7): UNKNOWN
//map<pair<정점,깊이>,거리>
map<pair<int, int>, int> memo;


//새로운 함수를 정의한다. 이 함수는 정수형 depth와 node,2차원 정수 벡터 adj와 weight를 인자로 받는다. 이때 adj와 weight는 참조형
//으로 선언한다.
//이 함수는 전치 그래프로 거리를 업데이트한다. 따라서 각 정점에서 source까지 가는 정점에 대한 업데이트를 진행하는 함수이다.


//벨만-포드와는 반대로 V-1에서 1까지 업데이트한다. 재귀는 depth = 0까지 도달하나, 0에서는 거리의 업데이트가 일어나지 않고 값을 무조건 반환한다.
//만약 depth 0일 때는 memo[{i,0}]에 대해서는 모두 값이 UNKNOWN 아니면 0이다. 따라서 무조건 값을 반환하게 되어 있다. 즉 거리는 V-1번 업데이트된다.
//즉 V번의 업데이트를 막았으므로 사이클을 방지한다. 하지만 음의 가중치 사이클이 존재하는 그래프는 원래 최단 거리를 구할 수 없다. 무한 재귀를 막는 것일 뿐이다.

//이 알고리즘은 전치 그래프를 사용하여 도착 지점에서 출발 지점으로 거슬러 올라간다. 이 과정에서 재귀를 통해서 도착 지점에서 출발 지점까지 가능한 모든 경로의
//거리를 비교하여 업데이트한다.
int ShortestPath_Memoization(int depth, int node,
	vector<vector<int>>& adj, vector<vector<int>>& weight)
{
	//이 알고리즘에서는 일반적인 깊이 우선 탐색을 사용하며, 다만 함수 끝 부분에서 {node,depth} 쌍에 대한 결과를 memo에 저장한다.
	//함수 시작 부분에서는 memo를 확인하여, 해당 키가 이미 존재하면 저장된 값을 반환한다.

	// 맵에 키가 있는지를 확인
	//source가 node로 들어오게 된다면 0이 반환되게 된다.
	//source가 0일 때는 1부터 if문 아래 코드들이 실행되게 된다.

	cout << "memoization called(" << node << ", " << depth << ")" << endl << endl;
	if (memo.find({ node, depth }) != memo.end())
	{
		cout << "memo[{" << node << ", " << depth << "}] 중복: " << memo[{node, depth}] << endl;
		return memo[{node, depth}];
	}

	cout << "memo[{" << node << ", " << depth << "}] = UNKNOWN" << endl;

	//해당 depth에서 방문한 적 없는 정점이라면 일단 UNKNOWN으로 하고 dist와 비교한다.
	//min을 통해서 더 작은 값을 찾아야 하기 때문에 벨만 포드에서 처음에 모든 거리를 UNKNOWN으로 하는 원리와 비슷하다.
	memo[{node, depth}] = UNKNOWN;

	// 인접한 에지에 대해 반복
	//node에서 갈 수 있는 정점이 여러 개라면 memo[{node,depth}]는 아래 for문을 통해서 모든 경로를 계산해 그 중 가장 작은 값으로
	//테이블을 업데이트할 것이다.
	for (auto next : adj[node])
	{
		//전치 그래프에서 node에서 next로 가는 에지 가중치를 의미한다.
		int w = weight[node][next];
		//역방향으로 가는 다음 정점의 거리값에 현재 에지 가중치를 더한다.
		//코드 최상단의 가장 마지막 그래프를 입력으로 사용할 때를 생각해보자.
		//distance[1]에 대한 재귀에서, memoization(1,4)가 호출될 것이고, 
		//memo[{1,4}] = UNKNOWN으로 설정되고, memoization(0,3)이 호출될 것이다.
		//여기서 memo[{0,3}]은 0에서 0으로 가는 경우라 0으로 설정되어 있고 중복이라 
		//0이 리턴된다. 그럼 다시 memoization(1,4)로 넘어가서 dist값이 3으로 설정되고(+w로 인해서)
		//UNKNOWN과 3중에 3이 작으므로 1에서 0으로 가는 경우는 3으로 업데이트된다.

		//또한 memo[{source,0}] = 0이 아니라 UNKNOWN으로 설정해야 하는 것 아닌가 라고 착각할 수 있는데,
		//만약 위 그래프 예의 마지막 그래프에서 4->3의 에지가 추가된다면 3에서 0까지 가는 거리는 4개의 에지가 되고
		//0에 도착할 때 depth = 0이 된다. 따라서 source에 대해서는 0까지는 유효하다. 또한 0까지의 거리는 4개인데 V-1에 충족하므로
		//사이클도 아니다.
		int dist = ShortestPath_Memoization(depth - 1, next, adj, weight) + w;

		//이전에 저장되었던 캐시와 새롭게 계산된 거리 값을 비교하여 더 작은 것으로 업데이트
		memo[{node, depth}] = min(memo[{node, depth}], dist);

		cout << "distance update: " << "memo[{" << node << ", " << depth << "}] = " << memo[{node, depth}] << endl;
	}

	return memo[{node, depth}];
}

//새로운 함수를 정의한다. 이 함수는 시작 정점 인덱스를 나타내는 source를 인자로 받고, 정수형 벡터를 반환한다.
vector<int> SingleSourceShortestPaths(int source)
{
	//입력 그래프에 대해 몇 가지 미리 수정할 것이 있다. 시작 정점에서 그래프의 다른 정점으로 이동하는 것 대신, 역으로
	//각각의 정점에서 시작 정점으로 이동하는 최단 경로를 계산할 것이다. 입력 그래프가 방향 그래프이기 때문에 입력 그래프의
	//전치 그래프를 생성하여 사용한다.
	vector<vector<int>> adj_t(V);
	vector<vector<int>> weight_t(V, vector<int>(V, UNKNOWN));

	//모든 정점에 대한 것이 기록되는 것이 아니라 하나의 시작 지점에 대한 경로를 저장하기 때문에
	//각 정점에 대해 함수가 호출될 때 memo를 비워준다. 즉 source가 0일 때는 0에 대한 값들만 저장된다.
	//memo[{source, i}]는 0에서 출발하여 0으로 간다는 이야기이다. 따라서 0이다.
	//source가 1일 때는 memo[{source,i}]는 1에서 출발하여 1로 간다는 이야기니까 0이다.
	//i는 source에 대한 모든 정점의 최단 거리를 계산할 때의 반복 횟수를 의미한다. 반복 변수가 감소하다가
	//depth까지 오면 해당 경로는 없는 것으로 간주한다. 즉 V-1번 반복을 해도 시작 정점으로 거꾸로 도달할 수 없다는 이야기이다.
	memo.clear();

	//여기서 전치 그래프의 인접 리스트와 가중치 행렬을 나타내기 위해 두 개의 2차원 정수 벡터 adj_t와 weight_t를 정의했다.
	//이후 중첩 for문을 이용하여 전치 그래프를 생성하고 memo 테이블을 초기화했다.
	for (int i = 0; i < V; i++)
	{
		cout << "source: " << source << endl << endl;
		// 전치 그래프 생성
		//각 반복에서 각 정점의 인접 정점들만 전치시킨다.
		//한 번에 모든 그래프를 전치시키는 것이 아니다.
		for (auto j : adj[i])
		{
			cout << i << " 정점" << endl;
			adj_t[j].push_back(i);
			weight_t[j][i] = weight[i][j];
			cout << "에지 전치 진행" << endl;
			cout << endl;
		}
		cout << "전치 종료" << endl << endl;
		// 기저 조건 - 시작 정점에서 자기 자신까지의 최단 거리는 항상 0
		//각 반복에서 시작 정점에서 자기 자신까지의 최단 거리는 항상 0이다.
		cout << "memo[{" << source << " , " << i << "}] = 0" << endl;
		memo[{source, i}] = 0;

		if (i != source)
		{
			//반복을 진행하다가 source에서 i로 갈 때 depth가 0이라면 경로는 없는 것이다.
			//다시 말하면 source에서 i로 가기 위해서 반복을 진행하는 데 depth가 0이 되면 UNKNOWN이라는 말이다.
			// V-1 반복 후 소스 이외의 노드에 도달한 경우,
			// 경로가 존재하지 않음
			cout << i << " != " << source << endl;
			//각 정점에서 거꾸로 시작 정점으로 가는 것을 기록하는 것이기 때문에 현재 반복문에서
			//source가 아닌 모든 정점에 대해 depth 0에 대해서 UNKNOWN 작업을 해주려고 하는 것이다.
			//거꾸로 가는 것이기 때문에 source가 아닌 다른 값은 전부 경로가 없는 것이다.

			//depth가 0으로 감소하면 경로가 존재하지 않는 것으로 설정한다.
			//따라서 source외의 정점에 도달한다면 depth 0에 해당하는 pair를 UNKNOWN으로 설정한다.
			memo[{i, 0}] = UNKNOWN;
			cout << "memo[{" << i << ", 0}] = UNKNOWN" << endl << endl;
		}
	}

	//크기가 V인 정수 벡터 distance를 정의한다. 그리고 이 벡터를 memoization함수 반환값으로 채운다.
	vector<int> distance(V);

	for (int i = 0; i < V; i++)
	{
		//0부터 시작해서 V-1번 반복한다. 전달되는 첫 번째 매개변수는 Depth이다.
		//두 번째 매개변수는 

		//source가 0일 때 distance[0]=0이다.
		cout << i << "Called" << endl << endl << endl;
		distance[i] = ShortestPath_Memoization(V - 1, i, adj_t, weight_t);
	}

	return distance;
}

//메인함수에서 입력을 처리하여 알고리즘을 적용할 그래프 구조를 생성한다. 첫 번째 줄에서는 V와 E를 입력으로 받고,
//이후 E개의 줄에서는 u,v,w를 나타내는 정수를 입력으로 받는다. 여기서 u,v,w는 시작 정점, 목표 정점, 두 정점 사이의 가중치를 나타낸다.
int main()
{
	cin >> V >> E;

	//가중치 표현
	weight.resize(V, vector<int>(V, UNKNOWN));

	//그래프 간의 연결 표현
	adj.resize(V);

	for (int i = 0; i < E; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;

		adj[u].push_back(v);
		weight[u][v] = w;
	}

	//2차원 정수 벡터 path를 정의한다. 그리고 0번 부터 V-1번 정점에 대해 함수 반환값으로 채운다.
	vector<vector<int>> paths(V);

	for (int i = 0; i < V; i++)
	{
		paths[i] = SingleSourceShortestPaths(i);
	}

	cout << "각 정점 사이의 최단 거리:" << endl;

	for (int i = 0; i < V; i++)
	{
		cout << i << ": ";

		for (int j = 0; j < V; j++)
		{
			(paths[i][j] == UNKNOWN) ? cout << "- "
				: cout << paths[i][j] << " ";
		}
		cout << endl;
	}
}

/*
 8 20
 0 1 387
 0 3 38
 0 5 471
 1 0 183
 1 4 796
 2 5 715
 3 0 902
 3 1 712
 3 2 154
 3 6 425
 4 3 834
 4 6 214
 5 0 537
 5 3 926
 5 4 125
 5 6 297
 6 1 863
 6 7 248
 7 0 73
 7 3 874
*/
