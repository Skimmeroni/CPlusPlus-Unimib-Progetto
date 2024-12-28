#include "Stack.hpp"
#include <iostream>
// #include <limits>

int main()
{
	Stack s(10);
	Stack p(5, 100);
	Stack f(5);
	Stack e;
	Stack u(1);

	for (int i = 0; i < s.size(); ++i) {
		s.push(i);
	}

	u.push(7);
	f.fill(5);

	std::cout << s << "Dimensione: " << s.size() << std::endl;
	std::cout << p << "Dimensione: " << p.size() << std::endl;
	std::cout << f << "Dimensione: " << f.size() << std::endl;
	std::cout << e << "Dimensione: " << e.size() << std::endl;
	std::cout << u << "Dimensione: " << u.size() << std::endl;

	try {
		u.push(7);
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

	// Stack z((std::size_t)~0);

	return 0;
}
