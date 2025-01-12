#include "Stack.hpp"
#include "Test.h"
#include <iostream>
#include <array>
#include <cassert>
#include <cmath>
#include <string>

Person::Person()
: name(""), surname(""), age(0), is_happy(false)
{}

Person::Person(const std::string& name, const std::string& surname,
               const int& age, const bool& is_happy)
: name(""), surname(""), age(0), is_happy(false)
{
	this->name = name;
	this->surname = surname;
	this->age = age;
	this->is_happy = is_happy;
}

Person::~Person()
{}

Person::Person(const Person& other)
: name(""), surname(""), age(0), is_happy(false)
{
	this->name = other.name;
	this->surname = other.surname;
	this->age = other.age;
	this->is_happy = other.is_happy;
}

std::ostream& operator<<(std::ostream& os, const Person& p)
{
	os << "{" << p.name << ", "
	          << p.surname << ", "
	          << p.age << ", " <<
	          p.is_happy << "}";
  return os;
}

void test_for_empty_stack()
{
	std::cout << "*** Manipolazione di uno stack vuoto ***" << std::endl;
	std::cout << std::endl;

	Stack<int> a;
	assert(a.get_size() == 0);
	assert(a.head() == -1);
	std::cout << a;

	try {    // Genera un'eccezione, va gestita
		a.pop();
	}
	catch (Minimum_size_reached) {
		std::cerr << "Lo stack é vuoto!" << std::endl;
	}

	Stack<Person> b;
	assert(b.get_size() == 0);
	assert(b.head() == -1);

	try {    // Genera un'eccezione, va gestita
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

	a.push(1);	 // NON genera un'eccezione, non serve gestire
	assert(a.get_size() == 3);
	assert(a.head() == 0);
	std::cout << a;

	a.push(2);   // NON genera un'eccezione, non serve gestire
	assert(a.get_size() == 3);
	assert(a.head() == 1);
	std::cout << a;

	a.push(3); // NON genera un'eccezione, non serve gestire
	assert(a.get_size() == 3);
	assert(a.head() == 2);
	std::cout << a;

	try {    // Genera un'eccezione, va gestita
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
		a.push(i);
	}
	assert(a.get_size() == 10);
	assert(a.head() == 9);
	std::cout << a;

	for (unsigned int i = 0; i < 3; ++i) {
		a.pop();
	}
	assert(a.get_size() == 10);
	assert(a.head() == 6);
	std::cout << a;

	for (unsigned int i = 0; i < static_cast<unsigned int>(a.get_size()) - 3; ++i) {
		a.pop();
	}
	assert(a.get_size() == 10);
	assert(a.head() == -1);
	std::cout << a;

	for (unsigned int i = 0; i < 2; ++i) {
			a.push(i);
	}
	assert(a.get_size() == 10);
	assert(a.head() == 1);
	std::cout << a;

	for (unsigned int i = 2; i < 6; ++i) {
			a.push(i);
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
			a.push(100);
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

	Stack<Person> b(5);
	b.push(Person("Alice", "Aspen", 10, true));
	b.push(Person("Bob", "Birch", 20, false));
	b.push(Person("Charlie", "Cedar", 30, true));
	b.push(Person("Daniel", "Dogwood", 40, false));
	b.push(Person("Eliza", "Elm", 50, true));
	assert(b.get_size() == 5);
	assert(b.head() == 4);
	std::cout << b;

	Stack<Person>::const_iterator b_s = b.begin();
	Stack<Person>::const_iterator b_e = b.end();

	b.clear();
	assert(b.get_size() == 5);
	assert(b.head() == -1);
	std::cout << b;
}

void test_for_copy_constructor()
{
	std::cout << "*** Costruttore di copia ***" << std::endl;
	std::cout << std::endl;

	Stack<int> a(9);
	for (unsigned int i = 0; i < static_cast<unsigned int>(a.get_size()); ++i) {
			a.push(81);
	}
	Stack<int> b(a);
	assert(b.get_size() == 9);
	assert(b.head() == 8);
	std::cout << b;

	Stack<Person> c(3);
	c.push(Person("Amelia", "Azalea", 27, true));
	c.push(Person("Brian", "Bloom", 42, false));
	c.push(Person("Charlotte", "Clover", 36, true));
	Stack<Person> d(c);
	assert(d.get_size() == 3);
	assert(d.head() == 2);
	std::cout << d;
}

void test_for_assignment()
{
	std::cout << "*** Operatore di assegnamento ***" << std::endl;
	std::cout << std::endl;

	Stack<int> a(12);
	for (unsigned int i = 0; i < static_cast<unsigned int>(a.get_size()); ++i) {
		a.push(0);
	}
	Stack<int> b;
	b = a;
	std::cout << b;

	Stack<Person> c(4);
	c.push(Person("Andrew", "Aloe", 31, true));
	c.push(Person("Bella", "Blossom", 24, false));
	c.push(Person("Charles", "Cornflower", 47, true));
	c.push(Person("Daisy", "Dandelion", 19, false));
	Stack<Person> d;
	d = c;
	assert(d.get_size() == 4);
	assert(d.head() == 3);
	std::cout << d;
}

void test_for_filter_out()
{
	std::cout << "*** Metodo di filtraggio ***" << std::endl;
	std::cout << std::endl;

	Stack<unsigned int> a(10);
	for (unsigned int i = 0; i < static_cast<unsigned int>(a.get_size()); ++i) {
			a.push(i);
	}
	std::cout << a;

	Comparison1 comp1;
	Stack<unsigned int> b = a.filter_out<Comparison1>(comp1);
	std::cout << b;

	Comparison2 comp2;
	Stack<unsigned int> c = a.filter_out<Comparison2>(comp2);
	std::cout << c;

	Stack<Person> d(5);
	d.push(Person("Alice", "Anemone", 34, true));
	d.push(Person("Bradley", "Bamboo", 40, false));
	d.push(Person("Catherine", "Cypress", 22, true));
	d.push(Person("Dylan", "Delphinium", 60, false));
	d.push(Person("Fiona", "Fern", 18, true));
	std::cout << d;

	Comparison3 comp3;
	d = d.filter_out<Comparison3>(comp3);
	std::cout << d;
}

void test_for_transform()
{
	std::cout << "*** Metodo di trasformazione ***" << std::endl;
	std::cout << std::endl;

	Stack<int> a(5);
	a.push(100);
	a.push(200);
	a.push(300);
	a.push(400);
	a.push(500);
	std::cout << a;
	Modifier1 mod1;
	transform<int, Modifier1>(a, mod1);
	std::cout << a;

	Stack<Person> b(5);
	b.push(Person("Ava", "Aster", 26, true));
	b.push(Person("Brandon", "Basil", 37, false));
	b.push(Person("Clara", "Chrysanthemum", 45, true));
	b.push(Person("Derek", "Daisy", 29, false));
	b.push(Person("Emily", "Eucalyptus", 33, true));
	std::cout << b;
	Modifier2 mod2;
	transform<Person, Modifier2>(b, mod2);
	std::cout << b;
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
}

void test_square_brackets() {}
