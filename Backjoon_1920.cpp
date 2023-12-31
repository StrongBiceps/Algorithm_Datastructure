#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> arr_1(100001, 0);
vector<long long> arr_2(100001, 0);

int N;
int M;

void binary_search(int n)
{
    auto first = arr_1.begin();
    auto last = first+N;

    while (true)
    {
        //���� �˻� ������ �߰� ���Ҹ� mid element�� ����
        auto range_length = distance(first, last);
        auto mid_element_index = first + (range_length / 2);
        auto mid_element = *mid_element_index;
        auto dist_mid_index = distance(first, mid_element_index);

        if (mid_element == n)
        {
            cout << '1'<<'\n';
            return;
        }
        else if (mid_element > n)
            advance(last, -dist_mid_index);
        else
            advance(first, dist_mid_index);

        //���� �˻� ������ �ϳ��� ���Ҹ� ���� �ִٸ� false�� ��ȯ
        if (range_length == 1)
        {
            cout << '0' << '\n';
            return;
        }
    }
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; ++i)
    {
        cin >> arr_1[i];
    }

    cin >> M;
    for (int i = 0; i < M; ++i)
    {
        cin >> arr_2[i];
    }

    sort(arr_1.begin(), arr_1.begin()+N);

    for (int i = 0; i < M; ++i)
    {
        binary_search(arr_2[i]);
    }
}