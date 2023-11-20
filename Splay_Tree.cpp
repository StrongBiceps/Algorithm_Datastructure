// C++ code for the above approach:
#include <iostream>
using namespace std;

struct node {
	int key;
	node* left, * right;
};

node* newNode(int key)
{
	node* temp = new node;
	temp->key = key;
	temp->left = temp->right = NULL;
	return temp;
}

node* rightRotate(node* x)
{
	node* y = x->left;
	x->left = y->right;
	y->right = x;
	return y;
}

node* leftRotate(node* x)
{
	node* y = x->right;
	x->right = y->left;
	y->left = x;
	return y;
}

//코드의 진행을 따라가보면, 가장 외부의 if-else 문에서 두 경우에 대해 삽입 과정에서 key와 1촌 관계를 유지하는 노드가 Root로 올라온다.
node* splay(node* root, int key)
{
	if (root == NULL || root->key == key)
		return root;

	if (root->key > key) {
		if (root->left == NULL)
			return root;
		if (root->left->key > key) {
			root->left->left = splay(root->left->left, key);
			root = rightRotate(root);
		}
		else if (root->left->key < key) {
			root->left->right
				= splay(root->left->right, key);
			if (root->left->right != NULL)
				root->left = leftRotate(root->left);
		}
		return (root->left == NULL) ? root
			: rightRotate(root);
	}
	else {
		if (root->right == NULL)
			return root;
		if (root->right->key > key) {
			root->right->left
				= splay(root->right->left, key);
			if (root->right->left != NULL)
				root->right = rightRotate(root->right);
		}
		else if (root->right->key < key) {
			root->right->right
				= splay(root->right->right, key);
			root = leftRotate(root);
		}
		return (root->right == NULL) ? root
			: leftRotate(root);
	}
}

node* insert(node* root, int key)
{
	if (root == NULL)
		return newNode(key);

	root = splay(root, key);

	if (root->key == key)
		return root;

	node* temp = newNode(key);
	if (root->key > key) {
		temp->right = root;
		temp->left = root->left;
		root->left = NULL;
	}
	else {
		temp->left = root;
		temp->right = root->right;
		root->right = NULL;
	}
	return temp;
}

// Drivers code
int main()
{
	node* root = NULL;
	/*root = insert(root, 100);
	root = insert(root, 50);
	root = insert(root, 200);
	root = insert(root, 40);
	root = insert(root, 60);*/

	//insert 연산에서는 삽입할 원소와 1촌 관계의 노드를 Root까지 회전시켜 올린 후 Root를 삽입할 노드로 변경하는 작업을 한다.
	//삽입 연산을 분석해보면,
	//먼저 내림차순으로 삽입하게 되면 무조건 가장 작은 노드가 Root에 있게 된다. 그러면 Insert연산에서 root->key > key의 경우의
	//temp->left = root->left;이 코드에서 root의 left보다 temp가 작을 때에도 이 코드가 유효한가? 라는 의문이 해결된다. Root의 왼쪽 자식이 없기 때문이다.
	//만약 아래 경우처럼 내림차순 반, 오름차순 반으로 삽입하게 되면 3을 삽입할 때에는 Root의 양 자식이 존재하게 된다. 하지만 이번에는 왼쪽으로 회전했기
	//때문에 5가 Root가 되고 5의 왼쪽 자식이 3의 왼쪽 자식이 되어도 문제가 없다. 
	//하지만 근본적으로 Splay 함수를 분석해보면 알 수 있다. 만약 Root의 Left가 Temp보다 컸다면, splay 재귀에 의해서 Root의 Left가 Root로 올라왔을 것이다.
	//즉 Splay 연산에 의해서 정확히 삽입될 노드와 치환되어야 할 노드가 올라오기 때문에 위의 걱정은 할 필요가 없다.
	root = insert(root, 7);
	root = insert(root, 6);
	root = insert(root, 5);
	root = insert(root, 1);
	root = insert(root, 2);
	root = insert(root, 3);

	/*root = insert(root, 7);
	root = insert(root, 6);
	root = insert(root, 5);
	root = insert(root, 1);
	root = insert(root, 3);
	root = insert(root, 2);*/

	//4를 찾는 Search하는 과정이라고 생각하자. Splay Tree는 Search 연산에서 해당 원소를 Splay하므로 4가 Root가 된다.
	root = splay(root,4);
	cout << "Preorder traversal of the modified Splay "
		"tree: \n";
	return 0;
}
