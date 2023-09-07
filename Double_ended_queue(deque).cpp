#include <iostream>
using namespace std;

#define SIZE 8

/*
 front == (rear+1)%SIZE �� �ڵ��� �ǹ̴� �迭�� ó���� �� ��迡�� ���� 1ĭ ����(���� �� ���)���� ����
 ���̴�. ���� ũ�Ⱑ 8�̰� front:0 rear:7 �� �� ��ȯ�� �������� �迭�� ���� �� ���� �ǹ��Ѵ�.
 
 �迭�� ��迡�� �Ӹ� �ƴ϶� ���� �迭�� ��ȯ������ �����ϱ� ������ ���� �� ��쿡�� �׻� front�� rear���� 1�� ũ��.
 ���� front�� ���� �� ��ĭ ���� ����Ű�� �����Ƿ� ��ȯ�� �迭���� ���� �� ��� �� ĭ�� ����ִ� ���°� �ȴ�. �� ĭ�� 
 ��� ���·� ����ؼ� ��ȯ�� �迭�� ������ �� �ִ�. �ϴ� front==rear�� ���� ����ִٴ� ���� �ǹ��Ѵ�. ������ �迭��
 ���� ä�������� �� ��Ȳ������ front == rear�̴�. �� ��Ȳ�� ���� �� ��Ȳ���� ����ִ� ������ ������ �� ����.

 ���� ��� front�� rear�� �ε����� 0�� ��Ȳ���� ���� á�ٰ� �����Ѵ�. �� ��Ȳ������ rear�� ��� ������ ���� ���̴�.
 �� �� front���� �����, rear : 0  front : 1�� ��Ȳ�� ���̴�. ���� rear�� ��� �ִ� ĭ�� ����Ű�� �ִ�. ���� front��
 rear�� ��ġ�� �����Ǿ���. ���� ��ġ�� �����Ǿ� �迭�� �հ� �ڷ� ���� �����ϴ� ������ �� �̻� �Ұ����ϰ� �ȴ�. ���� ��
 ���� ��ġ�� �����Ƿ� rear�� ������ �ϰ� �Ǹ� �ε��� 1�� ������ ���ٵ� �̹� ���Ұ� �����Ѵ�.  ���� rear���� ������ �ϰ�
 �Ǹ� �ε��� 0�� �����ϴ� ���ε� �ε��� 0�� �̹� front�� �����Ͽ� ��� �ִ� �����̴�. ���� �߸��� ������ �ϰ� �Ǵ� ���̴�.

 �̷��� ���� ������ ������ ĭ�� ����δ� ���̴�. ������ ĭ�� ����дٸ� ���� �� �ִ� ���¿� ��� �ִ� ���¸� ������ �� �ְ� �ǰ�
 ���� �� ���Ŀ��� front�� rear���� �����Ӱ� ������ �����ϰ� ���� ���Ŀ� �ٽ� ������ �����ϴ�.

 ���� ������ front�� rear�� %SIZE �� �̿��Ͽ� �ε����� �ٷ�� ������ ��ȯ���� �����ϱ� ���ؼ���. ���� ũ���� �迭�� ��ȯ������ ���������ν�
 ����� ������ ������ ���̴�. ������ �迭�� ��ȯ������ �������� �ʴ´ٸ� ���� �������ιۿ� �����ؾ� �Ѵ�. ���� ��ȯ�� ������ ����� ���� ����
 �� �������� Ȯ�����ش�.
*/

class Deque {
private:
    int front;  // ù��° ��� ���� index
    int rear;   // ������ ��� index
    int data[SIZE];

public:
    Deque() {
        front = 0;
        rear = 0;
    }
    ~Deque() {}

    void addFront(int n) {
        if (isFull()) {
            cout << "Deque Full Error" << endl;
            exit(1);
        }
        //front�� ���� ���� �� �ε����� ������Ų�� ���� �� ������ ����Ų��.
        data[front] = n;
        front = (front - 1 + SIZE) % SIZE;    // front�� 0 ���Ϸ� �������� ��� max index�� ��ȸ
    }

    void addRear(int n) {    // push
        if (isFull()) {
            cout << "Deque Full Error" << endl;
            exit(1);
        }
        //rear�� �ε��� ���� �� �����Ѵ�. ���� ���Ե� ������ ����Ų��.
        rear = (rear + 1) % SIZE;   // rear�� max�� �Ѿ�� ��� �ٽ� 0��° index�� ��ȸ
        data[rear] = n;
    }

    int deleteFront() {  // pop
        if (isEmpty()) {
            cout << "Deque Empty Error" << endl;
            exit(1);
        }
        //front�� �� ������ ����Ű�Ƿ� ������ �� �ܼ��� �ε����� ������Ų��.
        front = (front + 1) % SIZE;   // front�� max�� �Ѿ�� ��� �ٽ� 0��° index�� ��ȸ
        return data[front];
    }

    int deleteRear() {
        if (isEmpty()) {
            cout << "Deque Empty Error" << endl;
            exit(1);
        }
        //rear�� ���Ե� ��ġ�� ����Ű�Ƿ� ���� �ش� ���Ҹ� ���� �� �ε����� ���ҽ�Ų��.
        int tmp = data[rear];
        rear = (rear - 1 + SIZE) % SIZE;   // rear�� 0 ���Ϸ� �������� ��� max index�� ��ȸ
        return tmp;
    }

    int getFront() {
        if (isEmpty()) {
            cout << "Deque Empty Error" << endl;
            exit(1);
        }
        //front�� �� ������ ����Ű�Ƿ� ��ȯ�� �������� ���� �ε����� ��ȯ�ϱ� ���� 
        //�Ʒ� �ڵ带 ����Ѵ�.
        return data[(front + 1) % SIZE];
    }

    int getRear() {
        if (isEmpty()) {
            cout << "Deque Empty Error" << endl;
            exit(1);
        }
        //rear�� ���Ҹ� ����Ű�Ƿ� �ش� �ε��� ���Ҹ� ��ȯ�ϱ⸸ �ϸ� �ȴ�.
        return data[rear];
    }

    int size() {
        //��ȯ�� �����̱� ������ front�� rear�� ��Ұ� �� ���� ������.
        //���� front�� rear���� �۴ٸ� �ܼ��� rear-front�� �ϸ� �ǰ�
        //�� �ݴ��� rear�� SIZE�� ���ؼ� rear�� ���� ������ŭ front���� ũ�� �Ѵ�.
        //�� ��쿡�� front�� ���� size�� ������ �ȴ�.
        return front <= rear ? rear - front : (rear + SIZE) - front;
    }

    void display() {
        for (int i = front + 1; i <= front + size(); i++) {
            cout << "[" << data[i % SIZE] << "]";
        }
        cout << endl;
    }

    // circular array�� front�� rear ������ �������� �޼ҵ�
    void displayDetail() {
        cout << "DEQUE :";
        for (int i = front + 1; i <= front + size(); i++) {
            cout << "[" << data[i % SIZE] << "]";
        }
        cout << endl;
        cout << "index :";
        for (int i = front + 1; i <= front + size(); i++) {
            cout << " " << i % SIZE << " ";
        }
        cout << endl;
        cout << "front : " << front << ", rear : " << rear << endl;
        cout << endl;
    }

    bool isEmpty() {
        return front == rear;
    }
    bool isFull() {
        return front == (rear + 1) % SIZE;
    }
};

int main() {
    Deque deque;

    cout << "===== addRear x3 =====" << endl;
    deque.addRear(1);
    deque.addRear(2);
    deque.addRear(3);
    cout << " size : " << deque.size() << endl;
    deque.displayDetail();

    cout << "===== addFront x2 ======" << endl;
    deque.addFront(5);
    deque.addFront(6);
    cout << " size : " << deque.size() << endl;
    deque.displayDetail();

    cout << "===== deleteRear x1 ======" << endl;
    deque.deleteRear();
    cout << " size : " << deque.size() << endl;
    deque.displayDetail();

    cout << "===== deleteFront x3 ======" << endl;
    deque.deleteFront();
    deque.deleteFront();
    deque.deleteFront();
    cout << " size : " << deque.size() << endl;
    deque.displayDetail();
}