#include "Stack.hpp"
#include <iostream>

int main()
{
	Stack s(10);
	Stack e;
	Stack u(1);

	for (int i = 0; i < s.size(); ++i) {
		s.push(i);
	}
	u.push(7);

	std::cout << s << "Dimensione: " << s.size() << std::endl;
	std::cout << e << "Dimensione: " << e.size() << std::endl;
	std::cout << u << "Dimensione: " << u.size() << std::endl;

	try {
		// u.push(7);
	}
	catch (Maximum_size_reached) {
		std::cerr << "Lo stack é pieno!" << std::endl;
	}

	try {
		e.pop();
	}
	catch (Minimum_size_reached) {
		std::cerr << "Lo stack é vuoto!" << std::endl;
	}

	return 0;
}
