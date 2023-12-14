#include <iostream>
#include <string>
using namespace std;

bool Black = false;
bool White = true;

string str;
bool arr[65][65] = { 0 };
int N;

void Recur(int R,int C,int Size)
{
	bool Black_Temp = false;
	bool White_Temp = false;

	for (int i = R; i < R + Size; ++i)
	{
		for (int j = C; j < C + Size; ++j)
		{
			if (arr[i][j] == Black)
			{
				Black_Temp = true;
				if (White_Temp == true)
				{
					cout << "(";
					Recur(R, C, Size / 2);
					Recur(R, C + Size / 2, Size / 2);
					Recur(R + Size / 2, C, Size / 2);
					Recur(R + Size / 2, C + Size / 2, Size / 2);
					cout << ")";
					return;
				}
			}

			if (arr[i][j] == White)
			{
				White_Temp = true;
				if (Black_Temp == true)
				{
					cout << "(";
					Recur(R, C, Size / 2);
					Recur(R, C + Size / 2, Size / 2);
					Recur(R + Size / 2, C, Size / 2);
					Recur(R + Size / 2, C + Size / 2, Size / 2);
					cout << ")";

					return;
				}
			}
		}
	}

	if (Black_Temp == true)
	{
		cout << "0";
	}

	if (White_Temp == true)
	{
		cout << "1";
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; ++i)
	{
		cin >> str;
		for (int j = 0; j < N; ++j)
		{
			if (str[j] == '0')
				arr[i][j] = 0;
			else
				arr[i][j] = 1;
		}
	}

	Recur(0, 0, N);
}