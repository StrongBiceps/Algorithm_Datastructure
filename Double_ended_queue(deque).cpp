#include <iostream>
using namespace std;

#define SIZE 8

/*
 front == (rear+1)%SIZE 이 코드의 의미는 배열의 처음과 끝 경계에서 서로 1칸 차이(가득 찬 경우)인지 보는
 것이다. 만약 크기가 8이고 front:0 rear:7 일 때 순환식 구조에서 배열이 가득 찬 것을 의미한다.
 
 배열의 경계에서 뿐만 아니라 덱은 배열을 순환식으로 구성하기 때문에 가득 찬 경우에는 항상 front가 rear보다 1이 크다.
 또한 front는 삽입 후 한칸 앞을 가리키고 있으므로 순환식 배열에서 가득 찬 경우 한 칸은 비어있는 상태가 된다. 한 칸을 
 비운 상태로 사용해서 순환식 배열을 구현할 수 있다. 일단 front==rear는 덱이 비어있다는 것을 의미한다. 하지만 배열을
 가득 채워버리면 그 상황에서도 front == rear이다. 이 상황이 가득 찬 상황인지 비어있는 것인지 구분할 수 없다.

 예를 들어 front와 rear의 인덱스가 0인 상황에서 가득 찼다고 가정한다. 이 상황에서는 rear로 계속 삽입을 했을 것이다.
 이 때 front에서 지우면, rear : 0  front : 1인 상황일 것이다. 지금 rear는 비어 있는 칸을 가리키고 있다. 또한 front와
 rear의 위치가 역전되었다. 서로 위치가 역전되어 배열의 앞과 뒤로 삽입 삭제하는 과정이 더 이상 불가능하게 된다. 서로 역
 전된 위치에 있으므로 rear로 삽입을 하게 되면 인덱스 1에 삽입을 할텐데 이미 원소가 존재한다.  또한 rear에서 삭제를 하게
 되면 인덱스 0을 삭제하는 것인데 인덱스 0은 이미 front가 삭제하여 비어 있는 상태이다. 따라서 잘못된 동작을 하게 되는 것이다.

 이러한 이유 때문에 마지막 칸을 비워두는 것이다. 마지막 칸을 비워둔다면 가득 차 있는 상태와 비어 있는 상태를 구분할 수 있게 되고
 가득 찬 이후에도 front와 rear에서 자유롭게 삭제가 가능하고 삭제 이후에 다시 삽입이 가능하다.

 또한 덱에서 front와 rear를 %SIZE 를 이용하여 인덱스를 다루는 이유는 순환식을 구성하기 위해서다. 고정 크기의 배열을 순환식으로 구성함으로써
 양방향 접근을 구현한 것이다. 고정된 배열을 순환식으로 구성하지 않는다면 한쪽 방향으로밖에 삽입해야 한다. 따라서 순환식 구조가 양방향 삽입 삭제
 의 자율성을 확보해준다.
*/

class Deque {
private:
    int front;  // 첫번째 요소 앞의 index
    int rear;   // 마지막 요소 index
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
        //front는 먼저 삽입 후 인덱스를 증가시킨다 따라서 빈 공간을 가리킨다.
        data[front] = n;
        front = (front - 1 + SIZE) % SIZE;    // front가 0 이하로 떨어지는 경우 max index로 순회
    }

    void addRear(int n) {    // push
        if (isFull()) {
            cout << "Deque Full Error" << endl;
            exit(1);
        }
        //rear는 인덱스 증가 후 삽입한다. 따라서 삽입된 공간을 가리킨다.
        rear = (rear + 1) % SIZE;   // rear가 max를 넘어가는 경우 다시 0번째 index로 순회
        data[rear] = n;
    }

    int deleteFront() {  // pop
        if (isEmpty()) {
            cout << "Deque Empty Error" << endl;
            exit(1);
        }
        //front는 빈 공간을 가리키므로 삭제할 때 단순히 인덱스를 증가시킨다.
        front = (front + 1) % SIZE;   // front가 max를 넘어가는 경우 다시 0번째 index로 순회
        return data[front];
    }

    int deleteRear() {
        if (isEmpty()) {
            cout << "Deque Empty Error" << endl;
            exit(1);
        }
        //rear는 삽입된 위치를 가리키므로 먼저 해당 원소를 저장 후 인덱스를 감소시킨다.
        int tmp = data[rear];
        rear = (rear - 1 + SIZE) % SIZE;   // rear가 0 이하로 떨어지는 경우 max index로 순회
        return tmp;
    }

    int getFront() {
        if (isEmpty()) {
            cout << "Deque Empty Error" << endl;
            exit(1);
        }
        //front는 빈 공간을 가리키므로 순환식 구조에서 이전 인덱스를 반환하기 위해 
        //아래 코드를 사용한다.
        return data[(front + 1) % SIZE];
    }

    int getRear() {
        if (isEmpty()) {
            cout << "Deque Empty Error" << endl;
            exit(1);
        }
        //rear는 원소를 가리키므로 해당 인덱스 원소를 반환하기만 하면 된다.
        return data[rear];
    }

    int size() {
        //순환식 구조이기 때문에 front와 rear의 대소가 두 경우로 나뉜다.
        //만약 front가 rear보다 작다면 단순히 rear-front를 하면 되고
        //그 반대라면 rear에 SIZE를 더해서 rear가 원소 개수만큼 front보다 크게 한다.
        //그 경우에서 front를 빼면 size가 나오게 된다.
        return front <= rear ? rear - front : (rear + SIZE) - front;
    }

    void display() {
        for (int i = front + 1; i <= front + size(); i++) {
            cout << "[" << data[i % SIZE] << "]";
        }
        cout << endl;
    }

    // circular array의 front와 rear 정보를 보기위한 메소드
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