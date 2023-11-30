#include <iostream>
#include <vector>
#include <stdio.h>
#include <time.h>
using namespace std;

bool Team1[10] = { 0 };
bool Team2[10] = { 0 };
vector<int> Team1_arr;
vector<int> Team2_arr;

int arr[20][20];
int N = 0;
int Delta = 1000001;
int Min = 0;

int Result1 = 0;
int Result2 = 0;

void Divide(int n)
{
    if (n == N/2)
    {
        for (size_t i = 0; i < N; ++i)
        {
            if (Team1[i] == false && Team2_arr.size() <= N/2)
            {
                for (size_t j = 0; j < Team2_arr.size(); ++j)
                {
                    Result2 += arr[Team2_arr[j]][i];
                    Result2 += arr[i][Team2_arr[j]];
                }

                Team2_arr.push_back(i);
            }
        }


        Min = abs(Result1 - Result2);

        if (Delta > Min)
            Delta = Min;

        Result2 = 0;
        Team2_arr.clear();

        return;
    }

    for (size_t i = 0; i < N; ++i)
    {
        if (Team1[i] == false)
        {
            if (n > 0)
            {
                if (Team1_arr[n - 1] > i)
                    continue;
            }


            Team1[i] = true;

            for (size_t j = 0; j < Team1_arr.size(); ++j)
            {
                Result1 += arr[Team1_arr[j]][i];
                Result1 += arr[i][Team1_arr[j]];
            }

            Team1_arr.push_back(i);

            Divide(n + 1);
            Team1[i] = false;
            Team1_arr.pop_back();

            for (size_t j = 0; j < Team1_arr.size(); ++j)
            {
                Result1 -= arr[Team1_arr[j]][i];
                Result1 -= arr[i][Team1_arr[j]];
            }
        }
    }
}

int main()
{
    cin >> N;

    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < N; ++j)
        {
            if (i == j)
            {
                arr[i][j] = 0;
                continue;
            }

            cin >> arr[i][j];
        }
  
    Divide(0);
    cout << Delta;

    return 0;

}
//내 기록: 54ms (2초 제한)

/*모범 답안*/

#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

bool team[20] = {};
int score[20][20] = {};
int N, mymin = 99999999;
void teamset(int idx, int cnt)
{
    vector<int> start; // 스타트 팀원의 인덱스값
    vector<int> link; // 링크팀 팀원의 인덱스값
    int start_score = 0;
    int link_score = 0;
    if (cnt == (N / 2))
    {
        for (int i = 0; i < N; i++)
        {
            if (team[i] == true) // 선택된 사람들은 start팀에
                start.push_back(i);
            else // 그 외의 사람들은 link팀으로
                link.push_back(i);
        }
        for (int i = 0; i < (N / 2); i++)
            for (int j = 0; j < (N / 2); j++)
            {
                start_score += score[start[i]][start[j]];
                link_score += score[link[i]][link[j]];
            } // 각 팀의 능력치의 합 계산
        if (abs(start_score - link_score) < mymin)
            mymin = abs(start_score - link_score);
        return;
    }
    for (int i = idx; i < N; i++)
    {
        if (team[i])
            continue;
        else
        {
            team[i] = true;
            teamset(i, cnt + 1);
            team[i] = false;
        }
    }
}
int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &score[i][j]);
    teamset(0, 0);
    printf("%d", mymin);
}