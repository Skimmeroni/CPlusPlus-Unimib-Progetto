#include "Stack.hpp"
#include <iostream>
#include <cmath>
#include <array>
#include <string>

void test_for_empty_stack()
{
	/* Stack<int> vuoto */
	Stack<int> a;
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
	/* Stack<int> pieno */
	Stack<int> a(1);
	a.push(1);
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
	Stack<unsigned int> a(10);
	unsigned int s = static_cast<unsigned int>(a.size());
	for (unsigned int i = 0; i < s; ++i) {
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
	s = static_cast<unsigned int>(a.size());
	for (unsigned int i = 0; i < s - 3; ++i) {
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
	Stack<int> a(5);
	unsigned int s = static_cast<unsigned int>(a.size());
	for (unsigned int i = 0; i < s; ++i) {
		try {
			a.push(100);
		}
		catch (Maximum_size_reached) {
			std::cerr << "Lo stack é pieno!" << std::endl;
		}
	}
	std::cout << a << "Dimensione: " << a.size() << std::endl;
	a.clear();
	std::cout << a << "Dimensione: " << a.size() << std::endl;
}

void test_for_copy_constructor()
{
	/* Costruttore di copia */
	Stack<int> a(9);
	unsigned int s = static_cast<unsigned int>(a.size());
	for (unsigned int i = 0; i < s; ++i) {
		try {
			a.push(81);
		}
		catch (Maximum_size_reached) {
			std::cerr << "Lo stack é pieno!" << std::endl;
		}
	}
	Stack<int> b = a;
	std::cout << b << "Dimensione: " << b.size() << std::endl;
}

void test_for_assignment()
{
	/* Assegnamento */
	Stack<int> a(12);
	unsigned int s = static_cast<unsigned int>(a.size());
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
	std::cout << b << "Dimensione: " << b.size() << std::endl;
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
	unsigned int s = static_cast<unsigned int>(a.size());
	for (unsigned int i = 0; i < s; ++i) {
		try {
			a.push(i);
		}
		catch (Maximum_size_reached) {
			std::cerr << "Lo stack é pieno!" << std::endl;
		}
	}
	std::cout << a << "Dimensione: " << a.size() << std::endl;

	Comparison1 comp1;
	Stack<unsigned int> b = a.filter_out<Comparison1>(comp1);
	std::cout << b << "Dimensione: " << b.size() << std::endl;

	Comparison2 comp2;
	Stack<unsigned int> c = a.filter_out<Comparison2>(comp2);
	std::cout << c << "Dimensione: " << c.size() << std::endl;

	Comparison3 comp3;
	Stack<unsigned int> d = a.filter_out<Comparison3>(comp3);
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

	Stack<int> a(5);
	unsigned int s = static_cast<unsigned int>(a.size());
	for (unsigned int i = 0; i < s; ++i) {
		try {
			a.push(100);
		}
		catch (Maximum_size_reached) {
			std::cerr << "Lo stack é pieno!" << std::endl;
		}
	}
	std::cout << a << "Dimensione: " << a.size() << std::endl;
	Modifier1 mod1;
	transform<int, Modifier1>(a, mod1);
	std::cout << a << "Dimensione: " << a.size() << std::endl;

	Stack<int> b(5);
	b.push(100);
	b.push(200);
	b.push(300);
	b.push(400);
	b.push(500);
	std::cout << b << "Dimensione: " << b.size() << std::endl;
	Modifier2 mod2;
	transform<int, Modifier2>(b, mod2);
	std::cout << b << "Dimensione: " << b.size() << std::endl;
}

void test_for_loading_through_iterators()
{
	/* Caricamento mediante coppia di iteratori */
    std::array<int, 5> arr = {10, 20, 30, 40, 50};
	std::array<int, 5>::iterator it1 = arr.begin();
	std::array<int, 5>::iterator it2 = arr.end();

	Stack<int> a(5);
	a.load<std::array<int, 5>::iterator>(it1, it2);
	std::cout << a << "Dimensione: " << a.size() << std::endl;

	a.clear();
	a.load<std::array<int, 5>::iterator>(it1, it1);
	std::cout << a << "Dimensione: " << a.size() << std::endl;

	a.clear();
	a.load<std::array<int, 5>::iterator>(it2, it2);
	std::cout << a << "Dimensione: " << a.size() << std::endl;

	int arrr[5] = {10, 20, 30, 40, 50};
	int* itt1 = &arrr[0];
	int* itt2 = &arrr[4];
	Stack<int> b(itt1, itt2);
	std::cout << b << "Dimensione: " << b.size() << std::endl;

	b.clear();
	b.load<std::array<int, 5>::iterator>(itt1, itt1);
	std::cout << b << "Dimensione: " << b.size() << std::endl;

	b.clear();
	b.load<std::array<int, 5>::iterator>(itt1, itt2);
	std::cout << b << "Dimensione: " << b.size() << std::endl;
}

void test_for_iterators()
{
	/* Iteratori della classe */
	Stack<int> a(6);
	unsigned int s = static_cast<unsigned int>(a.size());
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
	// std::cout << b << "Dimensione: " << b.size() << std::endl;
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
	std::cout << std::endl;
	test_for_fancy_types();

	/* Allocazione impossibile */
	// Stack<int> z(3567587328);
	return 0;
}
