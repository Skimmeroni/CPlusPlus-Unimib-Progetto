#include "Stack.hpp"
#include "Test.h"
#include <array>

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
	std::cout << "*** Caricamento mediante coppia di iteratori ***" << std::endl;
	std::cout << std::endl;

	std::array<int, 5> arr = {10, 20, 30, 40, 50};
	Stack<int> a(10);

	a.load<std::array<int, 5>::iterator>(arr.begin(), arr.end());
	std::cout << a;

	a.load<std::array<int, 5>::iterator>(arr.begin(), arr.begin());
	std::cout << a;

	a.load<std::array<int, 5>::iterator>(arr.end(), arr.end());
	std::cout << a;

	int arrr[5] = {10, 20, 30, 40, 50};
	Stack<int> b(arrr, arrr + 5);
	std::cout << b;

	b.load<std::array<int, 5>::iterator>(arrr, arrr);
	std::cout << b;

	b.load<std::array<int, 5>::iterator>(arrr + 5, arrr + 5);
	std::cout << b;

	std::array<Person, 5> People = {Person("Adam", "Amaryllis", 54, true),
																	Person("Bianca", "Bellflower", 23, false),
																	Person("Caleb", "Cantaloupe", 31, true),
																	Person("Diana", "Dahlia", 48, false),
																	Person("Frank", "Fig", 25, true)};
	Stack<Person> c(People.begin(), People.end());
	std::cout << c;

	Stack<int> d;
	try {
		d.load<std::array<int, 5>::iterator>(arr.begin(), arr.end());
	}
	catch (Maximum_size_reached) {
		std::cerr << "Lo stack é pieno!" << std::endl;
	}
}

void test_for_iterators()
{
	std::cout << "*** Iteratori della classe ***" << std::endl;
	std::cout << std::endl;

	Stack<int> a(6);
	for (unsigned int i = 0; i < static_cast<unsigned int>(a.get_size()); ++i) {
			a.push(0 + i);
	}

	Stack<int>::iterator itb = a.begin();
	Stack<int>::iterator ite = a.end();
	while (itb != ite) {
		std::cout << ++(*itb) << " /// ";
		itb++;
	}
	std::cout << std::endl;

	Stack<int>::const_iterator c_itb = a.begin();
	// *c_itb = 1; Non é possibile!
	Stack<int>::const_iterator c_ite = a.end();
	while (c_itb != c_ite) {
		std::cout << *c_itb << " /// ";
		c_itb++;
	}
	std::cout << std::endl;

	Stack<Person> b(10);
	b.push(Person("Angela", "Aloe", 39, true));
	b.push(Person("Brent", "Bluebell", 27, false));
	b.push(Person("Cynthia", "Coriander", 44, true));
	b.push(Person("Damon", "Dogwood", 36, false));

	Stack<Person>::const_iterator c_bitb = b.begin();
	Stack<Person>::const_iterator c_bite = b.end();
	while (c_bitb != c_bite) {
		std::cout << *c_bitb << std::endl;
		c_bitb++;
	}
}
