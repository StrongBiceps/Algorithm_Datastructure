#include <iostream>
#include <vector>
using namespace std;

int arr[20][20] = { 0 };
bool visit[20] = { false };
vector<int> Team1;
vector<int> Team2;

int N;

int Result = 1000001;
int Team1_add = 0;
int Team2_add = 0;

void Back(int cnt)
{
    if (cnt == N / 2)
    {
        for (size_t i = 0; i < N; ++i)
        {
            if (visit[i] == false && Team2.size() < N / 2)
            {
                for (size_t j = 0; j < Team2.size(); ++j)
                {
                    Team2_add += arr[i][Team2[j]];
                    Team2_add += arr[Team2[j]][i];
                }
                Team2.push_back(i);
            }
        }

        if (abs(Team1_add - Team2_add) < Result)
            Result = abs(Team1_add - Team2_add);

        Team2_add = 0;
        Team2.clear();

        return;
    }

    for (size_t i = 0; i < N; ++i)
    {
        if (visit[i] == true)
            continue;
        if (cnt > 0)
        {
            if (Team1[cnt - 1] > i)
            {
                continue;
            }
        }

        for (size_t j = 0; j < Team1.size(); ++j)
        {
            Team1_add += arr[i][Team1[j]];
            Team1_add += arr[Team1[j]][i];
        }
        visit[i] = true;
        Team1.push_back(i);
        Back(cnt + 1);
        Team1.pop_back();
        visit[i] = false;

        for (size_t j = 0; j < Team1.size(); ++j)
        {
            Team1_add -= arr[i][Team1[j]];
            Team1_add -= arr[Team1[j]][i];
        }
    }
}

int main()
{
    cin >> N;

    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {

            cin >> arr[i][j];
        }
    }

    Back(0);

    cout << Result;
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