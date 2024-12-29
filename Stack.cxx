#include "Stack.hpp"
#include <iostream>
#include <cmath>

struct Comparison1 {
	bool operator()(int a) const {
		return a > 3;
	}
};

struct Comparison2 {
	bool operator()(int a) const {
		return (a % 2) == 0;
	}
};

struct Comparison3 {
	bool operator()(int a) const {
		return a > 100;
	}
};

struct Modifier1 {
	int operator()(int a) const {
		return a + 1;
	}
};

struct Modifier2 {
	int operator()(int a) const {
		return static_cast<int>(sqrt(a));
	}
};

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
	p.clear();
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

	/* Filtering */
	Stack a(10);
	for (int i = 0; i < a.size(); ++i) {
		try {
			a.push(i);
		}
		catch (Maximum_size_reached) {
			std::cerr << "Lo stack é pieno!" << std::endl;
		}
	}
	std::cout << a << "Dimensione: " << a.size() << std::endl;

	Comparison1 C1;
	Stack a1 = a.filter_out<Comparison1>(C1);
	std::cout << a1 << "Dimensione: " << a1.size() << std::endl;

	Comparison2 C2;
	Stack a2 = a.filter_out<Comparison2>(C2);
	std::cout << a2 << "Dimensione: " << a2.size() << std::endl;

	Comparison3 C3;
	Stack a3 = a.filter_out<Comparison3>(C3);
	std::cout << a3 << "Dimensione: " << a3.size() << std::endl;

	/* Trasformazione */
	Stack g(5, 100);
	std::cout << g << "Dimensione: " << g.size() << std::endl;
	Modifier1 M1;
	transform<Modifier1>(g, M1);
	std::cout << g << "Dimensione: " << g.size() << std::endl;

	Stack h(5);
	h.push(100);
	h.push(200);
	h.push(300);
	h.push(400);
	h.push(500);
	std::cout << h << "Dimensione: " << h.size() << std::endl;
	Modifier2 M2;
	transform<Modifier2>(h, M2);
	std::cout << h << "Dimensione: " << h.size() << std::endl;

	/* Allocazione impossibile */
	// Stack z(3567587328);

	return 0;
}
