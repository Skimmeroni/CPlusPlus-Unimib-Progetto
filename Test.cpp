#include "Stack.hpp"
#include "Test.h"
#include <iostream>
#include <array>
#include <cassert>
#include <cmath>
#include <string>

void test_for_empty_stack()
{
	std::cout << "*** Manipolazione di uno stack vuoto ***" << std::endl;
	std::cout << std::endl;

	Stack<int> a;
	assert(a.get_size() == 0);
	assert(a.head() == -1);
	std::cout << a;

	try {    // Genera un'eccezione
		a.pop();
	}
	catch (Minimum_size_reached) {
		std::cerr << "Lo stack é vuoto!" << std::endl;
	}

	Stack<std::array<char, 5>> b;
	assert(b.get_size() == 0);
	assert(b.head() == -1);
	// std::cout << b; Non é possibile!

	try {    // Genera un'eccezione
		b.pop();
	}
	catch (Minimum_size_reached) {
		std::cerr << "Lo stack é vuoto!" << std::endl;
	}
}

void test_for_full_stack()
{
	std::cout << "*** Manipolazione di uno stack pieno ***" << std::endl;
	std::cout << std::endl;

	Stack<int> a(3);
	assert(a.get_size() == 3);
	assert(a.head() == -1);
	std::cout << a;

	try {    // NON genera un'eccezione
		a.push(1);
	}
	catch (Maximum_size_reached) {
		std::cerr << "Lo stack é pieno!" << std::endl;
	}
	assert(a.get_size() == 3);
	assert(a.head() == 0);
	std::cout << a;

	try {    // NON genera un'eccezione
		a.push(2);
	}
	catch (Maximum_size_reached) {
		std::cerr << "Lo stack é pieno!" << std::endl;
	}
	assert(a.get_size() == 3);
	assert(a.head() == 1);
	std::cout << a;

	try {    // NON genera un'eccezione
		a.push(3);
	}
	catch (Maximum_size_reached) {
		std::cerr << "Lo stack é pieno!" << std::endl;
	}
	assert(a.get_size() == 3);
	assert(a.head() == 2);
	std::cout << a;

	try {    // Genera un'eccezione
		a.push(4);
	}
	catch (Maximum_size_reached) {
		std::cerr << "Lo stack é pieno!" << std::endl;
	}
	assert(a.get_size() == 3);
	assert(a.head() == 2);
	std::cout << a;
}

void test_for_push_pop()
{
	std::cout << "*** Carico/scarico di uno stack mediante push/pop ***" << std::endl;
	std::cout << std::endl;

	Stack<unsigned int> a(10);
	assert(a.get_size() == 10);
	assert(a.head() == -1);
	std::cout << a;

	for (unsigned int i = 0; i < static_cast<unsigned int>(a.get_size()); ++i) {
		try {    // NON genera un'eccezione
			a.push(i);
		}
		catch (Maximum_size_reached) {
			std::cerr << "Lo stack é pieno!" << std::endl;
		}
	}
	assert(a.get_size() == 10);
	assert(a.head() == 9);
	std::cout << a;

	for (unsigned int i = 0; i < 3; ++i) {
		try {    // NON genera un'eccezione
			a.pop();
		}
		catch (Minimum_size_reached) {
			std::cerr << "Lo stack é vuoto!" << std::endl;
		}
	}
	assert(a.get_size() == 10);
	assert(a.head() == 6);
	std::cout << a;

	for (unsigned int i = 0; i < static_cast<unsigned int>(a.get_size()) - 3; ++i) {
		try {    // NON genera un'eccezione
			a.pop();
		}
		catch (Minimum_size_reached) {
			std::cerr << "Lo stack é vuoto!" << std::endl;
		}
	}
	assert(a.get_size() == 10);
	assert(a.head() == -1);
	std::cout << a;

	for (unsigned int i = 0; i < 2; ++i) {
		try {    // NON genera un'eccezione
			a.push(i);
		}
		catch (Maximum_size_reached) {
			std::cerr << "Lo stack é pieno!" << std::endl;
		}
	}
	assert(a.get_size() == 10);
	assert(a.head() == 1);
	std::cout << a;

	for (unsigned int i = 2; i < 6; ++i) {
		try {    // NON genera un'eccezione
			a.push(i);
		}
		catch (Maximum_size_reached) {
			std::cerr << "Lo stack é pieno!" << std::endl;
		}
	}
	assert(a.get_size() == 10);
	assert(a.head() == 5);
	std::cout << a;
}

void test_for_clear()
{
	std::cout << "*** Svuotamento di uno stack ***" << std::endl;
	std::cout << std::endl;

	Stack<unsigned int> a(5);
	for (unsigned int i = 0; i < static_cast<unsigned int>(a.get_size()); ++i) {
		try {    // NON genera un'eccezione
			a.push(100);
		}
		catch (Maximum_size_reached) {
			std::cerr << "Lo stack é pieno!" << std::endl;
		}
	}
	assert(a.get_size() == 5);
	assert(a.head() == 4);
	std::cout << a;

	Stack<unsigned int>::const_iterator a_s = a.begin();
	Stack<unsigned int>::const_iterator a_e = a.end();

	while (a_s != a_e) {
		assert(*a_s == 100);
		a_s++;
	}

	a.clear();
	assert(a.get_size() == 5);
	assert(a.head() == -1);
	std::cout << a;
}

void test_for_copy_constructor()
{
	/* Costruttore di copia */
	Stack<int> a(9);
	unsigned int s = static_cast<unsigned int>(a.get_size());
	for (unsigned int i = 0; i < s; ++i) {
		try {
			a.push(81);
		}
		catch (Maximum_size_reached) {
			std::cerr << "Lo stack é pieno!" << std::endl;
		}
	}
	Stack<int> b = a;
	std::cout << b << "Dimensione: " << b.get_size() << std::endl;
}

void test_for_assignment()
{
	/* Assegnamento */
	Stack<int> a(12);
	unsigned int s = static_cast<unsigned int>(a.get_size());
	for (unsigned int i = 0; i < s; ++i) {
		try {
			a.push(0);
		}
		catch (Maximum_size_reached) {
			std::cerr << "Lo stack é pieno!" << std::endl;
		}
	}
	Stack<int> b;
	b = a;
	std::cout << b << "Dimensione: " << b.get_size() << std::endl;
}

void test_for_filter_out()
{
	/* Filtering */
	struct Comparison1 {
		bool operator()(unsigned int n) const {
			return n > 3;
		}
	};

	struct Comparison2 {
		bool operator()(unsigned int n) const {
			return (n % 2) == 0;
		}
	};

	struct Comparison3 {
		bool operator()(unsigned int n) const {
			return n > 100;
		}
	};

	Stack<unsigned int> a(10);
	unsigned int s = static_cast<unsigned int>(a.get_size());
	for (unsigned int i = 0; i < s; ++i) {
		try {
			a.push(i);
		}
		catch (Maximum_size_reached) {
			std::cerr << "Lo stack é pieno!" << std::endl;
		}
	}
	std::cout << a << "Dimensione: " << a.get_size() << std::endl;

	Comparison1 comp1;
	Stack<unsigned int> b = a.filter_out<Comparison1>(comp1);
	std::cout << b << "Dimensione: " << b.get_size() << std::endl;

	Comparison2 comp2;
	Stack<unsigned int> c = a.filter_out<Comparison2>(comp2);
	std::cout << c << "Dimensione: " << c.get_size() << std::endl;

	Comparison3 comp3;
	Stack<unsigned int> d = a.filter_out<Comparison3>(comp3);
	std::cout << d << "Dimensione: " << d.get_size() << std::endl;
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

	Stack<int> a(5);
	unsigned int s = static_cast<unsigned int>(a.get_size());
	for (unsigned int i = 0; i < s; ++i) {
		try {
			a.push(100);
		}
		catch (Maximum_size_reached) {
			std::cerr << "Lo stack é pieno!" << std::endl;
		}
	}
	std::cout << a << "Dimensione: " << a.get_size() << std::endl;
	Modifier1 mod1;
	transform<int, Modifier1>(a, mod1);
	std::cout << a << "Dimensione: " << a.get_size() << std::endl;

	Stack<int> b(5);
	b.push(100);
	b.push(200);
	b.push(300);
	b.push(400);
	b.push(500);
	std::cout << b << "Dimensione: " << b.get_size() << std::endl;
	Modifier2 mod2;
	transform<int, Modifier2>(b, mod2);
	std::cout << b << "Dimensione: " << b.get_size() << std::endl;
}

void test_for_loading_through_iterators()
{
	/* Caricamento mediante coppia di iteratori */
    std::array<int, 5> arr = {10, 20, 30, 40, 50};
	std::array<int, 5>::iterator it1 = arr.begin();
	std::array<int, 5>::iterator it2 = arr.end();

	Stack<int> a(10);
	a.load<std::array<int, 5>::iterator>(it1, it2);
	std::cout << a << "Dimensione: " << a.get_size() << std::endl;
	a.load<std::array<int, 5>::iterator>(it1, it2);
	std::cout << a << "Dimensione: " << a.get_size() << std::endl;
	try {
		a.load<std::array<int, 5>::iterator>(it1, it2);
	}
	catch (Maximum_size_reached) {
		std::cerr << "Lo stack é pieno!" << std::endl;
	}

	a.set_size(15);
	std::cout << a;
	try {
		a.load<std::array<int, 5>::iterator>(it1, it2);
	}
	catch (Maximum_size_reached) {
		std::cerr << "Lo stack é pieno!" << std::endl;
	}
	std::cout << a;
	try {
		a.set_size(14);
	}
	catch (Maximum_size_reached) {
		std::cerr << "Lo stack é pieno!" << std::endl;
	}

	a.clear();
	std::cout << a;
	try {
		a.load<std::array<int, 5>::iterator>(it1, it2);
	}
	catch (Maximum_size_reached) {
		std::cerr << "Lo stack é pieno!" << std::endl;
	}
	std::cout << a;

	a.clear();
	a.load<std::array<int, 5>::iterator>(it1, it1);
	std::cout << a << "Dimensione: " << a.get_size() << std::endl;

	a.clear();
	a.load<std::array<int, 5>::iterator>(it2, it2);
	std::cout << a << "Dimensione: " << a.get_size() << std::endl;

	int arrr[5] = {10, 20, 30, 40, 50};
	int* itt1 = &arrr[0];
	int* itt2 = &arrr[4];
	Stack<int> b(itt1, itt2);
	std::cout << b << "Dimensione: " << b.get_size() << std::endl;

	b.clear();
	b.load<std::array<int, 5>::iterator>(itt1, itt1);
	std::cout << b << "Dimensione: " << b.get_size() << std::endl;

	b.clear();
	b.load<std::array<int, 5>::iterator>(itt1, itt2);
	std::cout << b << "Dimensione: " << b.get_size() << std::endl;
}

void test_for_iterators()
{
	/* Iteratori della classe */
	Stack<int> a(6);
	unsigned int s = static_cast<unsigned int>(a.get_size());
	for (unsigned int i = 0; i < s; ++i) {
		try {
			a.push(85 + i);
		}
		catch (Maximum_size_reached) {
			std::cerr << "Lo stack é pieno!" << std::endl;
		}
	}
	Stack<int>::iterator itb = a.begin();
	*itb = 0;
	Stack<int>::iterator ite = a.end();
	while (itb != ite) {
		std::cout << *itb << std::endl;
		itb++;
	}

	std::cout << std::endl;

	Stack<int>::const_iterator c_itb = a.begin();
	// *c_itb = 1;  Non é possibile!
	Stack<int>::const_iterator c_ite = a.end();
	while (c_itb != c_ite) {
		std::cout << *c_itb << std::endl;
		c_itb++;
	}
}

void test_for_fancy_types()
{
	/* Datatype particolarmente convoluti */
	enum Color {Red, Green, Blue};

	struct Comparison {
		bool operator()(int n) const {
			return n > 0;
		}
	};

	struct Person {
		char* Name;
		unsigned int age;
		bool is_married;
		Person* best_friend;
	};

	Stack<double> a1(10);
	Stack<long double> a2(10);
	Stack<long long int> a3(10);
	Stack<unsigned long int> a4(10);
	Stack<unsigned char> a5(10);
	Stack<int*> a6(10);
	Stack<int**> a7(10);
	Stack<bool***> a8(10);
	Stack<char> a9(10);
	Stack<char*> a10(10);
	Stack<std::string> a11(10);
	Stack<std::array<int, 5>> a12(10);
	Stack<std::array<std::array<int, 5>, 5>> a13(10);
	Stack<Stack<int>> a14(10);
	Stack<std::array<Stack<std::array<int, 5>>, 5>> a15(10);
	Stack<Color> a16(10);
	Stack<Comparison> a17(10);
	Stack<Person> a18(10);

	std::array<std::array<int, 3>, 3> a = std::array<std::array<int, 3>, 3>();

	auto it1 = &a[0];
	auto it2 = &a[2];
	Stack<std::array<int, 3>> b(it1, it2);
	b.pop();
	b.push(std::array<int, 3>());
	// std::cout << b << "Dimensione: " << b.get_size() << std::endl;
 }

void test_square_brackets()
{
	Stack<unsigned int> a(5);
	for (unsigned int i = 0; i < static_cast<unsigned int>(a.get_size()); ++i) {
		try {    // NON genera un'eccezione
			a.push(100);
		}
		catch (Maximum_size_reached) {
			std::cerr << "Lo stack é pieno!" << std::endl;
		}
	}
	assert(a.get_size() == 5);
	assert(a.head() == 4);
	std::cout << a;

	try {
		std::cout << a[0] << std::endl;
	}
	catch (Item_out_of_bounds) {
		std::cerr << "L'elemento non esiste!" << std::endl;
	}

	try {
		std::cout << a[5] << std::endl;
	}
	catch (Item_out_of_bounds) {
		std::cerr << "L'elemento non esiste!" << std::endl;
	}

	try {
		std::cout << a[-1] << std::endl;
	}
	catch (Item_out_of_bounds) {
		std::cerr << "L'elemento non esiste!" << std::endl;
	}

	a.wipe();
	try {
		std::cout << a[10] << std::endl;
	}
	catch (Item_out_of_bounds) {
		std::cerr << "L'elemento non esiste!" << std::endl;
	}
}
