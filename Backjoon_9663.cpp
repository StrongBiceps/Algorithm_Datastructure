#include <iostream>
#define MAX 15
using namespace std;

int col[MAX];
int N, total = 0;

//���ݱ��� ��ġ�� ������ �˻縦 �����Ѵ� level ������ ���� ��ġ������ �ʾ����Ƿ� �˻��� ������ ����.
bool check(int level)
{
    for (int i = 0; i < level; i++)
        if (col[i] == col[level] || abs(col[level] - col[i]) == level - i)// �밢���̰ų� ���� ����
            return false;
    //col[i]�� �ǹ��ϴ� ���� X��ǥ, i�� �ǹ��ϴ°��� Y��ǥ�̹Ƿ� ���̰� �����ϴٸ� �밢���� �ִٰ� �� �� �ִ�.
    return true;
}

void nqueen(int x)
{
    if (x == N)
        total++;
    else
    {
        for (int i = 0; i < N; i++)
        {
            col[x] = i; // �ش� ��ġ�� ���� ��ġ
            if (check(x)) // ��ȿ�ϴٸ� �������� �� ��ġ, ��ȿ�����ʴٸ� �ٸ� ��ġ�� �� ��ġ ����
                nqueen(x + 1);
        }
    }
}
int main() {
    cin >> N;
    nqueen(0);
    cout << total;
}

/*��Ʈ��ŷ Ư���� ��͸� �� �����غ��� ������ �� �ִ�. �� ���� � �࿡ ���� ��ġ�� �� ������ ���� ��͸� ��� ����.
���� ���ǿ� �ɷ��� �������Դٸ� �ٷ� ���� ��Ϳ��� ���� ��ġ�� Ž���� ���̴�. �̷� ������ ����� ������ �о��� ������.*/