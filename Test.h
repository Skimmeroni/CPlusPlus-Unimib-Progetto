#ifndef _TEST_H
#define _TEST_H

#include <cmath>
#include <iostream>
#include <string>

enum Color {Red, Green, Blue};

struct Person {
	std::string name;
	std::string surname;
	unsigned int age;
	bool is_happy;

	Person();
	Person(const std::string& name, const std::string& surname,
	       const int& age, const bool& is_happy);
	~Person();
	Person(const Person& other);

	void swap(Person& other)
	{
		std::swap(this->name, other.name);
		std::swap(this->surname, other.surname);
		std::swap(this->age, other.age);
		std::swap(this->is_happy, other.is_happy);
	}

	Person& operator=(const Person& other)
	{
		if (this != &other) {
			Person temp(other);
			this->swap(temp);
		}

		return *this;
	}
};

std::ostream& operator<<(std::ostream& os, const Person& u);

struct Comparison {
	bool operator()(int n) const {
		return n > 0;
	}
};

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
	bool operator()(Person p) const {
		return p.is_happy;
	}
};

struct Modifier1 {
	int operator()(int n) const {
		return static_cast<int>(sqrt(n));
	}
};

struct Modifier2 {
	Person operator()(Person p) const {
		Person hexed(p);
		hexed.name[0] = '?';
		hexed.surname[0] = '?';
		hexed.age *= 3;
		hexed.is_happy = false;

		return hexed;
	}
};

void test_for_empty_stack();
void test_for_full_stack();
void test_for_push_pop();
void test_for_clear();
void test_for_copy_constructor();
void test_for_assignment();
void test_for_filter_out();
void test_for_transform();
void test_for_loading_through_iterators();
void test_for_iterators();
void test_square_brackets();

#endif
