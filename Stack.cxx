#include "Stack.hpp"
#include <iostream>
#include <cmath>
#include <array>

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
	Stack a;
	std::cout << a << "Dimensione: " << a.size() << std::endl;
	try {
		a.pop();
	}
	catch (Minimum_size_reached) {
		std::cerr << "Lo stack é vuoto!" << std::endl;
	}

	/* Stack pieno */
	Stack b(1, 1);
	std::cout << b << "Dimensione: " << b.size() << std::endl;

	try {
		b.push(7);
	}
	catch (Maximum_size_reached) {
		std::cerr << "Lo stack é pieno!" << std::endl;
	}

	/* Carico e scarico di uno stack */
	Stack c(10);
	for (int i = 0; i < c.size(); ++i) {
		try {
			c.push(i);
		}
		catch (Maximum_size_reached) {
			std::cerr << "Lo stack é pieno!" << std::endl;
		}
	}
	std::cout << c << "Dimensione: " << c.size() << std::endl;
	for (unsigned int i = 0; i < 3; ++i) {
		try {
			c.pop();
		}
		catch (Minimum_size_reached) {
			std::cerr << "Lo stack é vuoto!" << std::endl;
		}
	}
	std::cout << c << "Dimensione: " << c.size() << std::endl;
	for (unsigned int i = 0; i < c.size() - 3; ++i) {
		try {
			c.pop();
		}
		catch (Minimum_size_reached) {
			std::cerr << "Lo stack é vuoto!" << std::endl;
		}
	}
	std::cout << c << "Dimensione: " << c.size() << std::endl;

	/* Carico di uno stack con il medesimo valore mediante costruttore */
	Stack d(5, 100);
	std::cout << d << "Dimensione: " << d.size() << std::endl;
	d.clear();
	std::cout << d << "Dimensione: " << d.size() << std::endl;

	/* Carico di uno stack con il medesimo valore mediante fill() */
	Stack e(5);
	e.fill(5);
	std::cout << e << "Dimensione: " << e.size() << std::endl;

	/* Costruttore di copia */
	Stack f = d;
	std::cout << f << "Dimensione: " << f.size() << std::endl;

	/* Assegnamento */
	Stack g;
	g = d;
	std::cout << g << "Dimensione: " << g.size() << std::endl;

	/* Filtering */
	Stack h(10);
	for (int i = 0; i < h.size(); ++i) {
		try {
			h.push(i);
		}
		catch (Maximum_size_reached) {
			std::cerr << "Lo stack é pieno!" << std::endl;
		}
	}
	std::cout << h << "Dimensione: " << h.size() << std::endl;

	Comparison1 C1;
	Stack j1 = h.filter_out<Comparison1>(C1);
	std::cout << j1 << "Dimensione: " << j1.size() << std::endl;

	Comparison2 C2;
	Stack j2 = h.filter_out<Comparison2>(C2);
	std::cout << j2 << "Dimensione: " << j2.size() << std::endl;

	Comparison3 C3;
	Stack j3 = h.filter_out<Comparison3>(C3);
	std::cout << j3 << "Dimensione: " << j3.size() << std::endl;

	/* Trasformazione */
	Stack k(5, 100);
	std::cout << k << "Dimensione: " << k.size() << std::endl;
	Modifier1 M1;
	transform<Modifier1>(k, M1);
	std::cout << k << "Dimensione: " << k.size() << std::endl;

	Stack l(5);
	l.push(100);
	l.push(200);
	l.push(300);
	l.push(400);
	l.push(500);
	std::cout << l << "Dimensione: " << l.size() << std::endl;
	Modifier2 M2;
	transform<Modifier2>(l, M2);
	std::cout << l << "Dimensione: " << l.size() << std::endl;

	/* Caricamento mediante coppia di iteratori */

    std::array<int, 5> arr = {10, 20, 30, 40, 50};
	std::array<int, 5>::iterator it1 = arr.begin();
	std::array<int, 5>::iterator it2 = arr.end();

	Stack m(5, 5);
	m.load(it1, it2);
	std::cout << m << "Dimensione: " << m.size() << std::endl;

	m.load(it1, it1);
	std::cout << m << "Dimensione: " << m.size() << std::endl;

	m.load(it2, it2);
	std::cout << m << "Dimensione: " << m.size() << std::endl;

	int arrr[5] = {10, 20, 30, 40, 50};
	int* itt1 = &arrr[0];
	int* itt2 = &arrr[4];
	Stack n(itt1, itt2);
	std::cout << n << "Dimensione: " << n.size() << std::endl;

	n.load(itt1, itt1);
	std::cout << n << "Dimensione: " << n.size() << std::endl;

	n.load(itt1, itt2);
	std::cout << n << "Dimensione: " << n.size() << std::endl;

	/* Allocazione impossibile */
	// Stack z(3567587328);

	return 0;
}
