#ifndef _STACK_HPP
#define _STACK_HPP

#include <iostream>
#include <algorithm>

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
		Items = nullptr;

		try {
			Items = new int[size];
		}
		catch (std::bad_alloc) {
			std::cerr << "Allocazione di memoria fallita :(" << std::endl;
		}
	}

	~Stack()
	{
		delete[] Items;
	}

	Stack(const Stack& other) {
		top_pos = -1;
		maximum_size = 0;
		Items = nullptr;

		try {
			Items = new int[other.maximum_size];
		}
		catch (std::bad_alloc) {
			std::cerr << "Allocazione di memoria fallita :(" << std::endl;
		}

		for (unsigned int i = 0; i < other.maximum_size; ++i) {
			Items[i] = other.Items[i];
			top_pos++;
		}

		maximum_size = other.maximum_size;
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

	void swap(Stack& other) {
		std::swap(this->Items, other.Items);
		std::swap(this->top_pos, other.top_pos);
		std::swap(this->maximum_size, other.maximum_size);
	}

	Stack& operator=(const Stack& other) {
		if (this != &other) {
			Stack tmp(other);
			tmp.swap(*this);
		}

		return *this;
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
