#include "Stack.hpp"
#include <iostream>
#include <cmath>
#include <array>

void test_for_empty_stack()
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
}

void test_for_full_stack()
{
	/* Stack pieno */
	Stack a(1, 1);
	std::cout << a << "Dimensione: " << a.size() << std::endl;

	try {
		a.push(7);
	}
	catch (Maximum_size_reached) {
		std::cerr << "Lo stack é pieno!" << std::endl;
	}
}

void test_for_push_pop()
{
	/* Carico e scarico di uno stack */
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
	for (unsigned int i = 0; i < 3; ++i) {
		try {
			a.pop();
		}
		catch (Minimum_size_reached) {
			std::cerr << "Lo stack é vuoto!" << std::endl;
		}
	}
	std::cout << a << "Dimensione: " << a.size() << std::endl;
	for (unsigned int i = 0; i < a.size() - 3; ++i) {
		try {
			a.pop();
		}
		catch (Minimum_size_reached) {
			std::cerr << "Lo stack é vuoto!" << std::endl;
		}
	}
	std::cout << a << "Dimensione: " << a.size() << std::endl;
}

void test_for_clear()
{
	/* Carico di uno stack con il medesimo valore mediante costruttore */
	Stack a(5, 100);
	std::cout << a << "Dimensione: " << a.size() << std::endl;
	a.clear();
	std::cout << a << "Dimensione: " << a.size() << std::endl;
}

void test_for_fill()
{
	/* Carico di uno stack con il medesimo valore mediante fill() */
	Stack a(5);
	a.fill(5);
	std::cout << a << "Dimensione: " << a.size() << std::endl;
}

void test_for_copy_constructor()
{
	/* Costruttore di copia */
	Stack a(9, 81);
	Stack b = a;
	std::cout << b << "Dimensione: " << b.size() << std::endl;
}

void test_for_assignment()
{
	/* Assegnamento */
	Stack a(12, 0);
	Stack b;
	b = a;
	std::cout << b << "Dimensione: " << b.size() << std::endl;
}

void test_for_filter_out()
{
	/* Filtering */
	struct Comparison1 {
		bool operator()(int n) const {
			return n > 3;
		}
	};

	struct Comparison2 {
		bool operator()(int n) const {
			return (n % 2) == 0;
		}
	};

	struct Comparison3 {
		bool operator()(int n) const {
			return n > 100;
		}
	};

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

	Comparison1 comp1;
	Stack b = a.filter_out<Comparison1>(comp1);
	std::cout << b << "Dimensione: " << b.size() << std::endl;

	Comparison2 comp2;
	Stack c = a.filter_out<Comparison2>(comp2);
	std::cout << c << "Dimensione: " << c.size() << std::endl;

	Comparison3 comp3;
	Stack d = a.filter_out<Comparison3>(comp3);
	std::cout << d << "Dimensione: " << d.size() << std::endl;
}

void test_for_transform()
{
	/* Trasformazione */
	struct Modifier1 {
		int operator()(int n) const {
			return n + 1;
		}
	};

	struct Modifier2 {
		int operator()(int n) const {
			return static_cast<int>(sqrt(n));
		}
	};

	Stack a(5, 100);
	std::cout << a << "Dimensione: " << a.size() << std::endl;
	Modifier1 mod1;
	transform<Modifier1>(a, mod1);
	std::cout << a << "Dimensione: " << a.size() << std::endl;

	Stack b(5);
	b.push(100);
	b.push(200);
	b.push(300);
	b.push(400);
	b.push(500);
	std::cout << b << "Dimensione: " << b.size() << std::endl;
	Modifier2 mod2;
	transform<Modifier2>(b, mod2);
	std::cout << b << "Dimensione: " << b.size() << std::endl;
}

void test_for_loading_through_iterators()
{
	/* Caricamento mediante coppia di iteratori */
    std::array<int, 5> arr = {10, 20, 30, 40, 50};
	std::array<int, 5>::iterator it1 = arr.begin();
	std::array<int, 5>::iterator it2 = arr.end();

	Stack a(5, 5);
	a.load(it1, it2);
	std::cout << a << "Dimensione: " << a.size() << std::endl;

	a.load(it1, it1);
	std::cout << a << "Dimensione: " << a.size() << std::endl;

	a.load(it2, it2);
	std::cout << a << "Dimensione: " << a.size() << std::endl;

	int arrr[5] = {10, 20, 30, 40, 50};
	int* itt1 = &arrr[0];
	int* itt2 = &arrr[4];
	Stack b(itt1, itt2);
	std::cout << b << "Dimensione: " << b.size() << std::endl;

	b.load(itt1, itt1);
	std::cout << b << "Dimensione: " << b.size() << std::endl;

	b.load(itt1, itt2);
	std::cout << b << "Dimensione: " << b.size() << std::endl;
}

void test_for_iterators()
{
	/* Iteratori della classe */
	Stack a(5);
	a.push(85);
	a.push(86);
	a.push(87);
	a.push(88);
	a.push(89);
	Stack::iterator itb = a.begin();
	Stack::iterator ite = a.end();
	while (itb != ite) {
		std::cout << *itb << std::endl;
		itb++;
	}
}

int main()
{
	test_for_empty_stack();
	std::cout << std::endl;
	test_for_full_stack();
	std::cout << std::endl;
	test_for_push_pop();
	std::cout << std::endl;
	test_for_clear();
	std::cout << std::endl;
	test_for_fill();
	std::cout << std::endl;
	test_for_copy_constructor();
	std::cout << std::endl;
	test_for_assignment();
	std::cout << std::endl;
	test_for_filter_out();
	std::cout << std::endl;
	test_for_transform();
	std::cout << std::endl;
	test_for_loading_through_iterators();
	std::cout << std::endl;
	test_for_iterators();

	/* Allocazione impossibile */
	// Stack z(3567587328);

	return 0;
}
