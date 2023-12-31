#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct cmp {
    bool operator()(int a, int b) {
        return a > b; // ��ȣ ���� swap�̱� ����
    }
};
int main() {
    ios::sync_with_stdio(false);
    vector<int> result;
    int n, x;
    cin >> n;

    priority_queue<int, vector<int>, cmp> q; // �ּҰ� root��
    for (int i = 0; i < n; i++) {
        cin >> x;
        if (x != 0) {
            q.push(x); // 0�ƴϸ� �Է°��� �־��ְ� 
        }
        else {
            if (q.empty()) { // ���������
                result.push_back(0); // 0 ����
            }
            else {
                result.push_back(q.top()); // root�� ����
                q.pop(); // root �ϳ� ����
            }
        }
    }
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << '\n';
    }
    return 0;
}