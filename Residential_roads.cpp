#include <vector>
#include <iostream>
//필요한 헤더를 포함하고, 몇몇 상수와 전역 변수를 선언한다. 편의를 위해 몇몇 변수를 전역으로 선언하지만, 프로그래밍 관점에서
//전역 변수를 많이 사용하는 것은 좋지 않다는 점을 기억해야 한다.



using namespace std;

const int UNKNOWN = 1e9;
const char EMPTY_SPACE = '.';
const string roads = "-|/\\";

class Point
{
public:
	int x;
	int y;

	Point() : x(0), y(0) {}
	Point(int x, int y) : x(x), y(y) {}

	//GetCost()함수의 마지막 줄에서 사용할 연산자 오버로딩
	bool operator !=(const Point& other) const
	{
		return x != other.x || y != other.y;
	}
};

//지도 크기
int H, W;
//집 개수
int N;

//지도 행렬
vector<string> grid;
//지반 가중치
vector<vector<int>> terrain;
//두 집 사이에 도로를 건설하는 비용
vector<vector<int>> cost;
//집 좌표를 저장하는 행렬 N개 만큼 할당된다.
vector<Point> houses;

//각 도로의 방향에 따라 올바른 문자를 선택해야 한다. 이를 위해 해당 함수를 정의한다.
//이 함수는 도로 방향에 따라 처음에 정의했던 문자열에서 선택할 문자의 인덱스를 반환한다.
int GetDirection(int x_dir, int y_dir)
{
	if (y_dir == 0) return 0;
	if (x_dir == 0) return 1;
	if (x_dir == -1)
	{
		return (y_dir == 1) ? 2 : 3;
	}
	return (y_dir == 1) ? 3 : 2;
}

//출력을 위한 그리기 함수이다. 이 함수는 start인자와 end인자를 정수형으로 받는다.
void DrawPath(int start, int end)
{
	Point a = houses[start];
	Point b = houses[end];

	int x_dir = 0;
	int y_dir = 0;

	if (a.x != b.x)
	{
		x_dir = (a.x < b.x) ? 1 : -1;
	}

	if (a.y != b.y)
	{
		y_dir = (a.y < b.y) ? 1 : -1;
	}

	int direction = GetDirection(x_dir, y_dir);
	char mark = roads[direction];

	//이제부터 a지점에서 b지점까지 이동하면서 지도상의 각 셀 값이 EMPTY_SPACE라면 적절한 도로 문자로
	//설정한다. 만약 이미 다른 도로가 건설되어 있는 경우라면 '+' 문자로 교체한다.
	do {
		a.x += x_dir;
		a.y += y_dir;

		if (grid[a.y][a.x] == EMPTY_SPACE)
		{
			grid[a.y][a.x] = mark;
		}
		else if (!isalpha(grid[a.y][a.x]))
		{
			// 만약 두 도로가 교차하면 '+' 문자로 대체
			grid[a.y][a.x] = (mark != grid[a.y][a.x]) ? '+' : mark;
		}
	} while (a != b);
}

/*
* 
LCS 또는 0-1배낭 문제에서 사용되었던 재구성 방식과 next행렬에 저장된 값을 이용하여 각 경로상의 좌표를 재구성할 수 있다.
이를 위해 새로운 함수 GetPath()를 정의한다. 이 함수는 두 개의 정수 start와 end,그리고 next행렬 참조를 인자로 받고, 
경로상의 정점 인덱스를 저장한 정수형 벡터를 반환한다.
*/
vector<int> GetPath(int start, int end, vector<vector<int>>& next)
{
	vector<int> path = { start };

	do {
		start = next[start][end];

		path.push_back(start);
	} while (next[start][end] != end);

	return path;
}

//이 함수는 플로이드-워셜 알고리즘 구현과 경로 재구성을 담당한다. 경로 재구성을 위해 N*N크기의 정수 행렬
//next를 생성하고, 여기에 두 정점 a와 b사이의 최단 경로상에 있는 다음 좌표 인덱스를 저장할 것이다. 기본적으로
//이 행렬의 원소 값은 이동 가능한 정점 인덱스로 설정한다.
void GetShortestPaths()
{
	//거리
	vector<vector<int>> dist(N, vector<int>(N, UNKNOWN));

	//이동 가능한 경로 상의 정점 인덱스

	//next 배열은 플로이드 - 워셜 알고리즘에서 경로를 추적하기 위해 사용되는 2차원 배열이다.
	//next[start][end]의 값은, 시작점 start에서 종점 end까지 가는 최단 경로에서, 시작점 바로 다음에 오는 정점을 저장한다.
	//따라서 만약 start부터 end까지 가는 최단 경로가 start -> ...->mid -> ...->end라면,
	//이때의 중간 정점인 mid가 바로 다음에 오는 정점으로 갱신된다.즉, 이 경우엔 next[start][end] = next[start][mid];
	//플로이드 - 워셜 알고리즘은 모든 쌍 최단 경로 문제를 해결하는 알고리즘이므로, 최종적으로 완성된 
	//'next' 배열을 사용하면 어떤 두 점 사이의 최단 경로도 찾아낼 수 있다.
	vector<vector<int>> next(N, vector<int>(N, UNKNOWN));

	//dist는 곧 집들을 잇는 에지의 가중치(cost)이다.
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			//두 집 사이에 도로가 건설될 수 있는 경우에만 cost값이 유효하므로
			//dist또한 해당 경우에서만 UNKNOWN이 아니게 된다.
			dist[i][j] = cost[i][j];

			//만약 두 집 사이에 도로가 건설될 수 있다면 next값을 경로 상에서 목적지의 집 인덱스로 설정한다.
			if (dist[i][j] != UNKNOWN)
			{
				//아래 플로이드 워셜 알고리즘에서 두 정점 사이의 거리가 업데이트되지 않았다면
				//중간 지점을 거치지 않고 바로 가는 것이 가장 최단 거리이므로 next는 도착 지점이 된다.
				next[i][j] = j;
			}
		}

		//같은 집에 대한 거리는 0이고, next는 해당 집의 인덱스로 한다.
		dist[i][i] = 0;
		next[i][i] = i;
	}

	//각 집을 정점으로 하는 그래프에서 각 정점 사이의 최단 거리를 구한다.
	//그런 다음 플로이드-워셜 알고리즘을 구현한다. 이때 가장 안쪽 for문에서 start와 end 사이의 최단 거리가
	//갱신될 때마다 next[start][end]값도 next[start][mid]값으로 갱신한다.
	
	/*
	* 예를 들어 다음 그래프가 있다고 가정한다.
	* 		{0,1,3}
			{1,2,2}
			{2,3,1}
			{2,4,4}
			{1,4,1}

			0->1->2->3
				   ->4
				---->
	 일단 각 거리는 에지의 가중치로 설정되어 있는 상태이다. distance[i][j] == cost[i][j]
	 0에서 3으로 가는 최단 거리는 0->1->2->3이다. 
	
	처음에는 정점을 건너뛰는 즉 바로 이어져 있는 에지를 제외하고는 다른 정점으로 가는 거리는 모두 UNKNOWN이다.
	따라서 mid = 0일 때에는 거리 업데이트가 없다. 또 mid = 1일 때에는 0->1->2가 업데이트된다. 따라서 next[0][2]=next[0][1](1)이된다.
	또 mid = 2일 때에는 next[1][3] = next[1][2](2)와 next[0][3] =  next[0][2](1)가 저장될 것이다.

	do {
		start = next[start][end];

		path.push_back(start);
	} while (next[start][end] != end);

	따라서 이 코드를 실행하면

	start = next[0][3] : 1

	start = next[1][3] : 2

	start = next [2][3] : 3

	1->2->3의 경로가 추출된다.
	플로이드 워셜 알고리즘에서 같은 그래프로 확인하면 디버깅 출력문으로 확인할 수 있을 것이다.

	추가 설명을 하자면 0을 기준으로 3으로 가는 최단 중간 경로는 1이고, 1을 기준으로 3으로 가는 최단 중간 경로는 2이고,
	2는 3으로 바로 가니까 1,2,3의 경로가 추출되는 것이다. 다시 0을 기준으로 0->3의 최단 중간 경로는 곧 0->2의 최단 중간 경로이다.

	“정점 A와 정점 B사이의 최단 거리가 AB이고 정점 B와 정점 C사이의 최단 거리가 BC이면, 정점 A와 정점 C사이의 최단 거리는 AB+BC이다.”
	이 성질을 이용한 것이다. 따라서 0->3의 경로는 0->2 + 2->3이고 0->2의 경로는 0->1 + 1->2이므로 next와 do-while에서는 경로 중에서 가장 처음의
	중간 경로를 순서대로 추출할 수 있게 하는 것이다.

	만약 복잡한 그래프에서 A->E 까지 가는 최단 거리를 구한다고 하면 모든 중간 지점에 대해서 A->E를 비교하고 next가 계속 업데이트되는데
	최단인 중간 지점이 최후의 next값이 된다.
	*/
	for (int mid = 0; mid < N; mid++)
	{
		for (int start = 0; start < N; start++)
		{
			for (int end = 0; end < N; end++)
			{
				if (dist[start][end] > dist[start][mid] + dist[mid][end])
				{
					dist[start][end] = dist[start][mid] + dist[mid][end];
					//next[start][end] = mid(next[start][mid] = mid);
					next[start][end] = next[start][mid];
				}
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		//모든 집이 입구까지 최단 경로로 가야 한다. 입구 = N-1 번째 집
		//next에는 모든 정점이 입구까지 최단 거리로 가는 경로가 저장되어 있다.
		vector<int> path = GetPath(i, N - 1, next);

		int curr = i;

		//이동 경로상의 두 지점을 잇는 선을 그리는 반복문 코드를 추가한다.
		for (auto neighbor : path)
		{
			DrawPath(curr, neighbor);
			curr = neighbor;
		}
	}
}

//두 집의 좌표 a와 b를 인자로 받고, 부울 값을 반환하는 DirectLine()함수를 작성한다.
bool DirectLine(Point a, Point b)
{
	//수평,수직,대각 위치중 어느 하나에 있다면 true를 반환하고
	//무엇도 아니라면 false를 반환한다. 해당 두 집 사이에는 도로를 건설할 수 없다는 것이다.
	if (a.x == b.x) return true;
	if (a.y == b.y) return true;
	if (abs(a.x - b.x) == abs(a.y - b.y)) return true;

	return false;
}

//도로는 강,산,숲 등을 가로질러 건설할 수 없다.
// 두 집 사이에 도로를 건설하는 데 필요한 비용은 두 집을 잇는 경로상의 지반 강도 합과 같다.

//위 두 조건은 지도상의 좌표 a에서 좌표 b로 단순히 이동하면서 처리할 수 있다.
//즉, 이동 경로를 따라 지반 강도 행렬 terrain에 들어 있는 값의 합을 누적하여 비용을 계산한다.
//이와 동시에 grid[a.y][a.x] 행렬에 들어 있는 문자가 EMPTY_SPACE 즉, '.'문자인지를 검사하여
//'.'문자가 아니면 이동을 즉시 종료한다. 최종적으로 좌표 a가 좌표 b와 같아지면 지반 강도의 합
//cost를 반환한다. 만약 a와 b가 같지 않으면 경로 중간에 장애물이 있는 것으로 간주할 수 있고
//이 경우에는 UNKNOWN을 반환한다. 이러한 작업을 GetCost()함수로 구현한다. 이 함수는 두 주택의 인덱스를
//나타내는 정수 start와 end를 인자로 받고, 하나의 정수 값을 반환한다.
//'.'문자가 있어야 도로를 건설할 수 있으므로 중간에 '.'를 만나지 못하면 도로를 직선으로 건설할 수 없다.
//이 예제는 도로를 무조건 직선으로 연결하는 것이므로 두 집 사이 직선(대각 포함) 경로에 '.'가 하나라도 없으면
//도로를 건설할 수 없으므로 UNKNOWN을 반환한다.
int GetCost(int start, int end)
{
	Point a = houses[start];
	Point b = houses[end];

	int x_dir = 0;
	int y_dir = 0;

	//서로의 x좌표가 다를 때 둘 중 어떤 x좌표가 큰 지에 대해서 도로의 수평 방향을 결정한다.
	if (a.x != b.x)
	{
		x_dir = (a.x < b.x) ? 1 : -1;
	}

	//서로의 y좌표가 다를 때 둘 중 어떤 y좌표가 큰 지에 대해서 도로의 수직 방향을 결정한다.
	if (a.y != b.y)
	{
		y_dir = (a.y < b.y) ? 1 : -1;
	}

	int cost = 0;

	//정해진 도로 방향으로 값을 업데이트한다. 계속 가다보면 end를 만나게 될 것이다. 하지만 중간에
	//도로를 지을 수 없는 공간이 나타나거나 장애물이 존재하면 반복을 종료한다. 따라서 a의 좌표와
	//b의 좌표가 같을 수가 없다.
	do {
		a.x += x_dir;
		a.y += y_dir;

		cost += terrain[a.y][a.x];
	} while (grid[a.y][a.x] == EMPTY_SPACE);

	return (a != b) ? UNKNOWN : cost;
}

void BuildGraph()
{
	//모든 집이 서로 알맞는 위치에 있는지, 맞다면 비용을 계산한다.
	//이 for문은 단방향에 대해서만 저장하도록 안쪽 for문에서 j값을 i로 제한했다.
	//또한 해당 안쪽 for문의 if에서 반대 방향에 대한 cost값도 업데이트한다.
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (i == j) continue;

			// 두 집이 수평, 수직, 대각 위치에 있는지 확인
			if (DirectLine(houses[i], houses[j]))
			{
				// 두 집 사이의 도로 건설에 필요한 비용 계산
				cost[i][j] = cost[j][i] = GetCost(i, j);
			}
		}
	}
}

//입력으로 처리할 것들이 많으므로 별도의 함수를 정의해서 사용한다.
void Input()
{
	cin >> H >> W;
	cin >> N;

	grid.resize(H);
	houses.resize(N);
	terrain.resize(H, vector<int>(W, UNKNOWN));
	cost.resize(N, vector<int>(N, UNKNOWN));

	// 지도 정보
	for (int i = 0; i < H; i++)
	{
		cin >> grid[i];
	}

	// 지반 강도 정보
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			cin >> terrain[i][j];
		}
	}

	// 주택 좌표
	for (int i = 0; i < N; i++)
	{
		cin >> houses[i].x >> houses[i].y;

		// 주택 레이블 설정
		grid[houses[i].y][houses[i].x] = char(i + 'A');
	}
}

int main()
{
	Input();
	BuildGraph();
	GetShortestPaths();

	for (auto it : grid)
	{
		cout << it << "\n";
	}

	return 0;
}

/*
 5 5
 5
 .....
 .....
 .....
 .....
 .....
 0 42 68 35 0
 1 70 25 79 59
 63 65 0 6 46
 82 28 62 92 96
 0 43 28 37 9
 0 0
 4 0
 4 4
 2 2
 0 4
*/

/*
5 5
5
..#..
.###.
.....
..#..
..##.
0 42 0 35 0
1 0 0 0 59
63 65 0 6 46
82 28 0 92 96
0 43 0 0 0
0 0
4 0
4 4
2 2
0 4
*/