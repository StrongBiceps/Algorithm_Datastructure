#include <iostream>
#include <vector>
#include <stack>

using namespace std;

//DFS�� �����ϴ� FillStack()�Լ��� �� ���� ���ڸ� �޴´�. ������ node�� ���� ���� �ε����̰�,
//�ο��� ���� visited�� ������ �湮�� ������ ����� �����̴�. 2���� ������ ���� adj�� �׷����� ��Ÿ����
//���� ����Ʈ�̴�. ���������� ������ ���� stack�� �湮 ������ ���� ���� �ε����� ����ϰ� �ִ�.
//visited,adj,stack ���ڴ� ������ ���޵ȴ�. DFS�� �Ϲ����� ������� �����ϵ�, ���� ���� �ε����� ���ÿ� �߰��ϴ�
//�۾��� �߰��Ǿ�� �Ѵ�.
void FillStack(int node, vector<bool>& visited,
	vector<vector<int>>& adj, stack<int>& stack)
{
	//0->1->2->3->7->8->5->4->6 ������ true�� �����.
	visited[node] = true;

	for (auto next : adj[node])
	{
		if (!visited[next])
		{
			FillStack(next, visited, adj, stack);
		}
	}
	
	//8���� 3���� �����µ� 3�� visited true�̹Ƿ� 8���� ó�� for���� �����. ���� 8�� ���ÿ� ���� ����
	//����. 8�� �ڵ尡 �������Ƿ� 7�� ���� 7�� �� �̻��� �ڽ��� �����Ƿ� 7�� �� ������ ����.
	//�������� 3�� �ڽ��� �����Ƿ� for���� ��� ���ÿ� push�ȴ�. ���� ���ÿ� 8 7 3

	//�� �������� 2�� �ڽ� 3�� �������Ƿ� 2�� �ٸ� �ڽ��� 5�� ����. 5�� �ڽ��� 4�� ���� 4�� �ڽ���
	//2�� �̹� �湮�Ǿ����Ƿ� 4�� �ڵ嵵 ���� ���� 4�� ���ÿ� ����. ���� ���� 8 7 3 4
	//5�� �ٸ� �ڽ��� 6���� �̵��Ͽ� 6�� �ڽĵ� �̹� �������Ƿ� 6�� ���ÿ� ����. 8 7 3 4 6
	//���� 5�� ��� �ڽ��� �������Ƿ� 5�� ���ÿ� ����. 8 7 3 4 6 5 ���� 2�� ������ �״��� 1- >0 ������ ����
	//���� ���ÿ� 8 7 3 4 6 5 2 1 0 �� ����. ���ÿ� �� ������ �����غ��� 
	//8 7 3 (���� ���� ��� 1) 4 6 5 2(���� ���� ���2) 1 (���� ���� ���3) 0 (���� ���� ��� 4)������ ����.
	stack.push(node);
}

//�˰��� �Ĺݺο��� �� ��° DFS�Լ��� CollectConnectedComponents() �Լ��� ����Ѵ�. �� �Լ��� FillStack()�Լ��� ����� ���ڸ�
//�޴´� �ٸ� ���� Component�� ���� ���� ������ ����Ǿ� �ִ�. �� ���Ϳ� ������ ���� ���� ��ҿ� ���ϴ� ���� �ε����� ����ȴ�.
//CollectConnectedComponents()�Լ����� DFS ��ȸ �ڵ�� FillStack()�Լ��� ���� ����ϸ�, �ٸ� ���ÿ� ������ �߰��ϴ� �ڵ�� �����ִ�.
//��� �Լ� �պκп� ���� ���� node�� ���Ϳ� �߰��ϴ� �ڵ尡 �߰��ȴ�.
void CollectConnectedComponents(int node, vector<bool>& visited,
	vector<vector<int>>& adj, vector<int>& component)
{
	//��ġ�� ����� �ǹ̴� ��� �������� �� �� �ִ� 0,1�� ���� �Ųٷ� 0�� � ������ �� �� ����,
	//1�� 0�� �� �� �ְ� �Ǿ���. �� �� ������ ������ ������ ���� ��ҵ鵵 ������ ������ ���Ծ��� �湮�� �� ������
	//������ �� �ִ� ���� ��Ҵ� ������ �� ���� �Ǿ���, ������ �� ���� ���� ��Ҵ� ������ �� �ְ� �Ǿ���. 
	//���� �׷����� DFS�� �� ������ ���ÿ� �����ϴµ�, �� ������ ���� ���� ��ҳ��� ��ģ �����̰�,
	//��ġ �׷����� DFS�� �� ������ ������ �����Ǿ� ������ �� �ִ� ������ ���� ���� ��Һ��� ���ʷ� ���ܼ�
	//connectedComponents�迭�� ����ȴ�.
	visited[node] = true;
	cout << "Coll:"<<node << endl;
	component.push_back(node);

	for (auto next : adj[node])
	{
		if (!visited[next])
		{
			cout << "visit: " << next << endl;
			CollectConnectedComponents(next, visited, adj, component);
		}
	}
}

//���ο� �Լ� Transpose()�� �߰��Ѵ�. �� �Լ��� ���� ����Ʈ�� ǥ���� �׷����� ���ڷ� �ް�, ��ġ�� �׷����� ��ȯ�Ѵ�.
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

//�ڻ���� �˰����� ������ Kosaraju()�Լ��� �����Ѵ�. �� �Լ��� ���� ���� V�� �׷����� ǥ���ϴ� ���� ����Ʈ
//adj�� ���ڷ� �޴´�. �׸��� �Է� �׷������� ���� ���� ��� ������ ���� ������ ������ ���͸� ��ȯ�Ѵ�.
vector<vector<int>> Kosaraju(int V, vector<vector<int>> adj)
{
	//ù ��° �۾��� ���� �����̳� stack�� �湮 �迭 visited�� �����ϴ� ���̴�. visited �迭�� ��� ���Ҵ� false�� �ʱ�ȭ�Ѵ�.
	//�׸��� �׷��� ��� ������ ���� ���� �湮���� ���� �����̶�� DFS��ȸ�� �����Ѵ�.
	vector<bool> visited(V, false);
	stack<int> stack;

	for (int i = 0; i < V; i++)
	{
		if (!visited[i])
		{
			FillStack(i, visited, adj, stack);
		}
	}

	//�� ��° DFS�� �����ϱ⿡ �ռ� ���� ��ġ �׷��� transpose�� �����Ѵ�. 
	vector<vector<int>> transpose = Transpose(V, adj);

	//visited �迭�� �ٽ� false�� �ʱ�ȭ�Ѵ�.
	fill(visited.begin(), visited.end(), false);

	//connectedComponents��� �̸��� ������ ������ ���͸� �����Ѵ�. �� ���Ϳ� ��ġ �׷��������� ��ȸ ���,
	//�� ���� ���� ��Ҹ� ������ ���̴�. while�ݺ��� �ȿ��� �������κ��� �ϳ��� ������, �� ������ ���� �湮
	//���� �ʾҴٸ� DFS��ȸ�� �����Ѵ�. �̶� ������ ���� component�� �����ϰ�, �̸� CollecComponent()
	//�Լ��� ������ �����Ͽ� ���� ä���. DFS ��ȸ�� ������ component���͸� connectComponents�� �߰��Ѵ�.
	//�� �˰����� ������ �� ���°� �� ������ �ݺ��ϰ�, ���������� connectComponents�� ��ȯ�Ѵ�.
	vector<vector<int>> connectedComponents;

	while (!stack.empty())
	{
		int node = stack.top();
		cout << "stack:" << node << endl;
		stack.pop();

		if (!visited[node])
		{
			vector<int> component;

			CollectConnectedComponents(node, visited, transpose, component);
			connectedComponents.push_back(component);
		}
	}

	return connectedComponents;
}

//main �Լ����� ������ ���� ���� ��ҿ� ���ϴ� �������� ��ȣ�� ȭ�鿡 ����Ѵ�.
int main()
{
	int V = 9;

	vector<vector<int>> adj =
	{
		{ 1, 3 },
		{ 2, 4 },
		{ 3, 5 },
		{ 7 },
		{ 2 },
		{ 4, 6 },
		{ 7, 2 },
		{ 8 },
		{ 3 }
	};

	vector<vector<int>> connectedComponents = Kosaraju(V, adj);

	cout << "���� ���� ��� ����: " << connectedComponents.size() << endl;

	for (int i = 0; i < connectedComponents.size(); i++)
	{
		cout << "[" << i + 1 << "] ";

		for (auto node : connectedComponents[i])
			cout << node << " ";

		cout << endl;
	}
}