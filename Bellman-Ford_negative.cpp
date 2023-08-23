#include <vector>
#include <iostream>
#include <climits>

using namespace std;

//���� Ŭ������ ���� ������ src�� ���� ������ dst, �׸��� ����ġ�� �����ȴ�.
class Edge
{
public:
	int src;
	int dst;
	int weight;
};

//���Ѵ븦 ǥ���ϱ� ���� ��� UNKNOWN�� �����Ѵ�. UNKNOWN�� ���� ��� ������, �׷��� ���� ����ġ�� �պ��� �����
//ū ������ �����Ѵ�. ���⼭�� ���� �ִ밪�� INT_MAX�� �����߰�, INT_MAX�� climits> ���Ͽ� ���ǵǾ� �ִ�.

const int UNKNOWN = INT_MAX;

//���� ���� ���� �˰����� ������ BellmanFord() �Լ��� �����Ѵ�. �� �Լ��� �׷����� ǥ���ϴ� ���� ����Ʈ
//edges, ���� ���� V, ��� ���� ��ȣ Start�� ���ڷ� �ް�, �Ÿ� �� �迭�� ��ȯ�Ѵ�. �� �Լ� ���ο����� V�� ũ����
//�Ÿ� �� �迭 distance�� ����ϰ�, �� �迭�� �ʱ갪�� UNKNOWN���� �����Ѵ�. �ٸ� ��� ������ ���ؼ��� distance����
//0���� �����Ѵ�.

vector<int> BellmanFord(vector<Edge> edges, int V, int start)
{
	vector<int> distance(V, UNKNOWN);
	distance[start] = 0;

	//�˰����� ��κ��� ���� �ܰ迡�� �����Ѵ�. �� �ܰ迡���� (V-1)�� �ݺ��Ǵ� ������ �����ϰ�, �� ����������
	//��ü ������ �����ϸ鼭 �� ������ �Ÿ� ���� ������Ʈ�Ѵ�. ��ü������ �����ϸ� ������ ���� �߿��� ���� ������ 
	//�Ÿ� ���� UNKNOWN�� �ƴ� ��쿡 ���ؼ��� �Ÿ� ���� ������Ʈ�ϸ�, �̶�(���� ���� �Ÿ� ��+���� ����ġ) ��� �����
	//������ ������ �Ÿ� ������ ������ ������ ������ �Ÿ� ���� (���� ���� �Ÿ� ��+ ���� ����ġ)�� ��ü�Ѵ�.

	//(V-1)�� �ݺ�
	//�� ������ V-1�� �ݺ��ϸ鼭 �Ÿ��� ������Ʈ�ϴ� ���̴�.
	//�� �� ������ V-1�� 
	for (int i = 0; i < V - 1; ++i)
	{
		cout << "outter" << endl;
		//��ü ������ ���� �ݺ�
		for (auto& e : edges)
		{
			//������ ���� ������ UNKNOWN���̸� ��ŵ
			//�� �� ���̶� �Ÿ��� ������Ʈ �� ������ ������ �ٽ� �Ÿ� ������Ʈ�� �����Ѵ�.
			//�Ÿ��� ������ ������ ���ؼ��� �Ÿ��� �ٷ� ������Ʈ �ع����� �ǵ�ġ ���� ��Ȳ�� �߻��Ѵ�.
			//������� 1->2->3->4<-5 �� �׷����� �ִٰ� ����. 3->4������ ���������� ������Ʈ�� �̷������.
			//���� 5(���Ѵ�)->4�� �Ÿ��� ������Ʈ �Ǿ� ������ 1->5->4�� �����ϴٴ� ��Ȳ�� �ȴ�. ������
			//1���� �ٷ� 5�� �� ���� ����. �� �Ÿ��� �� ���̶� ������Ʈ �� ���¶�� ���� �ش� ��������
			//��ΰ� �̾��� �ְ�, �Ÿ��� ���� ���¶�� ���̴�.
			if (distance[e.src]==UNKNOWN)
			{
				cout << "continue" << endl;
				continue;
			}
			//������ ���� ������ �Ÿ� ���� ���ο� ��ο� ���� �Ÿ� ������ ũ��
			//�Ÿ� ���� ������Ʈ��
			if (distance[e.dst] > distance[e.src] + e.weight)
			{
				cout << "update" << endl;
				distance[e.dst] = distance[e.src] + e.weight;
			}
		}
	}

	//V-1���� �ݺ��� �Ϸ�Ǿ������� �Ÿ��� ������Ʈ�Ǵ� ��찡 �߻��Ѵٸ� ����Ŭ�� ���̴�.
	for (auto& e : edges)
	{
		if (distance[e.src] == UNKNOWN)
			continue;

		if (distance[e.dst] > distance[e.src] + e.weight)
		{
			cout << "���� ����ġ ����Ŭ �߰�" << endl;
			return {};
		}
	}

	return distance;
}

int main()
{
	int V = 6;              // ���� ����
	vector<Edge> edges;     // ���� �������� ����

	vector<vector<int>> edge_map{ // {���� ����, ��ǥ ����, ����ġ}
		{0, 1, 3},
		{1, 3, -8},
		{2, 1, 3},
		{2, 5, 5},
		{3, 2, 3},
		{2, 4, 2},
		{4, 5, -1},
		{5, 1, 8}
	};

	for (auto& e : edge_map)
	{
		edges.emplace_back(Edge{ e[0], e[1], e[2] });
	}

	int start = 0;
	vector<int> distance = BellmanFord(edges, V, start);

	if (!distance.empty())
	{
		cout << "[" << start << "�� �������κ��� �ּ� �Ÿ�]" << endl;

		for (int i = 0; i < distance.size(); i++)
		{
			if (distance[i] == UNKNOWN)
				cout << i << "�� ����: �湮���� ����!" << endl;
			else
				cout << i << "�� ����: " << distance[i] << endl;
		}
	}
}