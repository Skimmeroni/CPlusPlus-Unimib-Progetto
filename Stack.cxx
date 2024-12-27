#include "Stack.hpp"
#include <iostream>

int main()
{
	Stack s(10);

	for (int i = 0; i < s.size(); ++i) {
		s.push(i);
	}

	std::cout << "Lo stack ha dimensione " << s.size() << std::endl;

	for (int i = 0; i < s.size(); ++i) {
		std::cout << s.peek() << std::endl;
		s.pop();
	}

	return 0;
}
