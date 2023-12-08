#include <iostream>
#include <string>
using namespace std;

//아래 코드를 분석하자면, '-'를 가장 처음 만날 때부터 다 빼버리면 된다. 즉, 이후부터 만나는 -이전까지 괄호를 친다고 보면 된다.

//예를 들어서, 10+20-30+40+50-60+70 이라고 가정하면, 10+20은 그냥 더하는 것이고, -30부터 계속 빼면 된다. 즉 -를 만난 순간부터는

//모든 +를 -괄호로 묶을 수 있다. 10+20-(30+40+50)-(60+70) 그래서 결국에는 다 빼버리면 된다.
int main() {
    string input;
    cin >> input;

    int result = 0;
    string num;
    bool isMinus = false;

    for (int i = 0; i <= input.size(); i++) {

        if (input[i] == '-' || input[i] == '+' || i == input.size()) {
            if (isMinus) {
                result -= stoi(num);
                num = "";
            }
            else {
                result += stoi(num);
                num = "";
            }
        }
        else {
            num += input[i];
        }

        if (input[i] == '-') {
            isMinus = true;
        }
    }

    cout << result;
}
