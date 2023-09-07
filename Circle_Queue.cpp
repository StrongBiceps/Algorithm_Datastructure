#include <iostream>
using namespace std;

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif

// Doubly Linked List
class Node {
public:

    int data;
    Node* prev;
    Node* next;

    Node() {
        prev = nullptr;
        next = nullptr;
        data = 0;
    }
    Node(int n, Node* prevNode = nullptr, Node* nextNode = nullptr) {
        data = n;
        prev = prevNode;
        next = nextNode;
    }
    ~Node() {}

    void setPrev(Node* prevNode) {
        prev = prevNode;
    }
    void setNext(Node* nextNode) {
        next = nextNode;
    }
};

// Deque Class
class Deque {
private:
    Node* front;
    Node* rear;
    int dataSize;

public:
    Deque() {
        front = nullptr;
        rear = nullptr;
        dataSize = 0;
    }
    ~Deque() {
        while (!isEmpty()) {
            deleteFront(); //deleteRear();
        }
    }

    void addFront(int n) {
        Node* node = new Node(n, nullptr, front);
        if (rear == nullptr) {
            rear = node;
        }
        else {
            front->setPrev(node);
        }
        front = node;
        ++dataSize;
    }

    void addRear(int n) {
        Node* node = new Node(n, rear, nullptr);
        if (front == nullptr) {
            front = node;
        }
        else {
            rear->setNext(node);
        }
        rear = node;
        ++dataSize;
    }

    //마지막에는 front와 rear가 같은 node를 가리키고 있을 것이다.
    int deleteFront() {
        if (isEmpty()) {
            cout << "Deque Empty Error" << endl;
            exit(EXIT_FAILURE);
        }
        else {
            if (front == rear)
            {
                int data = front->data;
                auto node = front;
                delete front;
                front = nullptr;
                --dataSize;
                return data;
            }
            else
            {
                int data = front->data;
                Node* node = front;
                front = front->next;
                front->setPrev(nullptr);
                delete node;
                --dataSize;
                return data;
            }
        }
    }

    ////마지막에는 front와 rear가 같은 node를 가리키고 있을 것이다.
    int deleteRear() {
        if (isEmpty()) {
            cout << "Deque Empty Error" << endl;
            exit(EXIT_FAILURE);
        }
        else {
            if (front == rear)
            {
                int data = rear->data;
                auto node = rear;
                delete rear;
                rear = nullptr;
                --dataSize;
                return data;
            }
            else
            {
                int data = rear->data;
                Node* node = rear;
                rear = rear->prev;
                rear->setNext(nullptr);
                delete node;
                --dataSize;
                return data;
            }
        }
    }

    // deque의 모든 data 출력
    void display() {
        if (isEmpty()) {
            cout << "Deque is Empty" << endl;
        }
        else {
            Node* node = front;
            while (node) {
                cout << "[" << node->data << "]";
                node = node->next;
            }
            cout << endl;
        }
    }

    // deque size 반환
    int size() {
        return dataSize;
    }

    bool isEmpty() {
        return dataSize == 0;
    }
};

class Queue
{
private:
    Deque* DQ;

public:
    Queue();
    ~Queue();
    void Push(int _iVal);
    int Pop();
    int Size();
    void Display();
};

int main() {
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif  _DEBUG

    Queue Q;

    cout << "=== push x3===" << endl;
    Q.Push(10);
    Q.Push(20);
    Q.Push(30);
    Q.Display();

    cout << "=== pop x2 === " << endl;
    Q.Pop();
    Q.Pop();
    Q.Display();

    return 0;
}

Queue::Queue()
{
    DQ = new Deque;
}

Queue::~Queue()
{
    delete DQ;
    DQ = nullptr;
}

void Queue::Push(int _iVal)
{
    DQ->addRear(_iVal);
}

int Queue::Pop()
{
    if (DQ->isEmpty())
    {
        cout << "Queue Full error" << endl;
        return 0;
    }
    return DQ->deleteFront();
}

int Queue::Size()
{
    return DQ->size();
}

void Queue::Display()
{
    DQ->display();
}
