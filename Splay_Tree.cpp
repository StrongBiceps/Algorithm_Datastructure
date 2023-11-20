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

//�ڵ��� ������ ���󰡺���, ���� �ܺ��� if-else ������ �� ��쿡 ���� ���� �������� key�� 1�� ���踦 �����ϴ� ��尡 Root�� �ö�´�.
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

	//insert ���꿡���� ������ ���ҿ� 1�� ������ ��带 Root���� ȸ������ �ø� �� Root�� ������ ���� �����ϴ� �۾��� �Ѵ�.
	//���� ������ �м��غ���,
	//���� ������������ �����ϰ� �Ǹ� ������ ���� ���� ��尡 Root�� �ְ� �ȴ�. �׷��� Insert���꿡�� root->key > key�� �����
	//temp->left = root->left;�� �ڵ忡�� root�� left���� temp�� ���� ������ �� �ڵ尡 ��ȿ�Ѱ�? ��� �ǹ��� �ذ�ȴ�. Root�� ���� �ڽ��� ���� �����̴�.
	//���� �Ʒ� ���ó�� �������� ��, �������� ������ �����ϰ� �Ǹ� 3�� ������ ������ Root�� �� �ڽ��� �����ϰ� �ȴ�. ������ �̹����� �������� ȸ���߱�
	//������ 5�� Root�� �ǰ� 5�� ���� �ڽ��� 3�� ���� �ڽ��� �Ǿ ������ ����. 
	//������ �ٺ������� Splay �Լ��� �м��غ��� �� �� �ִ�. ���� Root�� Left�� Temp���� �Ǵٸ�, splay ��Ϳ� ���ؼ� Root�� Left�� Root�� �ö���� ���̴�.
	//�� Splay ���꿡 ���ؼ� ��Ȯ�� ���Ե� ���� ġȯ�Ǿ�� �� ��尡 �ö���� ������ ���� ������ �� �ʿ䰡 ����.
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

	//4�� ã�� Search�ϴ� �����̶�� ��������. Splay Tree�� Search ���꿡�� �ش� ���Ҹ� Splay�ϹǷ� 4�� Root�� �ȴ�.
	root = splay(root,4);
	cout << "Preorder traversal of the modified Splay "
		"tree: \n";
	return 0;
}
