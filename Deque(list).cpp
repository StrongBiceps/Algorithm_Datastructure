#include <iostream>
using namespace std;

//Doubly Linked List�� �̿��Ͽ� ���� ������ ������ ���ӵ� �迭�� ������� �ʴ´�. ���� ���� ������ ���ؼ� ������ �ʿ䰡 ����
//�ܼ��� rear�� front�� ����⿡ �°� ������Ʈ�ϸ� �ȴ�.
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
    Node* prev; // ���� Node�� ����Ű�� pointer
    Node* next; // ���� Node�� ����Ű�� pointer

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
    Node* front;    // Deque�� front�� ����Ű�� Node pointer
    Node* rear;     // Deque�� rear�� ����Ű�� Node pointer
    int dataSize;   // Stack�� ����� ������ size

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

    //���ο� node�� ���� (prev : null, next : ������ front node)
    //front�� ���ο� node�� ����
    //���� �����̶�� rear = node ����
    //���� front�� �߰��� ������ ���� node�� prev�� ���� �߰��Ǵ� node ����
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

    //addFront()�� ���� �ƶ�.
    //���ο� node�� ���� (prev : ������ rear node, next : null)
    //rear�� ���ο� node�� ����
    //���� �����̶�� front = node ����
    //���� rear�� �߰��� ������ ���� node�� next�� ���� �߰��Ǵ� node ����

    //���� ������ ������ front�� rear�� ���� node�� ����Ű�� �ִ�.
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

    //deque�� ����ִ� ��� error occurred
    //�׷��� �ʴٸ�, �켱 front node�� �����͸� �ӽ� ���� 'data'�� ��Ƴ���
    //front�� next node�� ������ ����, ������ node(front����)�� delete ó�� (�޸��ڿ�������)
    //�Ʊ� ��Ƴ��� 'data'�� ��ȯ
    //���� ���� front����� prev�� null�� ����

    //���������� front�� rear�� ���� node�� ����Ű�� ���� ���̴�.
    int deleteFront() {
        if (isEmpty()) {
            cout << "Deque Empty Error" << endl;
            exit(EXIT_FAILURE);
        }
        else {
            //front�� rear�� ���� ��Ȳ������ ��尡 �ϳ� ���̹Ƿ� �ϳ��� ���� ����� �۾���
            //�� �ʿ䰡 ���� �ٷ� �ش� ��带 ���������� �ȴ�.
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

    //deleteFront()�� ���� �ƶ�.
    //deque�� ����ִ� ��� error occurred
    //�׷��� �ʴٸ�, �켱 rear node�� �����͸� �ӽ� ���� 'data'�� ��Ƴ���
    //rear�� prev node�� ������ ����, ������ node(rear����)�� delete ó�� (�޸��ڿ�������)
    //�Ʊ� ��Ƴ��� 'data'�� ��ȯ
    //���� ���� rear����� next�� null�� ����

    ////���������� front�� rear�� ���� node�� ����Ű�� ���� ���̴�.
    int deleteRear() {
        if (isEmpty()) {
            cout << "Deque Empty Error" << endl;
            exit(EXIT_FAILURE);
        }
        else {
            //front�� rear�� ���� ��Ȳ������ ��尡 �ϳ� ���̹Ƿ� �ϳ��� ���� ����� �۾���
            //�� �ʿ䰡 ���� �ٷ� �ش� ��带 ���������� �ȴ�.
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

    // deque�� ��� data ���
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

    // deque size ��ȯ
    int size() {
        return dataSize;
    }

    bool isEmpty() {
        return dataSize == 0;
    }
};

int main() {
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif  _DEBUG

    Deque deque;

    cout << "===== addRear x3 =====" << endl;
    deque.addRear(1);
    deque.addRear(2);
    deque.addRear(3);
    cout << " size : " << deque.size() << endl;
    deque.display();

    cout << "===== addFront x2 ======" << endl;
    deque.addFront(5);
    deque.addFront(6);
    cout << " size : " << deque.size() << endl;
    deque.display();

    cout << "===== deleteRear x1 ======" << endl;
    cout << deque.deleteRear() << endl;
    cout << " size : " << deque.size() << endl;
    deque.display();

    cout << "===== deleteFront x4 ======" << endl;
    cout << deque.deleteFront() << endl;
    cout << deque.deleteFront() << endl;
    cout << deque.deleteFront() << endl;
    cout << deque.deleteFront() << endl;
    cout << " size : " << deque.size() << endl;
    deque.display();

    cout << "===== addRear x3 =====" << endl;
    deque.addRear(1);
    deque.addRear(2);
    deque.addRear(3);
    cout << " size : " << deque.size() << endl;
    deque.display();

    cout << "===== addFront x2 ======" << endl;
    deque.addFront(5);
    deque.addFront(6);
    cout << " size : " << deque.size() << endl;
    deque.display();

    cout << "===== deleteRear x1 ======" << endl;
    cout << deque.deleteRear() << endl;
    cout << " size : " << deque.size() << endl;
    deque.display();

    cout << "===== deleteFront x4 ======" << endl;
    cout << deque.deleteFront() << endl;
    cout << deque.deleteFront() << endl;
    cout << deque.deleteFront() << endl;
    cout << deque.deleteFront() << endl;
    cout << " size : " << deque.size() << endl;
    deque.display();
}