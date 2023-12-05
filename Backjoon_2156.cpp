#include <iostream>
using namespace std;

int N;
int DP[10000] = { 0 };
int Value[10000] = { 0 };

int main()
{
    cin >> N;

    for (size_t i = 0; i < N; ++i)
    {
        cin >> Value[i];
    }
    
    //DP[2]���� �ִ� ���� ������Ų��. �Ʒ� ���ۿ� ���� �����̴�. (3��° �ܱ���)

    //��ȭ���� ���� ������ ��ܹ������� �� ���� �þ���. �� i-1������ ���, ���� ���� �������� �ʾƵ� �ǹǷ� 
    //�� �ٷ� �� �ܱ��� ������ ������ ���ϸ� �ȴ�.
    DP[0] = Value[0];
    DP[1] = Value[0] + Value[1];
    DP[2] = max(Value[0] + Value[1],max(Value[1]+Value[2], Value[0] + Value[2]));

    for (size_t i = 3; i < N; ++i)
    {
        DP[i] = max(DP[i-2]+Value[i],max(DP[i-3] + Value[i-1] + Value[i],DP[i-1]));
    }

    cout << DP[N - 1];
}