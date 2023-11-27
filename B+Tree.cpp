//#include <iostream>
//#include <queue>
//using namespace std;
//typedef long long ll;
//typedef unsigned long long ull;
//#define pb push_back
//
//const int bucketSize = 3;
//
//// Create 2 classes, one for node and one for tree;
//
//class node {
//public:
//	bool isLeaf;
//	//node** ptr;
//	vector<node*> ptr;
//	int* key, size;
//	node();
//};
//node::node()
//{
//	key = new int[bucketSize];
//	//ptr = new node * [bucketSize + 1];
//	ptr.resize(10000);
//	fill(ptr.begin(), ptr.end(), nullptr);
//}
//class Btree {
//public:
//	// Root of tree stored here;
//	node* root;
//	Btree();
//	void deleteNode(int);
//
//	int search(int);
//	void display(node*);
//	void insert(int);
//	node* findParent(node*, node*);
//	node* getRoot();
//	void shiftLevel(int, node*, node*);
//};
//
//node* Btree::getRoot() { return root; }
//Btree::Btree() { root = NULL; }
//
//void Btree::insert(int x)
//{
//	if (root == NULL) {
//		root = new node;
//		root->key[0] = x;
//		root->isLeaf = true;
//		root->size = 1;
//	}
//
//	else {
//		node* current = root;
//		node* parent = nullptr;
//
//		//������ ��ġ�� ���� ���� �̵��Ѵ�.
//		while (current->isLeaf == false) {
//			parent = current;
//
//			for (int i = 0; i < current->size; i++) {
//				if (x < current->key[i]) {
//					current = current->ptr[i];
//					break;
//				}
//
//				if (i == current->size - 1) {
//					current = current->ptr[i + 1];
//					break;
//				}
//			}
//		}
//
//		// now we have reached leaf;
//		if (current->size
//			< bucketSize) { // if the node to be inserted is
//							// not filled
//			//���� ��尡 �� ���� �ʾ��� ��
//			int i = 0;
//
//			// Traverse btree
//			while (x > current->key[i] && i < current->size)
//				// goto pt where needs to be inserted.
//				i++;
//
//			for (int j = current->size; j > i; j--)
//				// adjust and insert element;
//				//������ ���� �ڸ��� shift�Ѵ�.
//				current->key[j] = current->key[j - 1];
//
//			//������ ��ġ�� �����Ѵ�.
//			current->key[i] = x;
//
//			// size should be increased by 1
//			current->size++;
//
//			//Ű ���� �ϳ� �þ���Ƿ� �� ���� ��带 ����Ű�� ���� �ε����� �ϳ� ������Ų��.
//			current->ptr[current->size]
//				= current->ptr[current->size - 1];
//			current->ptr[current->size - 1] = NULL;
//		}
//
//		// if block does not have enough space;
//		//��尡 �� á�� ��
//		else {
//			node* newLeaf = new node;
//			int tempNode[bucketSize + 1];
//
//			for (int i = 0; i < bucketSize; i++)
//				// all elements of this block stored
//				tempNode[i] = current->key[i];
//			int i = 0, j = 0;
//
//			// find the right posn of num to be inserted
//			while (x > tempNode[i] && i < bucketSize)
//				i++;
//
//			for (int j = bucketSize + 1; j > i; j--)
//				tempNode[j] = tempNode[j - 1];
//			tempNode[i] = x;
//			// inserted element in its rightful position;
//			//���Ե� ������ ������ �ڸ��� ã�´�.
//
//			newLeaf->isLeaf = true;
//			current->size = (bucketSize + 1) / 2;
//			newLeaf->size
//				= (bucketSize + 1)
//				- (bucketSize + 1)
//				/ 2; // now rearrangement begins!
//			//������ ����
//
//			//���� ����� ���� ��带 newleaf�� �����Ѵ�.
//			current->ptr[current->size] = newLeaf;
//			//���� current ����� ���� ��带 newleaf����� ���� ���� �����Ѵ�.
//			newLeaf->ptr[newLeaf->size]
//				= current->ptr[bucketSize];
//
//			current->ptr[newLeaf->size]
//				= current->ptr[bucketSize];
//			current->ptr[bucketSize] = NULL;
//
//			//���Ҹ� ������ �۾�
//			for (int i = 0; i < current->size; i++)
//				current->key[i] = tempNode[i];
//
//			for (int i = 0, j = current->size;
//				i < newLeaf->size; i++, j++)
//				newLeaf->key[i] = tempNode[j];
//
//			// if this is root, then fine,
//			// else we need to increase the height of tree;
//			if (current == root) {
//				node* newRoot = new node;
//				newRoot->key[0] = newLeaf->key[0];
//				newRoot->ptr[0] = current;
//				newRoot->ptr[1] = newLeaf;
//				newRoot->isLeaf = false;
//				newRoot->size = 1;
//				root = newRoot;
//			}
//			else
//				//�θ� ��忡 �ڽ��� �߰��ϰ� ���Ҹ� �����ϴ� ����
//				shiftLevel(
//					newLeaf->key[0], parent,
//					newLeaf); // parent->original root
//		}
//	}
//}
//
//void Btree::shiftLevel(int x, node* current, node* child)
//{ // insert or create an internal node;
//	//���� �θ� ����� current�� ���� ������ �ִٸ� �Ʒ� �ڵ带 �����Ѵ�.
//	if (current->size
//		< bucketSize) { // if can fit in this level, do that
//		int i = 0;
//		while (x > current->key[i] && i < current->size)
//			i++;
//		for (int j = current->size; j > i; j--)
//			current->key[j] = current->key[j - 1];
//
//		for (int j = current->size + 1; j > i + 1; j--)
//			current->ptr[j] = current->ptr[j - 1];
//
//		current->key[i] = x;
//		current->size++;
//
//		//���� �������� ������ newleaf�� �ڽ����� �����.
//		current->ptr[i + 1] = child;
//	}
//
//	// shift up
//	//���� �θ� ��� ���� �� á�ٸ� �����Ѵ�. �����ϱ� ������ shift�Լ��� �ٽ� ȣ��� ���̴�.
//	else {
//		node* newInternal = new node;
//		int tempKey[bucketSize + 1];
//		node* tempPtr[bucketSize + 2];
//
//		for (int i = 0; i < bucketSize; i++)
//			tempKey[i] = current->key[i];
//
//		for (int i = 0; i < bucketSize + 1; i++)
//			tempPtr[i] = current->ptr[i];
//
//		int i = 0, j = 0;
//		while (x > tempKey[i] && i < bucketSize)
//			i++;
//
//		for (int j = bucketSize + 1; j > i; j--)
//			tempKey[j] = tempKey[j - 1];
//
//		tempKey[i] = x;
//		for (int j = bucketSize + 2; j > i + 1; j--)
//			tempPtr[j] = tempPtr[j - 1];
//
//		tempPtr[i + 1] = child;
//		newInternal->isLeaf = false;
//		current->size = (bucketSize + 1) / 2;
//
//		newInternal->size
//			= bucketSize - (bucketSize + 1) / 2;
//
//		for (int i = 0, j = current->size + 1;
//			i < newInternal->size; i++, j++)
//			newInternal->key[i] = tempKey[j];
//
//		for (int i = 0, j = current->size + 1;
//			i < newInternal->size + 1; i++, j++)
//			newInternal->ptr[i] = tempPtr[j];
//
//		if (current == root) {
//			node* newRoot = new node;
//			newRoot->key[0] = current->key[current->size];
//			newRoot->ptr[0] = current;
//			newRoot->ptr[1] = newInternal;
//			newRoot->isLeaf = false;
//			newRoot->size = 1;
//			root = newRoot;
//		}
//
//		else
//			shiftLevel(current->key[current->size],
//				findParent(root, current),
//				newInternal);
//	}
//}
//int Btree::search(int x)
//{
//	if (root == NULL)
//		return -1;
//
//	else {
//		node* current = root;
//
//		//���� ��忡 ������ �� ���� ������ ��ġ�� ã�ư���.
//		while (current->isLeaf == false) {
//			for (int i = 0; i < current->size; i++) {
//				if (x < current->key[i]) {
//					current = current->ptr[i];
//					break;
//				}
//
//				if (i == current->size - 1) {
//					current = current->ptr[i + 1];
//					break;
//				}
//			}
//		}
//
//		for (int i = 0; i < current->size; i++) {
//			if (current->key[i] == x) {
//				// cout<<"Key found "<<endl;
//				return 1;
//				// return;
//			}
//		}
//
//		// cout<<"Key not found"<<endl;
//		return 0;
//	}
//}
//
//// Print the tree
//void Btree::display(node* current)
//{
//	if (current == NULL)
//		return;
//	queue<node*> q;
//	q.push(current);
//
//	//���� ���� �������� ����� �ڽĵ��� ���ʴ�� ���ʺ��� ��ȸ�ϸ鼭 display�ϴ� �Լ�
//	while (!q.empty()) {
//		int l;
//		l = q.size();
//
//		for (int i = 0; i < l; i++) {
//			node* tNode = q.front();
//			q.pop();
//
//			for (int j = 0; j < tNode->size; j++)
//				if (tNode != NULL)
//					cout << tNode->key[j] << " ";
//
//			for (int j = 0; j < tNode->size + 1; j++)
//				if (tNode->ptr[j] != NULL)
//					q.push(tNode->ptr[j]);
//
//			cout << "\t";
//		}
//		cout << endl;
//	}
//}
//
////�θ� ��带 ã�� �Լ� child�� current ������ ���踦 �����Ͽ� child�� �θ� �����Ѵ�.
////current�� root���� ���۵Ǿ� ��ͷ� ã�ư���.
//node* Btree::findParent(node* current, node* child)
//{
//	node* parent = nullptr;
//	if (current->isLeaf || (current->ptr[0])->isLeaf)
//		return NULL;
//
//	for (int i = 0; i < current->size + 1; i++) {
//		if (current->ptr[i] == child) {
//			parent = current;
//			return parent;
//		}
//		else {
//			parent = findParent(current->ptr[i], child);
//			if (parent != NULL)
//				return parent;
//		}
//	}
//	return parent;
//}
//
//signed main()
//{
//	ios_base::sync_with_stdio(false);
//	Btree node;
//	cout << "The size of bucket is " << bucketSize << "! "
//		<< endl;
//
//	node.insert(1);
//	node.insert(2);
//	node.insert(3);
//	node.display(node.getRoot());
//	node.insert(4);
//	node.insert(5);
//	node.display(node.getRoot());
//
//	return 0;
//}

/*
 * B_Plus_Tree example
 *
 *
 * 20210112, youseop, jeongseo, gojae
 *
 *
 */

//from https://github.com/Jeongseo21/Data_structure---B_tree/blob/main/%5BData%20structure%5D%20B%20tree/%5BData%20structure%5D%20B%20tree/B%2Btree.c

 /*
  * B-Tree :
  *   1. Every node has at most 2*DEGREE children.
  *   2. Every node has at most 2*DEGREE -1 keys.
  *   3. Every node (except root) has more than DEGREE - 1 keys.
  *   4. A node with n keys contains n+1 children.
  *   5. All leaves appear in the same level.
  */

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define EMPTY 0
#define DEGREE 3 /*The degree of the tree.*/

#pragma warning(disable:4996)

typedef struct node
{
	int key[2 * DEGREE - 1];
	struct node* child[2 * DEGREE];
	int leaf;
	int n;
	struct node* next;
}
node;
typedef struct B_Plus_Tree
{
	node* root;
}B_Plus_Tree;
void B_Plus_Tree_Create(B_Plus_Tree* T);
void B_Plus_Tree_Insert(B_Plus_Tree* T, int k);
void B_Tree_Split_Child(node* x, int i);
void B_Plus_Tree_Split_Child(node* x, int i);
void B_Plus_Tree_Insert_Nonfull(node* x, int k);
void B_Plus_Tree_Display(B_Plus_Tree* T);
void B_Plus_Tree_Display_Main(node* x, int h);
void B_Plus_Tree_Leaf_Check(B_Plus_Tree* x);
void B_Plus_Tree_insert_items(B_Plus_Tree* T, int x, int y);
void B_Plus_Tree_Delete(B_Plus_Tree* T, int k);
void B_Plus_Tree_Delete_main(node* x, int k);
void main()
{
	B_Plus_Tree* T = (B_Plus_Tree*)malloc(sizeof(B_Plus_Tree));
	if (T == NULL) {
		printf("memory allocation falied");
		return;
	}
	B_Plus_Tree_Create(T);
	int command, x, y;
	printf("##########################\n\n    $ B_Plus_TREE Project $ \n\nproduced by \n\n@jeongseo \n@youseop \n@gojae\n\n##########################\n\n");
	while (1) {
		printf("\n1: insert one item\n2: insert items (x~y)\n3: delete item\n4: display\ncommad: ");
		scanf("%d", &command);
		if (command == 1) {
			printf("insert item: ");
			getchar();
			scanf("%d", &x);
			B_Plus_Tree_Insert(T, x);
			B_Plus_Tree_Display(T);
		}
		else if (command == 2) {
			printf("\ninsert x & y\n (y should be bigger than x)\nx: ");
			getchar();
			scanf("%d", &x);
			printf("y: ");
			getchar();
			scanf("%d", &y);
			B_Plus_Tree_insert_items(T, x, y);
		}
		else if (command == 3) {
			printf("\ninsert a number you wanna delete.\nk : ");
			getchar();
			scanf("%d", &x);
			B_Plus_Tree_Delete(T, x);
			B_Plus_Tree_Display(T);
		}
		else if (command == 4) {
			B_Plus_Tree_Display(T);
		}
		else if (command == 0) {
			break;
		}
		getchar();
	}
	free(T);
}
void B_Plus_Tree_Create(B_Plus_Tree* T)
{
	node* x = (node*)malloc(sizeof(node));
	if (x == NULL) {
		printf("memory allocation falied");
		return;
	}
	x->next = NULL;
	x->leaf = TRUE;
	x->n = 0;
	T->root = x;
}
void B_Plus_Tree_Insert(B_Plus_Tree* T, int k)
{
	node* r = T->root;
	if (r->n == 2 * DEGREE - 1)
	{
		node* s = (node*)malloc(sizeof(node));
		if (s == NULL) {
			printf("memory allocation falied");
			return;
		}
		T->root = s;
		s->leaf = FALSE;
		s->next = NULL; // ���⵵ �־���� �ұ�?#####################################
		s->n = 0;
		s->child[0] = r;
		if (r->leaf == 1) {
			B_Plus_Tree_Split_Child(s, 0);
		}
		else {
			B_Tree_Split_Child(s, 0);
		}
		B_Plus_Tree_Insert_Nonfull(s, k);
	}
	else
	{
		B_Plus_Tree_Insert_Nonfull(r, k);
	}
}
void B_Tree_Split_Child(node* x, int i)
{
	node* z = (node*)malloc(sizeof(node));
	if (z == NULL)
	{
		printf("memory allocation falied");
		return;
	}
	node* y = x->child[i]; // 0 <= i
	z->leaf = y->leaf;
	z->n = DEGREE - 1;
	for (int j = 0; j < DEGREE - 1; j++)
	{
		z->key[j] = y->key[j + DEGREE];
	}
	if (y->leaf == FALSE)
	{
		for (int j = 0; j < DEGREE; j++)
		{
			z->child[j] = y->child[j + DEGREE];
		}
	}
	y->n = DEGREE - 1;
	for (int j = x->n; j > i; j--)
	{
		x->child[j + 1] = x->child[j];
	}
	x->child[i + 1] = z;
	for (int j = x->n - 1; j > i - 1; j--)
	{
		x->key[j + 1] = x->key[j];
	}
	x->key[i] = y->key[DEGREE - 1];
	x->n = x->n + 1;
}
void B_Plus_Tree_Split_Child(node* x, int i) {
	node* z = (node*)malloc(sizeof(node));
	if (z == NULL)
	{
		printf("memory allocation falied");
		return;
	}
	node* y = x->child[i];
	z->leaf = y->leaf;
	z->n = DEGREE;
	for (int j = x->n - 1; j > i - 1; j--) {
		x->key[j + 1] = x->key[j];
	}
	for (int j = x->n; j > i; j--) {
		x->child[j + 1] = x->child[j];
	}
	x->key[i] = y->key[DEGREE - 1];
	x->child[i + 1] = z;
	for (int j = 0; j < DEGREE; j++) {
		z->key[j] = y->key[DEGREE - 1 + j];
	}
	y->n = DEGREE - 1;
	x->n++;
	z->next = y->next;
	y->next = z;
}
void B_Plus_Tree_Insert_Nonfull(node* x, int k)
{
	int i = x->n;
	if (x->leaf)
	{
		i--;
		while (i >= 0 && k < x->key[i])
		{
			x->key[i + 1] = x->key[i];
			i--;
		}
		x->key[i + 1] = k;
		x->n = x->n + 1;
	}
	else {
		while (i >= 1 && k < x->key[i - 1])
		{
			i--;
		}
		if ((x->child[i])->n == 2 * DEGREE - 1)
		{
			if ((x->child[0])->leaf == 1) {
				B_Plus_Tree_Split_Child(x, i);
			}
			else {
				B_Tree_Split_Child(x, i);
			}
			if (k > x->key[i]) {
				i++;
			}
		}
		B_Plus_Tree_Insert_Nonfull(x->child[i], k);
	}
}
void B_Plus_Tree_Delete(B_Plus_Tree* T, int k) {
	node* r = T->root;
	if ((r->n == 1 && r->leaf == FALSE) && ((r->child[0])->n == DEGREE - 1 && (r->child[1])->n == DEGREE - 1)) {
		node* y = r->child[0];
		node* z = r->child[1];
		if (y->leaf == TRUE) {
			for (int j = 0; j < DEGREE - 1; j++) {
				y->key[j + DEGREE - 1] = z->key[j];
			}
			y->n = 2 * DEGREE - 2;
			y->next = NULL;
			T->root = y;
			free(r);
			free(z);
			B_Plus_Tree_Delete_main(y, k);
		}
		else {
			y->key[DEGREE - 1] = r->key[0];
			for (int j = 0; j < DEGREE - 1; j++) {
				y->key[DEGREE + j] = z->key[j];
			}
			for (int j = 0; j < DEGREE; j++) {
				y->child[DEGREE + j] = z->child[j];
			}
			y->n = 2 * DEGREE - 1;
			T->root = y;
			free(r);
			free(z);
			B_Plus_Tree_Delete_main(y, k);
		}
	}
	else {
		B_Plus_Tree_Delete_main(r, k);
	}
	return;
}
void B_Plus_Tree_Delete_main(node* x, int k) {
	int i = x->n;
	while (i > 0 && x->key[i - 1] > k) {
		i--;
	}
	int i_for_key = x->n;
	while (i_for_key > 0 && x->key[i_for_key - 1] >= k) {
		i_for_key--;
	}
	if (x->leaf == TRUE) {//x�� ��������� ��,
		if (x->key[i_for_key] == k) {
			for (int j = i_for_key; j < x->n - 1; j++) {
				x->key[j] = x->key[j + 1];
			}
			x->n--;
			return;
		}
		else {
			printf("no data\n\n");
			return;
		}
	}
	else if ((x->child[i])->n == DEGREE - 1) {//x�� ������尡 �ƴϰ� ���� �� ���� ����� ��
		node* my_way_c = x->child[i];
		if (my_way_c->leaf == FALSE) {//my_way_c�� ������尡 �ƴ� ��
			//����######################################################################
			if (i != 0 && (x->child[i - 1])->n > DEGREE - 1)
			{
				node* left_c = x->child[i - 1];
				for (int j = DEGREE - 2; j >= 0; j--) {
					my_way_c->key[j + 1] = my_way_c->key[j];
				}
				if (my_way_c->leaf == FALSE)
				{
					for (int j = DEGREE - 1; j >= 0; j--) {
						my_way_c->child[j + 1] = my_way_c->child[j];
					}
				}
				my_way_c->key[0] = x->key[i - 1];
				my_way_c->child[0] = left_c->child[left_c->n];
				my_way_c->n++;
				x->key[i - 1] = left_c->key[left_c->n - 1];
				left_c->n--;
			}
			else if (i != x->n && (x->child[i + 1])->n > DEGREE - 1) //������ ���� ����
			{
				node* right_c = x->child[i + 1];
				my_way_c->key[DEGREE - 1] = x->key[i];
				my_way_c->child[DEGREE] = right_c->child[0];
				my_way_c->n++;
				x->key[i] = right_c->key[0];
				for (int j = 0; j < right_c->n - 1; j++)
				{
					right_c->key[j] = right_c->key[j + 1];
				}
				for (int j = 0; j < right_c->n; j++) {
					right_c->child[j] = right_c->child[j + 1];
				}
				right_c->n--;
			}
			else {//x�� k�� ����, ǳ���� ������ ������!!!
				if (i == 0) {
					node* right_c = x->child[i + 1];
					for (int j = 0; j < DEGREE - 1; j++) {
						right_c->key[j + DEGREE] = right_c->key[j];
						right_c->key[j] = my_way_c->key[j];
					}
					if (right_c->leaf == 0) {
						for (int j = 0; j < DEGREE; j++) {
							right_c->child[j + DEGREE] = right_c->child[j];
							right_c->child[j] = my_way_c->child[j];
						}
					}
					right_c->key[DEGREE - 1] = x->key[i];
					right_c->n = DEGREE * 2 - 1;
					for (int j = 0; j < x->n - 1; j++) {
						x->key[j] = x->key[j + 1];
					}
					for (int j = 0; j < x->n; j++)
					{
						x->child[j] = x->child[j + 1];
					}
					free(my_way_c);
					my_way_c = right_c;
					x->n--;
				}
				else {
					node* left_c = x->child[i - 1];
					left_c->key[DEGREE - 1] = x->key[i - 1];
					for (int j = 0; j < DEGREE - 1; j++) {
						left_c->key[j + DEGREE] = my_way_c->key[j];
					}
					if (left_c->leaf == 0) {
						for (int j = 0; j < DEGREE; j++) {
							left_c->child[j + DEGREE] = my_way_c->child[j];
						}
					}
					left_c->n = 2 * DEGREE - 1;
					for (int j = i - 1; j < x->n - 1; j++) {
						x->key[j] = x->key[j + 1];
					}
					for (int j = i; j < x->n; j++) {
						x->child[j] = x->child[j + 1];
					}
					free(my_way_c);
					my_way_c = left_c;
					x->n--;
				}
			}
			B_Plus_Tree_Delete_main(my_way_c, k);
			//����######################################################################
		}
		else {//my_way_c�� ��������� ��, **B_Tree������ ������ �ٸ� ���**
			if (i != 0 && (x->child[i - 1])->n > DEGREE - 1) {
				//������ ǳ���ؼ� ���ʿ��� ������ �� �ִ� ���
				node* left_c = x->child[i - 1];
				for (int j = DEGREE - 2; j >= 0; j--) {
					my_way_c->key[j + 1] = my_way_c->key[j];
				}
				my_way_c->key[0] = left_c->key[left_c->n - 1];
				my_way_c->n++;
				x->key[i - 1] = left_c->key[left_c->n - 1];
				left_c->n--;
			}
			else if (i != x->n && (x->child[i + 1])->n > DEGREE - 1) {
				//�������� ǳ���ؼ� �����ʿ��� ������ �� �ִ� ���
				node* right_c = x->child[i + 1];
				my_way_c->key[DEGREE - 1] = right_c->key[0];
				my_way_c->n++;
				for (int j = 0; j < right_c->n - 1; j++) {
					right_c->key[j] = right_c->key[j + 1];
				}
				x->key[i] = right_c->key[0];
				right_c->n--;
			}
			else {
				//������尡 ��� ���
				if (i == 0) {
					node* right_c = x->child[i + 1];
					for (int j = 0; j < DEGREE - 1; j++) {
						my_way_c->key[DEGREE - 1 + j] = right_c->key[j];
					}
					my_way_c->n = 2 * DEGREE - 2;
					my_way_c->next = right_c->next;
					for (int j = 0; j < x->n - 1; j++) {
						x->key[j] = x->key[j + 1];
					}
					for (int j = 1; j < x->n; j++) {
						x->child[j] = x->child[j + 1];
					}
					x->n--;
					free(right_c);
				}
				else {
					node* left_c = x->child[i - 1];
					for (int j = 0; j < DEGREE - 1; j++) {
						left_c->key[DEGREE - 1 + j] = my_way_c->key[j];
					}
					left_c->n = 2 * DEGREE - 2;
					left_c->next = my_way_c->next;
					for (int j = i - 1; j < x->n - 1; j++) {
						x->key[j] = x->key[j + 1];
					}
					for (int j = i; j < x->n; j++) {
						x->child[j] = x->child[j + 1];
					}
					x->n--;
					free(my_way_c);
					my_way_c = left_c;
				}
			}
			B_Plus_Tree_Delete_main(my_way_c, k);
		}
	}
	else {
		//���� �� ���� ǳ���� �� �׳� �Ʒ��� ������
		B_Plus_Tree_Delete_main(x->child[i], k);
	}
	return;
}
void B_Plus_Tree_Display(B_Plus_Tree* T)
{
	node* r = T->root;
	B_Plus_Tree_Display_Main(r, 1);
	B_Plus_Tree_Leaf_Check(T);
}
void B_Plus_Tree_Display_Main(node* x, int h)
{
	printf("%d : ", h);
	for (int i = 0; i < x->n; i++)
	{
		printf("%d ", x->key[i]);
	}
	printf("\n");
	if (x->leaf == 0)
	{
		for (int i = 0; i < x->n + 1; i++)
		{
			B_Plus_Tree_Display_Main(x->child[i], h + 1);
		}
	}
}
void B_Plus_Tree_Leaf_Check(B_Plus_Tree* T) {
	printf("[linked list connection check]\n");
	node* x = T->root;
	while (x->leaf == 0) {
		x = x->child[0];
	}
	while (x->next != NULL) {
		printf("[ ");
		for (int i = 0; i < x->n; i++) {
			printf("%d ", x->key[i]);
		}
		printf("]");
		x = x->next;
	}
	printf("[ ");
	for (int i = 0; i < x->n; i++) {
		printf("%d ", x->key[i]);
	}
	printf("]");
	printf("\n[done]\n\n");
}
void B_Plus_Tree_insert_items(B_Plus_Tree* T, int x, int y) {
	for (int i = x; i < y + 1; i++) {
		B_Plus_Tree_Insert(T, i);
	}
	B_Plus_Tree_Display(T);
}