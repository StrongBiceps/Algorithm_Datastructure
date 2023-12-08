#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
struct Job
{
    int Start;
    int End;
};

//끝나는 시간이 같다면 시작 시간이 더 빠른 것이 먼저 오게 정렬한다.
bool comp(Job& A, Job& B)
{
    if (A.End == B.End)
        return A.Start < B.Start;
    return A.End < B.End;
}

int main()
{
    cin >> N;
    vector<Job> List;
    for (int i = 0; i < N; ++i)
    {
        Job Temp;
        cin >> Temp.Start >> Temp.End;
        List.push_back(Temp);
    }

    sort(List.begin(), List.end(), comp);

    int cnt = 1;
    int first = List[0].End;

    for (auto it = List.begin() + 1; it != List.end(); ++it)
    {
        if ((*it).Start >= first)
        {
            ++cnt;
            first = (*it).End;
        }
    }

    cout << cnt;
}