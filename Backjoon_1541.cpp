#include <iostream>
#include <string>
using namespace std;

//�Ʒ� �ڵ带 �м����ڸ�, '-'�� ���� ó�� ���� ������ �� �������� �ȴ�. ��, ���ĺ��� ������ -�������� ��ȣ�� ģ�ٰ� ���� �ȴ�.

//���� ��, 10+20-30+40+50-60+70 �̶�� �����ϸ�, 10+20�� �׳� ���ϴ� ���̰�, -30���� ��� ���� �ȴ�. �� -�� ���� �������ʹ�

//��� +�� -��ȣ�� ���� �� �ִ�. 10+20-(30+40+50)-(60+70) �׷��� �ᱹ���� �� �������� �ȴ�.
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
