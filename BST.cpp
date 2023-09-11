#include <iostream>
using namespace std;

template<typename T>
class BST
{
public:
	class BST_node
	{
	public:
		T Data;
		BST_node* Left;
		BST_node* Right;
	};

	using node = BST_node;
	using node_ptr = node*;
private:
	node_ptr Root;
public:
	BST() :Root(NULL) {}
	node_ptr find(T Value)
	{
		return find_impl(Root, Value);
	}
	void insert(T Value)
	{
		if (!Root)
		{
			Root = new node{ Value,NULL,NULL };
		}
		else
		{
			insert_impl(Root, Value);
		}
	}
	void inOrder()
	{
		inOrder_impl(Root);
	}
	node_ptr Successor(node_ptr Start)
	{
		auto cur = Start->Right;
		while (cur && cur->Left)
		{
			cur = cur->Left;
		}
		return cur;
	}
	void delete_Value(T Value)
	{
		Root = delete_impl(Root, Value);
	}
private:
	node_ptr find_impl(node_ptr current, T Value)
	{
		if (!current)
		{
			cout << "Error";
			return;
		}
		if (current->Data == Value)
		{
			return current;
		}
		if (current->Data > Value)
		{
			find_impl(current->Left, Value);
		}
		find_impl(current->Right, Value);
	}
	void insert_impl(node_ptr current, T Value)
	{
		if (Value < current->Data)
		{
			if (!current->Left)
			{
				current->Left = new node{ Value,NULL,NULL };
			}
			else
			{
				insert_impl(current->Left, Value);
			}
		}
		else
		{
			if (!current->Right)
			{
				current->Right = new node{ Value,NULL,NULL };
			}
			else
			{
				insert_impl(current->Right, Value);
			}
		}
	}
	void inOrder_impl(node_ptr Start)
	{
		if (!Start)
			return;
		inOrder_impl(Start->Left);
		cout << "¹æ¹® " << Start->Data << ",";
		inOrder_impl(Start->Right);
	}
	node_ptr delete_impl(node_ptr Start, T Value)
	{
		if (!Start)
		{
			cout << "Error";
			return Start;
		}
		if (Start->Data < Value)
		{
			Start->Right = delete_impl(Start->Right, Value);
		}
		else if (Start->Data > Value)
		{
			Start->Left = delete_impl(Start->Left, Value);
		}
		else
		{
			if (!Start->Left)
			{
				auto temp = Start->Right;
				delete Start;
				return temp;
			}
			if (!Start->Right)
			{
				auto temp = Start->Left;
				delete Start;
				return temp;
			}
			auto SuccNode = Successor(Start);
			Start->Data = SuccNode->Data;
			Start->Right = delete_impl(Start->Right, SuccNode->Data);
		}
		return Start;
	}
};

int main()
{
	BST<int> B1;
	B1.insert(10);
	B1.insert(5);
	B1.insert(20);
	B1.insert(30);
	B1.delete_Value(20);
	B1.inOrder();
}