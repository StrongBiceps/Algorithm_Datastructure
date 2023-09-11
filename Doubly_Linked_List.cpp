#include <iostream>
using namespace std;

template<typename T>
class Doubly_ll
{
private:
	class Doubly_ll_node
	{
	public:
		T* Data;
		Doubly_ll_node* next;
		Doubly_ll_node* prev;
		~Doubly_ll_node()
		{
			delete Data;
		}
	};
public:
	using node = Doubly_ll_node;
	using node_ptr = node*;
private:
	node_ptr header;
	node_ptr Trailer;
	size_t N;
public:
	Doubly_ll() :N(0)
	{
		header = new node{ NULL,NULL,NULL };
		Trailer = new node{ NULL,NULL,NULL };
		header->next = Trailer;
		Trailer->prev = header;
	}
	size_t& Getsize()
	{
		return N;
	}
	void Push_Front(T Value)
	{
		auto new_node = new node{ new T(Value),NULL,NULL };
		header->next->prev = new_node;
		new_node->next = header->next;
		header->next = new_node;
		new_node->prev = header;
		N++;
	}
	void Push_Back(T Value)
	{
		auto new_node = new node{ new T(Value),NULL,NULL };
		Trailer->prev->next = new_node;
		new_node->next = Trailer;
		new_node->prev = Trailer->prev;
		Trailer->prev = new_node;
		N++;
	}
	void Erase(T Value)
	{
		auto cur = header->next;
		auto end = Trailer;
		while (cur != end)
		{
			if (*(cur->Data) == Value)
			{
				cur->prev->next = cur->next;
				cur->next->prev = cur->prev;
				delete cur;
				N--;
				return;
			}
			cur = cur->next;
		}
	}
	class Doubly_ll_it
	{
	private:
		node_ptr ptr;
	public:
		Doubly_ll_it(node_ptr p) :ptr(p) {}
		T& operator*()
		{
			return *(ptr->Data);
		}
		node_ptr& Get()
		{
			return ptr;
		}
		Doubly_ll_it& operator++()
		{
			ptr = ptr->next;
			return *this;
		}
		Doubly_ll_it operator++(int)
		{
			auto it = *this;
			++(*this);
			return it;
		}
		Doubly_ll_it& operator--()
		{
			ptr = ptr->prev;
			return *this;
		}
		Doubly_ll_it operator--(int)
		{
			auto it = *this;
			--(*this);
			return it;
		}
		friend bool operator==(const Doubly_ll_it& it1, const Doubly_ll_it& it2)
		{
			return it1.ptr == it2.ptr;
		}
		friend bool operator!=(const Doubly_ll_it& it1, const Doubly_ll_it& it2)
		{
			return it1.ptr != it2.ptr;
		}
	};
	Doubly_ll_it begin() { return Doubly_ll_it{ header->next }; }
	Doubly_ll_it end() { return Doubly_ll_it{ Trailer }; }
	Doubly_ll_it begin() const { return Doubly_ll_it{ header->next }; }
	Doubly_ll_it end() const { return Doubly_ll_it{ Trailer }; }
	Doubly_ll(const Doubly_ll& Other) :Doubly_ll()
	{
		for (const auto& i : Other)
		{
			Push_Back(i);
		}
	}
	Doubly_ll(const initializer_list<T>& il) :Doubly_ll()
	{
		for (const auto& i : il)
		{
			Push_Back(i);
		}
	}
	~Doubly_ll()
	{
		while (Getsize())
		{
			Erase(*(header->next->Data));
		}
		delete header;
		delete Trailer;
	}
	void LoopOnce()
	{
		for (const auto& i : *this)
		{
			cout << i << " ";
		}
		cout << endl;
	}
};

int main()
{
	//40 30 20 10 
	Doubly_ll<int> il;
	il.Push_Front(10);
	il.Push_Front(20);
	il.Push_Front(30);
	il.Push_Front(40);
	Doubly_ll<int> il2(il);
	//40 30 10 50
	il2.Erase(20);
	il2.Push_Back(50);
	il2.LoopOnce();
}