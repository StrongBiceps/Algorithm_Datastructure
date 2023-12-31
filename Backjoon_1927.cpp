#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct cmp {
    bool operator()(int a, int b) {
        return a > b; // 부호 주의 swap이기 때문
    }
};
int main() {
    ios::sync_with_stdio(false);
    vector<int> result;
    int n, x;
    cin >> n;

    priority_queue<int, vector<int>, cmp> q; // 최소값 root에
    for (int i = 0; i < n; i++) {
        cin >> x;
        if (x != 0) {
            q.push(x); // 0아니면 입력값을 넣어주고 
        }
        else {
            if (q.empty()) { // 비어있으면
                result.push_back(0); // 0 저장
            }
            else {
                result.push_back(q.top()); // root값 저장
                q.pop(); // root 하나 제거
            }
        }
    }
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << '\n';
    }
    return 0;
}