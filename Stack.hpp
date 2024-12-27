#ifndef _STACK_HPP
#define _STACK_HPP

#include <iostream>

struct Maximum_size_reached {};
struct Minimum_size_reached {};

class Stack {
	friend std::ostream& operator<<(std::ostream& os, const Stack& stack);
private:
	int* Items;
	int top_pos;
	unsigned int maximum_size;
public:
	Stack()
	{
		top_pos = -1;
		maximum_size = 0;
		Items = nullptr;
	}

	Stack(const unsigned int& size)
	{
		top_pos = -1;
		maximum_size = size;
		Items = new int[size];
	}

	~Stack()
	{
		delete[] Items;
	}

	void push(const int& value)
	{
		if (maximum_size == top_pos + 1) {
			throw Maximum_size_reached();
		} else {
			top_pos++;
			Items[top_pos] = value;
		}
	}

	int pop()
	{
		if (top_pos == -1) {
			throw Minimum_size_reached();
		} else {
			int old_top = Items[top_pos];
			top_pos--;
			return old_top;
		}
	}

	int peek() const
	{
		if (top_pos == -1) {
			throw Minimum_size_reached();
		} else {
			return Items[top_pos];
		}
	}

	bool stack_empty() const
	{
		if (top_pos == -1) {
			return true;
		} else {
			return false;
		}
	}

	unsigned int size() const
	{
		return maximum_size;	
	}
};

	std::ostream& operator<<(std::ostream& os, const Stack& stack)
	{
		os << "[ ";
		if (!stack.stack_empty()) {
			for (unsigned int i = 0; i <= stack.top_pos; ++i) {
				os << stack.Items[i] << " ";
			}
		}
			os << "]" << std::endl;
		return os;
	}

#endif
