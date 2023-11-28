#include <iostream>
using namespace std;

//class RedBlackTree {
//private:
//	// Node creating subclass
//	struct Node {
//		int data;
//		Node* left;
//		Node* right;
//		char colour;
//		Node* parent;
//
//		Node(int data) : data(data), left(nullptr), right(nullptr), colour('R'), parent(nullptr) {}
//	};
//
//	Node* root;
//	bool ll; // Left-Left Rotation flag
//	bool rr; // Right-Right Rotation flag
//	bool lr; // Left-Right Rotation flag
//	bool rl; // Right-Left Rotation flag
//
//	// Function to perform Left Rotation
//	Node* rotateLeft(Node* node) {
//		Node* x = node->right;
//		Node* y = x->left;
//		x->left = node;
//		node->right = y;
//		node->parent = x;
//		if (y != nullptr)
//			y->parent = node;
//		return x;
//	}
//
//	// Function to perform Right Rotation
//	Node* rotateRight(Node* node) {
//		Node* x = node->left;
//		Node* y = x->right;
//		x->right = node;
//		node->left = y;
//		node->parent = x;
//		if (y != nullptr)
//			y->parent = node;
//		return x;
//	}
//
//	// Helper function for insertion
//	Node* insertHelp(Node* root, int data) {
//		bool f = false; // Flag to check RED-RED conflict
//
//		if (root == nullptr)
//			return new Node(data);
//		else if (data < root->data) {
//			root->left = insertHelp(root->left, data);
//			//왼쪽 자식으로 삽입 후 부모를 설정해주는 코드
//			root->left->parent = root;
//			if (root != this->root) {
//				if (root->colour == 'R' && root->left->colour == 'R')
//					f = true;
//			}
//		}
//		else {
//			root->right = insertHelp(root->right, data);
//			root->right->parent = root;
//			if (root != this->root) {
//				if (root->colour == 'R' && root->right->colour == 'R')
//					f = true;
//			}
//		}
//
//		// Perform rotations
//		if (ll) {
//			root = rotateLeft(root);
//			root->colour = 'B';
//			root->left->colour = 'R';
//			ll = false;
//		}
//		else if (rr) {
//			root = rotateRight(root);
//			root->colour = 'B';
//			root->right->colour = 'R';
//			rr = false;
//		}
//		else if (rl) {
//			root->right = rotateRight(root->right);
//			root->right->parent = root;
//			root = rotateLeft(root);
//			root->colour = 'B';
//			root->left->colour = 'R';
//			rl = false;
//		}
//		else if (lr) {
//			root->left = rotateLeft(root->left);
//			root->left->parent = root;
//			root = rotateRight(root);
//			root->colour = 'B';
//			root->right->colour = 'R';
//			lr = false;
//		}
//
//		// Handle RED-RED conflicts
//		if (f) {
//			if (root->parent->right == root) {
//				if (root->parent->left == nullptr || root->parent->left->colour == 'B') {
//					if (root->left != nullptr && root->left->colour == 'R')
//						rl = true;
//					else if (root->right != nullptr && root->right->colour == 'R')
//						ll = true;
//				}
//				else {
//					root->parent->left->colour = 'B';
//					root->colour = 'B';
//					if (root->parent != this->root)
//						root->parent->colour = 'R';
//				}
//			}
//			else {
//				if (root->parent->right == nullptr || root->parent->right->colour == 'B') {
//					if (root->left != nullptr && root->left->colour == 'R')
//						rr = true;
//					else if (root->right != nullptr && root->right->colour == 'R')
//						lr = true;
//				}
//				else {
//					root->parent->right->colour = 'B';
//					root->colour = 'B';
//					if (root->parent != this->root)
//						root->parent->colour = 'R';
//				}
//			}
//			f = false;
//		}
//		return root;
//	}
//
//	// Helper function to perform Inorder Traversal
//	void inorderTraversalHelper(Node* node) {
//		if (node != nullptr) {
//			inorderTraversalHelper(node->left);
//			std::cout << node->data << " ";
//			inorderTraversalHelper(node->right);
//		}
//	}
//
//	// Helper function to print the tree
//	void printTreeHelper(Node* root, int space) {
//		if (root != nullptr) {
//			space += 10;
//			printTreeHelper(root->right, space);
//			std::cout << std::endl;
//			for (int i = 10; i < space; i++)
//				std::cout << " ";
//			std::cout << root->data << std::endl;
//			printTreeHelper(root->left, space);
//		}
//	}
//
//public:
//	RedBlackTree() : root(nullptr), ll(false), rr(false), lr(false), rl(false) {}
//
//	// Function to insert data into the tree
//	void insert(int data) {
//		if (root == nullptr) {
//			root = new Node(data);
//			root->colour = 'B';
//		}
//		else
//			root = insertHelp(root, data);
//	}
//
//	// Function to perform Inorder Traversal of the tree
//	void inorderTraversal() {
//		inorderTraversalHelper(root);
//	}
//
//	// Function to print the tree
//	void printTree() {
//		printTreeHelper(root, 0);
//	}
//};
//
//int main() {
//	// Test the RedBlackTree
//	RedBlackTree t;
//	int arr[] = { 1, 4, 6, 3, 5, 7, 8, 2, 9 };
//	for (int i = 0; i < 9; i++) {
//		t.insert(arr[i]);
//		std::cout << std::endl;
//		t.inorderTraversal();
//	}
//	t.printTree();
//	return 0;
//}

//https://www.geeksforgeeks.org/deletion-in-red-black-tree/
//매우 까다로우니 위 사이트 참고하며 연습하길 바람.

#include <iostream>
#include <queue>
using namespace std;

enum COLOR { RED, BLACK };

class Node {
public:
	int val;
	COLOR color;
	Node* left, * right, * parent;

	Node(int val) : val(val) {
		parent = left = right = NULL;

		// Node is created during insertion
		// Node is red at insertion
		color = RED;
	}

	// returns pointer to uncle
	Node* uncle() {
		// If no parent or grandparent, then no uncle
		if (parent == NULL or parent->parent == NULL)
			return NULL;

		if (parent->isOnLeft())
			// uncle on right
			return parent->parent->right;
		else
			// uncle on left
			return parent->parent->left;
	}

	// check if node is left child of parent
	bool isOnLeft() { return this == parent->left; }

	// returns pointer to sibling
	Node* sibling() {
		// sibling null if no parent
		if (parent == NULL)
			return NULL;

		if (isOnLeft())
			return parent->right;

		return parent->left;
	}

	// moves node down and moves given node in its place
	void moveDown(Node* nParent) {
		if (parent != NULL) {
			if (isOnLeft()) {
				parent->left = nParent;
			}
			else {
				parent->right = nParent;
			}
		}
		nParent->parent = parent;
		parent = nParent;
	}

	bool hasRedChild() {
		return (left != NULL and left->color == RED) or
			(right != NULL and right->color == RED);
	}
};

class RBTree {
	Node* root;

	// left rotates the given node
	void leftRotate(Node* x) {
		// new parent will be node's right child
		Node* nParent = x->right;

		// update root if current node is root
		if (x == root)
			root = nParent;

		x->moveDown(nParent);

		// connect x with new parent's left element
		x->right = nParent->left;
		// connect new parent's left element with node
		// if it is not null
		if (nParent->left != NULL)
			nParent->left->parent = x;

		// connect new parent with x
		nParent->left = x;
	}

	void rightRotate(Node* x) {
		// new parent will be node's left child
		Node* nParent = x->left;

		// update root if current node is root
		if (x == root)
			root = nParent;

		x->moveDown(nParent);

		// connect x with new parent's right element
		x->left = nParent->right;
		// connect new parent's right element with node
		// if it is not null
		if (nParent->right != NULL)
			nParent->right->parent = x;

		// connect new parent with x
		nParent->right = x;
	}

	void swapColors(Node* x1, Node* x2) {
		COLOR temp;
		temp = x1->color;
		x1->color = x2->color;
		x2->color = temp;
	}

	void swapValues(Node* u, Node* v) {
		int temp;
		temp = u->val;
		u->val = v->val;
		v->val = temp;
	}

	// fix red red at given node
	void fixRedRed(Node* x) {
		// if x is root color it black and return
		if (x == root) {
			x->color = BLACK;
			return;
		}

		// initialize parent, grandparent, uncle
		Node* parent = x->parent, * grandparent = parent->parent,
			* uncle = x->uncle();

		if (parent->color != BLACK) {
			if (uncle != NULL && uncle->color == RED) {
				// uncle red, perform recoloring and recurse
				parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				fixRedRed(grandparent);
			}
			else {
				// Else perform LR, LL, RL, RR
				if (parent->isOnLeft()) {
					if (x->isOnLeft()) {
						// for left right
						swapColors(parent, grandparent);
					}
					else {
						leftRotate(parent);
						swapColors(x, grandparent);
					}
					// for left left and left right
					rightRotate(grandparent);
				}
				else {
					if (x->isOnLeft()) {
						// for right left
						rightRotate(parent);
						swapColors(x, grandparent);
					}
					else {
						swapColors(parent, grandparent);
					}

					// for right right and right left
					leftRotate(grandparent);
				}
			}
		}
	}

	// find node that do not have a left child
	// in the subtree of the given node
	Node* successor(Node* x) {
		Node* temp = x;

		while (temp->left != NULL)
			temp = temp->left;

		return temp;
	}

	// find node that replaces a deleted node in BST
	//후속 노드를 구하는 함수
	Node* BSTreplace(Node* x) {
		// when node have 2 children
		if (x->left != NULL and x->right != NULL)
			return successor(x->right);

		// when leaf
		if (x->left == NULL and x->right == NULL)
			return NULL;

		// when single child
		if (x->left != NULL)
			return x->left;
		else
			return x->right;
	}

	// deletes the given node
	void deleteNode(Node* v) {
		//후속 노드를 반환한다.
		Node* u = BSTreplace(v);

		// True when u and v are both black
		bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
		Node* parent = v->parent;

		if (u == NULL) {
			// u is NULL therefore v is leaf
			if (v == root) {
				// v is root, making root null
				root = NULL;
			}
			else {
				if (uvBlack) {
					// u and v both black
					// v is leaf, fix double black at v
					fixDoubleBlack(v);
				}
				else {
					// u or v is red
					if (v->sibling() != NULL)
						// sibling is not null, make it red"
						// 노드의 삽입 과정을 보면 leaf 노드(NIL을 자식으로 가진 노드)는 형제와 자신 모두 Red일 것이다.
						//이 코드가 왜 있는 것인지 알 수 없다.
						v->sibling()->color = RED;
				}

				// delete v from the tree
				if (v->isOnLeft()) {
					parent->left = NULL;
				}
				else {
					parent->right = NULL;
				}
			}
			delete v;
			return;
		}

		if (v->left == NULL or v->right == NULL) {
			// v has 1 child
			if (v == root) {
				// v is root, assign the value of u to v, and delete u
				v->val = u->val;
				v->left = v->right = NULL;
				delete u;
			}
			else {
				// Detach v from tree and move u up
				if (v->isOnLeft()) {
					parent->left = u;
				}
				else {
					parent->right = u;
				}
				delete v;
				u->parent = parent;
				if (uvBlack) {
					// u and v both black, fix double black at u
					fixDoubleBlack(u);
				}
				else {
					// u or v red, color u black
					u->color = BLACK;
				}
			}
			return;
		}

		// v has 2 children, swap values with successor and recurse
		swapValues(u, v);
		deleteNode(u);
	}

	void fixDoubleBlack(Node* x) {
		if (x == root)
			// Reached root
			return;

		Node* sibling = x->sibling(), * parent = x->parent;
		if (sibling == NULL) {
			// No sibling, double black pushed up
			//Red Black Tree는 리프 노드가 아닌 이상 항상 형제 노드가 있을 것이라고 예상되기 때문에, 이 경우는 Root가 리프 자식만 가지고 있을 때
			//의 경우로 보인다.
			fixDoubleBlack(parent);
		}
		else {
			if (sibling->color == RED) {
				//형제가 빨간색이라면 회전을 수행해야 한다.
				// Sibling red
				parent->color = RED;
				sibling->color = BLACK;
				if (sibling->isOnLeft()) {
					// left case
					rightRotate(parent);
				}
				else {
					// right case
					leftRotate(parent);
				}
				fixDoubleBlack(x);
			}
			else {
				// Sibling black
				if (sibling->hasRedChild()) {
					// at least 1 red children
					if (sibling->left != NULL and sibling->left->color == RED) {
						if (sibling->isOnLeft()) {
							// left left
							sibling->left->color = sibling->color;
							sibling->color = parent->color;
							rightRotate(parent);
						}
						else {
							// right left
							sibling->left->color = parent->color;
							rightRotate(sibling);
							leftRotate(parent);
						}
					}
					else {
						if (sibling->isOnLeft()) {
							// left right
							sibling->right->color = parent->color;
							leftRotate(sibling);
							rightRotate(parent);
						}
						else {
							// right right
							sibling->right->color = sibling->color;
							sibling->color = parent->color;
							leftRotate(parent);
						}
					}
					parent->color = BLACK;
				}
				else {
					// 2 black children
					sibling->color = RED;
					if (parent->color == BLACK)
						fixDoubleBlack(parent);
					else
						parent->color = BLACK;
				}
			}
		}
	}

	// prints level order for given node
	void levelOrder(Node* x) {
		if (x == NULL)
			// return if node is null
			return;

		// queue for level order
		queue<Node*> q;
		Node* curr;

		// push x
		q.push(x);

		while (!q.empty()) {
			// while q is not empty
			// dequeue
			curr = q.front();
			q.pop();

			// print node value
			cout << curr->val << " ";

			// push children to queue
			if (curr->left != NULL)
				q.push(curr->left);
			if (curr->right != NULL)
				q.push(curr->right);
		}
	}

	// prints inorder recursively
	void inorder(Node* x) {
		if (x == NULL)
			return;
		inorder(x->left);
		cout << x->val << " ";
		inorder(x->right);
	}

public:
	// constructor
	// initialize root
	RBTree() { root = NULL; }

	Node* getRoot() { return root; }

	// searches for given value
	// if found returns the node (used for delete)
	// else returns the last node while traversing (used in insert)
	Node* search(int n) {
		Node* temp = root;
		while (temp != NULL) {
			if (n < temp->val) {
				if (temp->left == NULL)
					break;
				else
					temp = temp->left;
			}
			else if (n == temp->val) {
				break;
			}
			else {
				if (temp->right == NULL)
					break;
				else
					temp = temp->right;
			}
		}

		return temp;
	}

	// inserts the given value to tree
	void insert(int n) {
		Node* newNode = new Node(n);
		if (root == NULL) {
			// when root is null
			// simply insert value at root
			newNode->color = BLACK;
			root = newNode;
		}
		else {
			Node* temp = search(n);

			if (temp->val == n) {
				// return if value already exists
				return;
			}

			// if value is not found, search returns the node
			// where the value is to be inserted

			// connect new node to correct node
			newNode->parent = temp;

			if (n < temp->val)
				temp->left = newNode;
			else
				temp->right = newNode;

			// fix red red violation if exists
			fixRedRed(newNode);
		}
	}

	// utility function that deletes the node with given value
	void deleteByVal(int n) {
		if (root == NULL)
			// Tree is empty
			return;

		Node* v = search(n), * u;

		if (v->val != n) {
			cout << "No node found to delete with value:" << n << endl;
			return;
		}

		deleteNode(v);
	}

	// prints inorder of the tree
	void printInOrder() {
		cout << "Inorder: " << endl;
		if (root == NULL)
			cout << "Tree is empty" << endl;
		else
			inorder(root);
		cout << endl;
	}

	// prints level order of the tree
	void printLevelOrder() {
		cout << "Level order: " << endl;
		if (root == NULL)
			cout << "Tree is empty" << endl;
		else
			levelOrder(root);
		cout << endl;
	}
};

int main() {
	RBTree tree;

	tree.insert(7);
	tree.insert(3);
	tree.insert(18);
	tree.insert(10);
	tree.insert(22);
	tree.insert(8);
	tree.insert(11);
	tree.insert(26);
	tree.insert(2);
	tree.insert(6);
	tree.insert(13);

	tree.printInOrder();
	tree.printLevelOrder();

	cout << endl << "Deleting 18, 11, 3, 10, 22" << endl;

	tree.deleteByVal(18);
	tree.deleteByVal(11);
	tree.deleteByVal(3);
	tree.deleteByVal(10);
	tree.deleteByVal(22);

	tree.printInOrder();
	tree.printLevelOrder();
	return 0;
}
