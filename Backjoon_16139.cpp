#include <iostream>
#include <vector>
using namespace std;

//��� ���ĺ��� �󵵸� DP�� �����ϰ�, �������� ���ϴ� ���� �����̴�.

string A;
string B;
int DP[26][200002] = { 0 };
int N;

int main()
{
    //�� �� �� �Ⱥ��̸� 50���̴�.... ������ ������ ���� ������ ����.
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

    cin >> A;
    cin >> N;

   for (int i = 0; i <= 25; ++i)
    {
        for (int j = 1; j <= A.size(); ++j)
        {
            if (i + 'a' == (int)A[j-1])
                DP[i][j] = DP[i][j - 1]+1;
            else
                DP[i][j] = DP[i][j - 1];
        }
    }

    for (int i = 0; i < N; ++i)
    {
        int a, b;
        char Character;
        cin >> Character;
        cin >> a >> b;
        if(a == 0)
            //������ �Է¿��� �䱸�ϴ� ���ڿ��� index�� 0���� �����ε� DP���� 1���� �����̹Ƿ� �� ��° ������ +1�ؼ� ����ؾ� ��.
            cout << DP[Character - 'a'][b+1]<<'\n';
        else
            cout << DP[Character - 'a'][b+1] - DP[Character - 'a'][a]<<'\n';
    }
}