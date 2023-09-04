#include <vector>
#include <algorithm>
#include <utility>
#include <time.h>
#include <iomanip>
#include <iostream>
#include <string>

/*
* ABC�� AXB�� �̿��Ͽ� ��͸� �ۼ��Ѵ�.


i = 0
	for j to B.size
	���� - DP[0][j] = 0

i = 1
	for j to B.size

	j = 0
	���� - DP[1][0] = 0

	j = 1
	���� - DP[1][1] = DP[0][0]+1 - 1

	j = 2
	�ٸ� - DP[1][2] = DP[1][1] - 1 �ߺ� 

	j = 3
	�ٸ� - DP[1][3] = DP[1][2] - 1 �ߺ�

i = 2
	for j to B.size

	j = 0
	���� - DP[2][0] = 0

	j = 1
	�ٸ� - DP[2][1] = DP[1][1] - 1 �ߺ�

	j = 2
	�ٸ� - DP[2][2] = DP[2][1] - 1 �ߺ�

	j = 3
	���� - DP[2][3] = DP[1][2] + 1 - 2 �ߺ�

i = 3
	for j to B.size
	
	j = 0
	���� - DP[3][0] = 0
	
	j = 1 
	������ �� �ٸ� ...

	��� ����� ���� ���� LCS ���̸� DP�� �����ϰ� ���������� Reconstruct �Լ��� ȣ���Ͽ� ���� ���� �κ� �������� ����Ѵ�.
*/
#define DEBUG 0

#if DEBUG
#define PRINT(x) cerr << x
#else
#define PRINT(x)
#endif

using namespace std;

vector<vector<pair<int, int>>> found;

int LCS_BruteForce(string A, string B, int i, int j,
	vector<pair<int, int>> subsequence)
{
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

const int UNKNOWN = -1;

int LCS_Memoization(string A, string B, int i, int j,
	vector<vector<int>>& memo)
{
	// ���� ���� - �� ���ڿ��� ���ؼ��� 0�� ��ȯ
	if (i == 0 || j == 0)
	{
		return 0;
	}

	// �� ���ڿ��� �κ� ���ڿ��� ���� ����� ����Ǿ� ������ ��ȯ
	// Have we found a result for the prefixes of the two strings?
	if (memo[i - 1][j - 1] != UNKNOWN)
	{
		return memo[i - 1][j - 1];
	}

	// A�� B�� �� �κ� ���ڿ����� �� ������ ���ڰ� ������ Ȯ��
	if (A[i - 1] == B[j - 1])
	{
		// �� ��� A�� B�� �κ� ���ڿ����� ���� LCS ���̴� �� �κ� ���ڿ����� 
		// ������ �� ���ڸ� ������ ���ڿ��κ��� ���� LCS ���̿� 1�� ���� �Ͱ� ����

		memo[i - 1][j - 1] = 1 + LCS_Memoization(A, B, i - 1, j - 1, memo);

		// ���̺� ����� ����� ��ȯ
		return memo[i - 1][j - 1];
	}

	// A�� B�� �� �κ� ���ڿ����� �� ������ ���ڰ� ���� �ʴٸ�
	// A�� �κ� ���ڿ����� ������ ���ڸ� ������ �Ͱ� B�� �κ� ���ڿ����� ���� LCS ����,
	// B�� �κ� ���ڿ����� ������ ���ڸ� ������ �Ͱ� A�� �κ� ���ڿ����� ���� LCS ���� ��
	// �ִ��� �����Ͽ� ����

	memo[i - 1][j - 1] = max(LCS_Memoization(A, B, i - 1, j, memo),
		LCS_Memoization(A, B, i, j - 1, memo));

	return memo[i - 1][j - 1];
}

//���� ���� �κ� �������� ����ϰ� �ʹٸ� ��� �ؾ� �ұ�? ���� ���� ���� ����� ���� ���� �κ� ������ ��ü�� ��
//���� �� ������, �ʹ� ��ȿ�����̴�. �������� �ռ� ���� DP ���̺� ���� ��Ʈ��ŷ�� ���������ν� ���� ���� �κ�
//�������� ���� ���� �� �ִ�.

//������ ��Ʈ��ŷ �ǻ� �ڵ��̴�.

/*
* ���� i = 0 �Ǵ� j = 0:
*		�� ���ڿ��� ��ȯ�Ѵ�.
* 
* ���� A�� �κ� ���ڿ��� B�� �κ� ���ڿ� �� ������ ���ڰ� ���ٸ�:
*		�� �κ� ���ڿ����� �� ���ھ� �� �κ� ���ڿ����� LCS�� ���ϰ�, ���� ���ڸ� �ڿ� �߰��Ѵ�.
* �׷��� ������:
*		���� DP(i-1,j) ���� DP(i,j-1)���� ũ�ٸ�:
*				A�� �κ� ���ڿ����� �� ���ڸ� ������ �κ� ���ڿ��� B�� �κ� ���ڿ��� LCS�� ���Ѵ�.
*		�׷��� ������:
*				B�� �κ� ���ڿ����� �� ���ڸ� ������ �κ� ���ڿ��� A�� �κ� ���ڿ��� LCS�� ���Ѵ�.
*/
string ReconstructLCS(vector<vector<int>> DP, string A, string B, int i, int j)
{
	/*
	* ���� ABC�� AXB�� �Է����� ����Ѵٸ�,
	* ������ ���ڰ� �ٸ��� DP[3][2]���� DP[2][3]�� �� ũ�Ƿ� ReconstructLCS(2,3) ȣ��
	* �� ���ڰ� �����Ƿ� ReconstructLCS(1,2) ȣ��
	* 
	* DP[0][2]�� ���� �����̹Ƿ� Reconstruct(1,1) ȣ��
	* �� ���ڴ� �����Ƿ� Reconstruct(0,0)ȣ�� -> ��� ����
	*/
	if (i == 0 || j == 0)
	{
		return "";
	}

	if (A[i - 1] == B[j - 1])
	{
		return ReconstructLCS(DP, A, B, i - 1, j - 1) + A[i - 1];
	}
	else if (DP[i - 1][j] > DP[i][j - 1])
	{
		return ReconstructLCS(DP, A, B, i - 1, j);
	}
	else
	{
		return ReconstructLCS(DP, A, B, i, j - 1);
	}
}

//LCS�Լ������� ���� DP���̺��� �����Ѵ�. �� ���̺��� 2���� ���� ���ͷ� ǥ���� �� �ִ�. �̶� ù ��° ���� ũ��� ���ڿ�
//A�� ���̺��� 1ũ�� �����ϰ�, �� ��° ���� ũ��� ���ڿ� B���� 1ũ�� �����Ѵ�.
string LCS_Tabulation(string A, string B)
{
	vector<vector<int>> DP(A.size() + 1, vector<int>(B.size() + 1));

	for (int i = 0; i <= A.size(); i++)
	{
		for (int j = 0; j <= B.size(); j++)
		{
			//�κ������� �� �����ʹ� �޸� ���� ������ for�ݺ��� ���� ó������ �ʰ� �Ź�
			//�ݺ��� �ȿ��� ó���Ѵ�. A�Ǵ� B���ڿ��� ��� �ִ� ��찡 ���� �����̰�, �̴� i=0
			//�Ǵ� j=0�� ����̱� �����̴�. ���� ������ ó���ϴ� �ҽ� �ڵ�� ������ ����.
			if (i == 0 || j == 0)
			{
				DP[i][j] = 0;
			}
			//�� ���ڰ� ���� ��쿡�� LCS ���̴� �� ������ ���ڸ� ������ �� �κ� ���ڿ��� LCS ���̿� 1�� ����
			//����̴�.
			else if (A[i - 1] == B[j - 1])
			{
				DP[i][j] = DP[i - 1][j - 1] + 1;
			}
			//���������� �� �κ� ���ڿ��� ������ ���ڰ� ���� ���� ��츦 ó���ؾ� �Ѵ�. �� ��� LCS���̴�
			//A�� �κ� ���ڿ����� ������ ���ڸ� ������ �Ͱ� B�� �κ� ���ڿ����� ���� LCS����, �׸��� B�� �κ�
			//���ڿ����� ������ ���ڸ� ������ �Ͱ� A�� �κ� ���ڿ����� ���� LCS���� �� ���� �ִ��̴�. Ÿ�淹�̼�
			//����� ������ ��� Ư�� ������ LCS���̴� �� �� ���� LCS���̿� �� �� ������ LCS ������ �ִ񰪰� ����.
			else
			{
				DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
			}
		}
	}

	string lcs = ReconstructLCS(DP, A, B, A.size(), B.size());

	return lcs;
}

vector<string> types =
{
	"BRUTE FORCE",
	"MEMOIZATION",
	"TABULATION"
};

void GetTime(clock_t& timer, string type)
{
	// ���� �ð����� timer�� ���� ��� �ð��� ���
	timer = clock() - timer;

	// ȭ�鿡 ��� �ð� ���
	cout << type << " ��� ��� �ð�: ";
	cout << fixed << setprecision(5) << (float)timer / CLOCKS_PER_SEC << endl;

	timer = clock(); // timer�� ���� �ð����� �ʱ�ȭ
}

int main()
{
	string A, B;
	cin >> A >> B;

	int tests = 3;


	for (int i = 0; i < tests; i++)
	{
		int LCS;

		clock_t timer = clock();

		switch (i)
		{
		case 0:
		{
			LCS = LCS_BruteForce(A, B, 0, 0, {});

#if DEBUG
			PrintSubsequences(A, B);
#endif
			break;
		}
		case 1:
		{
			vector<vector<int>> memo(A.size(), vector<int>(B.size(), UNKNOWN));
			LCS = LCS_Memoization(A, B, A.size(), B.size(), memo);

			break;
		}
		case 2:
		{
			string lcs = LCS_Tabulation(A, B);

			LCS = lcs.size();

			cout << A << "�� " << B << "�� ���� ���� �κ� ������: " << lcs << endl;
			break;
		}
		}

		cout << A << "�� " << B << "�� ���� ���� �κ� ������ ����: " << LCS << endl;

		GetTime(timer, types[i]);
		cout << endl;
	}
}

/*
A1B2C3D4E ABCDE
5
ABCDE

ABZCYDABAZADAEA YABAZADBBEAAECYACAZ
10
YABAZADAEA

QWJEHFBEMVJEIIFJEEVFBEHFJXAJXBE BVBQHEJEJCHEEHXBNEBCHHEHHFEHSBE
14
QHEJEJEEBEHFBE

AAA12AAA3AA4AA56AA7AAA8 AA1AA2AAA3A4A5A6AA7A89AAA
19
AA12AAA3A4A56AA7AAA

 */