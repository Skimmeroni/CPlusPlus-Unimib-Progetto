/**
	@file Main.cpp

	@brief File principale del progetto

	File principale del progetto, che chiama
	tutte le funzioni di test
*/
#include "Test.h"

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
	return 0;
}
