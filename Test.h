#ifndef _TEST_H
#define _TEST_H

#include <cmath>
#include <iostream>

enum Color {Red, Green, Blue};

struct Person {
	char* Name;
	unsigned int age;
	bool is_married;
	Person* best_friend;
};

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
	bool operator()(unsigned int n) const {
		return n > 100;
	}
};

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
void test_for_fancy_types();
void test_square_brackets();

#endif
