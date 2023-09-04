#include <algorithm>
#include <utility>
#include <iostream>
#include <vector>

#define DEBUG 1

#if DEBUG
#define PRINT(x) cerr << x
#else
#define PRINT(x)
#endif

using namespace std;

vector<vector<pair<int, int>>> found;


//�� �Լ��� �� ���� ���ڿ� A�� B, �� ���� ���� �ε��� i�� j, �׸��� ���� �� subsequence�� ���ڷ� �ް�
//�ϳ��� ������ ��ȯ�Ѵ�. �� �Լ� �ٱ��� 2���� ���� �� ���� found�� ���� ������ �����Ѵ�.
int LCS_BruteForce(string A, string B, int i, int j,
	vector<pair<int, int>> subsequence)
{
	//A�� B�� �ٱ��� �� ���ڿ��̰�, i�� j�� A�� B ���ڿ��� �ε����� ��Ÿ����. �׸��� subsequence�� ���� �κ� ��������
	// �����ϴ� �ε��� ���� �����ϸ�, ����� ���� found ���Ϳ� �߰��ȴ�. �̹� �տ��� �ǻ� �ڵ带 ��������Ƿ� �ǻ� �ڵ带
	// �ּ����� �־�ΰ�, �� �Ʒ��� ���� C++�ڵ带 �ۼ��ϸ� ���� �Լ��� �ϼ��� �� �ִ�.
	
	// ���� i�� A�� ���̺��� Ŀ���ų� �Ǵ� j�� B�� ���̺��� Ŀ����:
	if (i >= A.size() || j >= B.size())
	{
		found.push_back(subsequence);

		// ��͸� �����ϰ� �κ� �������� ���̸� ��ȯ�մϴ�.
		return subsequence.size();
	}

	// ���� A[i] = B[j] �̸�:
	if (A[i] == B[j])
	{
		// �κ� ������ ���̸� 1��ŭ �����մϴ�.
		subsequence.push_back({ i, j });

		// i�� j�� ���� 1�� �����մϴ�.
		return LCS_BruteForce(A, B, i + 1, j + 1, subsequence);
	}

	/* �׷��� ������:

	   �ɼ� 1) (i + 1)��°�� j��° ���ڿ� ���� �˻縦 �����մϴ�.
	   �ɼ� 2) i��°�� (j + 1)��° ���ڿ� ���� �˻縦 �����մϴ�.

	   �� ������ LCS�� �ɼ� 1 �� �ɼ� 2�� �ִ񰪰� �����ϴ�.
	 */

	//�� ���ڰ� ���� �ʾ��� ��쿡 ��Ͱ� �� ������ �����µ�, �� ���� �߿��� ū subsequence ����� ��ȯ�Ǿ� �Ѵ�.
	//LCS�� ���� �κ� ���� �������̱� �����̴�.
	return max(LCS_BruteForce(A, B, i + 1, j, subsequence),
		LCS_BruteForce(A, B, i, j + 1, subsequence));
}

void PrintSubsequences(string A, string B)
{
	// ���� �Լ��� �̿��� ����
	sort(found.begin(), found.end(), [](auto a, auto b)
		{
			// �κ� ������ ���̸� �������� ����
			if (a.size() != b.size())
			{
				return a.size() < b.size();
			}

			// �� �κ� ������ ���̰� ���ٸ� �ε����� ���� ������ ����
			return a < b;
		});

	// �ߺ� ����
	//��͸� �� �ɼ����� �����ϴ� ���� ���������� �ߺ��� ���ڿ� �������� ����� ���� �ִ�. ���� �ߺ��� �������ش�.
	//unique�� ���ؼ� �ߺ��� vector<pait<int,int>>�� found ������ ������. unique�� ������ ������ �ߺ��� ����� ���� iterator��
	//��ȯ�Ѵ�. ���� erase�� ��ȯ�� �ݺ��ں��� ������ ����������.
	found.erase(unique(found.begin(), found.end()), found.end());

	int previousSize = 0;

	for (auto subsequence : found)
	{
		if (subsequence.size() != previousSize)
		{
			previousSize = subsequence.size();
			PRINT("SIZE = " << previousSize << endl);
		}

		// ������ �̿��Ͽ� ������ �ڸ��� ǥ��
		string a_seq(A.size(), '_');
		string b_seq(B.size(), '_');

		for (auto pair : subsequence)
		{
			// ��ĭ�� �κ� ���ڿ� ���ڷ� ä���
			a_seq[pair.first] = A[pair.first];
			b_seq[pair.second] = B[pair.second];
		}

		PRINT("\t" << a_seq << " " << b_seq << endl);
	}
}

int main()
{
	string A, B;
	cin >> A >> B;

	int LCS = LCS_BruteForce(A, B, 0, 0, {});
	cout << A << "�� " << B << "�� ���� ���� �κ� ������ ����: " << LCS << endl;

#if DEBUG
	PrintSubsequences(A, B);
#endif
}

/*
ABCX ACYXB
*/