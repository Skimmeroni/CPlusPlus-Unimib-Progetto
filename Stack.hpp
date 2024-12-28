#ifndef _STACK_HPP
#define _STACK_HPP

#include <iostream>
#include <algorithm>

struct Maximum_size_reached {};
struct Minimum_size_reached {};

class Stack {
	friend std::ostream& operator<<(std::ostream& os, const Stack& stack);
	typedef int stack_value;
private:
	stack_value* Items;
	int top_pos;
	unsigned int maximum_size;
public:
	Stack()
	: top_pos(-1), maximum_size(0), Items(nullptr)
	{
		#ifndef NDEBUG
		std::cout << "Stack::Stack()" << std::endl;
		#endif
	}

	explicit Stack(const unsigned int& size)
	: top_pos(-1), maximum_size(0), Items(nullptr)
	{
		try {
			Items = new stack_value[size];
		}
		catch (std::bad_alloc) {
			std::cerr << "Allocazione di memoria fallita :(" << std::endl;
		}

		maximum_size = size;

		#ifndef NDEBUG
		std::cout << "Stack::Stack(unsigned int)" << std::endl;
		#endif
	}

	Stack(const unsigned int& size, const stack_value& value)
	: top_pos(-1), maximum_size(0), Items(nullptr)
	{
		try {
			Items = new stack_value[size];
		}
		catch (std::bad_alloc) {
			std::cerr << "Allocazione di memoria fallita :(" << std::endl;
		}

		for (unsigned int i = 0; i < size; ++i) {
			Items[i] = value;
			top_pos++;
		}

		maximum_size = size;

		#ifndef NDEBUG
		std::cout << "Stack::Stack(unsigned int, stack_value)" << std::endl;
		#endif
	}

	Stack(const Stack& other)
	: top_pos(-1), maximum_size(0), Items(nullptr)
	{
		try {
			Items = new stack_value[other.maximum_size];
		}
		catch (std::bad_alloc) {
			std::cerr << "Allocazione di memoria fallita :(" << std::endl;
		}

		for (unsigned int i = 0; i < other.maximum_size; ++i) {
			Items[i] = other.Items[i];
			top_pos++;
		}

		maximum_size = other.maximum_size;

		#ifndef NDEBUG
		std::cout << "Stack::Stack(const Stack&)" << std::endl;
		#endif
	}

	~Stack()
	{
		delete[] Items;

		#ifndef NDEBUG
		std::cout << "Stack::~Stack()" << std::endl;
		#endif
	}

	void push(const stack_value& value)
	{
		if (maximum_size == top_pos + 1) {
			throw Maximum_size_reached();
		} else {
			top_pos++;
			Items[top_pos] = value;
		}
	}

	stack_value pop()
	{
		if (top_pos == -1) {
			throw Minimum_size_reached();
		} else {
			stack_value old_top = Items[top_pos];
			top_pos--;
			return old_top;
		}
	}

	stack_value peek() const
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

	void fill(const stack_value& value)
	{
		for (unsigned int i = 0; i < maximum_size; ++i) {
			Items[i] = value;
		}
	}

	void swap(Stack& other) {
		std::swap(this->Items, other.Items);
		std::swap(this->top_pos, other.top_pos);
		std::swap(this->maximum_size, other.maximum_size);
	}

	Stack& operator=(const Stack& other) {
		if (this != &other) {
			Stack tmp(other);
			this->swap(tmp);
		}

		#ifndef NDEBUG
		std::cout << "Stack::operator=(const Stack&)" << std::endl;
		#endif

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
