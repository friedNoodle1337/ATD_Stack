#ifndef CLASSSTACK_H
#define CLASSSTACK_H

template <typename T>
class MyStack
{
public:

	MyStack():
		head_(nullptr)
	{  }
	~MyStack();

	MyStack &operator=(MyStack &&right) noexcept;

	bool isEmpty();
	void push(T item);
	void pop();
	T top();
	void print();

	friend std::ostream &operator <<(std::ostream &out, const MyStack &stack);

private:

	struct Node
	{
		T item_;
		Node *next_;

		Node(T item, Node *next = nullptr):
			item_(item),
			next_(next)
		{  }
	};

	Node *head_;

	void swap(MyStack &other) noexcept;

};

#endif CLASSSTACK_H
