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

//������ �ð��� ���ٸ� ���� �ð��� �� ���� ���� ���� ���� �����Ѵ�.
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