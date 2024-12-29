#include "Stack.hpp"
#include <iostream>

int main()
{
	/* Stack vuoto */
	Stack e;
	std::cout << e << "Dimensione: " << e.size() << std::endl;
	try {
		e.pop();
	}
	catch (Minimum_size_reached) {
		std::cerr << "Lo stack é vuoto!" << std::endl;
	}

	/* Stack pieno */
	Stack u(1, 1);
	std::cout << u << "Dimensione: " << u.size() << std::endl;

	try {
		u.push(7);
	}
	catch (Maximum_size_reached) {
		std::cerr << "Lo stack é pieno!" << std::endl;
	}

	/* Carico e scarico di uno stack */
	Stack s(10);
	for (int i = 0; i < s.size(); ++i) {
		try {
			s.push(i);
		}
		catch (Maximum_size_reached) {
			std::cerr << "Lo stack é pieno!" << std::endl;
		}
	}
	std::cout << s << "Dimensione: " << s.size() << std::endl;
	for (unsigned int i = 0; i < 3; ++i) {
		try {
			s.pop();
		}
		catch (Minimum_size_reached) {
			std::cerr << "Lo stack é vuoto!" << std::endl;
		}
	}
	std::cout << s << "Dimensione: " << s.size() << std::endl;
	for (unsigned int i = 0; i < s.size() - 3; ++i) {
		try {
			s.pop();
		}
		catch (Minimum_size_reached) {
			std::cerr << "Lo stack é vuoto!" << std::endl;
		}
	}
	std::cout << s << "Dimensione: " << s.size() << std::endl;

	/* Carico di uno stack con il medesimo valore mediante costruttore */
	Stack p(5, 100);
	std::cout << p << "Dimensione: " << p.size() << std::endl;

	/* Carico di uno stack con il medesimo valore mediante fill() */
	Stack f(5);
	f.fill(5);
	std::cout << f << "Dimensione: " << f.size() << std::endl;

	/* Costruttore di copia */
	Stack w = p;
	std::cout << w << "Dimensione: " << w.size() << std::endl;

	/* Assegnamento */
	e = p;
	std::cout << e << "Dimensione: " << e.size() << std::endl;

	/* Allocazione impossibile */
	// Stack z(3567587328);

	return 0;
}
