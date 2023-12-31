#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
1 2 3 3 4 의 배열이 있을 때,

Lowerbound(3)은 인덱스 2를 반환하고 upperbound(3)은 인덱스 4를 반환한다.

lowerbound는 <=의 인덱스를 반환하고 Upperbound는 >의 인덱스를 반환한다.
 */

int n, m;
vector<int> arr;
vector<int> target;
int count[5000001] = { 0 };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;

    for (auto i = 0; i < n; i++) {
        int x;
        cin >> x;
        arr.push_back(x);
    }
    sort(arr.begin(), arr.end());

    cin >> m;
    for (auto i = 0; i < m; i++) {
        int x;
        cin >> x;

        cout << upper_bound(arr.begin(), arr.end(), x) - lower_bound(arr.begin(), arr.end(), x) << " ";
    }
}