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

//���� �ٸ� Ǯ�� (���� �� ����) ������ �� �ڵ�� ����.
#include <iostream>
#include <string>
using namespace std;

string expression;
int Result = 0;
bool Min = false;
int Next = 0;

int main()
{
    cin >> expression;
    string Temp;

    for (int i = 0; i < expression.size(); ++i)
    {
        if (expression[i] == '+')
        {
            if (Min == false)
                Result += stoi(expression.substr(Next, i));
            else
                Result -= stoi(expression.substr(Next, i));
            Next = i + 1;
            Temp = "";
        }
        else if (expression[i] == '-')
        {
            if (Min == false)
                Result += stoi(expression.substr(Next, i));
            else
                Result -= stoi(expression.substr(Next, i));

            if (Min == false)
                Min = true;

            Next = i + 1;
            Temp = "";
        }
        else
        {
            Temp += expression[i];
        }
    }

    if (Min == false)
        Result += stoi(expression.substr(Next, expression.size()));
    else
        Result -= stoi(expression.substr(Next, expression.size()));


    cout << Result;
}