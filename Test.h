/**
	@file Test.h

	@brief File header dei test per il progetto

	File di dichiarazioni dei test per il progetto, contenente
	strutture dati e firme di funzioni
*/

#ifndef _TEST_H
#define _TEST_H

#include <cmath>
#include <iostream>

/**
	Struttura che rappresenta una persona, usata per i test
*/

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

/**
	Ridefinizione dell'operatore << per un oggetto Person
*/

std::ostream& operator<<(std::ostream& os, const Person& u);

/**
	Funtori pensati per tipi di dato interi
*/

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

struct Modifier1 {
	int operator()(int n) const {
		return static_cast<int>(sqrt(n));
	}
};

/**
	Funtori pensati per oggetti Person
*/

struct Comparison3 {
	bool operator()(Person p) const {
		return p.is_happy;
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

/**
	Test di manipolazione di uno stack vuoto
*/

void test_for_empty_stack();

/**
	Test di manipolazione di uno stack pieno
*/

void test_for_full_stack();

/**
	Test di carico e scarico di uno stack
*/

void test_for_push_pop();

/**
	Test di svuotamento dello stack
*/

void test_for_clear();

/**
	Test sul copy constructor
*/

void test_for_copy_constructor();

/**
	Test sull'assegnamento
*/

void test_for_assignment();

/**
	Test sul metodo di classe filter_out
*/

void test_for_filter_out();

/**
	Test sulla funzione pubblica transform
*/

void test_for_transform();

/**
	Test sul riempimento di uno stack mediante iteratori
*/

void test_for_loading_through_iterators();

/**
	Test sugli iteratori offerti dalla classe
*/

void test_for_iterators();

#endif
