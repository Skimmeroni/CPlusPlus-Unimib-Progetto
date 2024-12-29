/**
	@file Stack.hpp

	@brief File header della classe Stack

	File di dichiarazioni della classe Stack
*/

#ifndef _STACK_HPP
#define _STACK_HPP

#include <iostream>
#include <algorithm>

struct Maximum_size_reached {};
struct Minimum_size_reached {};

/**
	@brief Classe Stack

	Classe che implementa la struttura dati stack, utilizzando un array
	statico di dimensione fissata
*/
class Stack {
	friend std::ostream& operator<<(std::ostream& os, const Stack& stack);
	typedef int stack_value;
private:
	stack_value* Items;        // puntatore all'array statico
	int top_pos;               // posizione della cima dello stack
	unsigned int maximum_size; // dimensione (massima) dello stack
public:
	/**
		@brief Costruttore di default

		Costruttore di default, che inizializza lo stack con dimensione
		massima 0, posizione della cima -1 e array statico vuoto.

		Nota: la scelta di far partire la posizione della cima da -1
		permette di mappare le posizioni dell'array direttamente a
		partire da 0.

		@post top_pos == -1
		@post maximum_size == 0
		@post Items = nullptr
	*/
	Stack()
	: top_pos(-1), maximum_size(0), Items(nullptr)
	{
		#ifndef NDEBUG
		std::cout << "Stack::Stack()" << std::endl;
		#endif
	}

	/**
		@brief Costruttore secondario

		Costruttore secondario, che inizializza lo stack con dimensione
		massima della dimensione data e array statico di lunghezza
		pari alla dimensione data

		Nota: l'array non viene riempito con alcun valore di default

		Nota: viene dichiarato explicit per evitare che il compilatore
		lo intenda come un cast implicito

		@param size la dimensione massima dello stack

		@post top_pos == -1
		@post maximum_size == size
		@post Items != nullptr

		@throw std::bad_alloc se l'allocazione della memoria fallisce
	*/
	explicit Stack(const unsigned int& size)
	: top_pos(-1), maximum_size(0), Items(nullptr)
	{
		try {
			Items = new stack_value[size];
		}
		catch (std::bad_alloc) {
			std::cerr << "Allocazione di memoria fallita :(" << std::endl;
		}

		maximum_size = size;

		#ifndef NDEBUG
		std::cout << "Stack::Stack(unsigned int)" << std::endl;
		#endif
	}

	/**
		@brief Costruttore secondario

		Costruttore secondario, che inizializza lo stack con dimensione
		massima della dimensione data, array statico di lunghezza
		pari alla dimensione data e posizione della cima pari alla
		dimensione data. Tutte le celle dello stack vengono riempite
		con il valore dato.

		@param size la dimensione massima dello stack
		@param value il valore con cui riempire lo stack

		@post top_pos == size
		@post maximum_size == size
		@post Items != nullptr

		@throw std::bad_alloc se l'allocazione della memoria fallisce
	*/
	Stack(const unsigned int& size, const stack_value& value)
	: top_pos(-1), maximum_size(0), Items(nullptr)
	{
		try {
			Items = new stack_value[size];
		}
		catch (std::bad_alloc) {
			std::cerr << "Allocazione di memoria fallita :(" << std::endl;
		}

		for (unsigned int i = 0; i < size; ++i) {
			Items[i] = value;
			top_pos++;
		}

		maximum_size = size;

		#ifndef NDEBUG
		std::cout << "Stack::Stack(unsigned int, stack_value)" << std::endl;
		#endif
	}

	/**
		@brief Costruttore di copia

		Costruttore di copia che crea uno stack a partire da uno
		stack giá esistente

		@param other lo stack da usare come riferimento

		@post this->Items == other.Items
		@post this->top_pos == other.top_pos
		@post this->maximum_size == other.maximum_size

		@throw std::bad_alloc se l'allocazione della memoria fallisce
	*/
	Stack(const Stack& other)
	: top_pos(-1), maximum_size(0), Items(nullptr)
	{
		try {
			Items = new stack_value[other.maximum_size];
		}
		catch (std::bad_alloc) {
			std::cerr << "Allocazione di memoria fallita :(" << std::endl;
		}

		for (unsigned int i = 0; i < other.maximum_size; ++i) {
			Items[i] = other.Items[i];
			top_pos++;
		}

		maximum_size = other.maximum_size;

		#ifndef NDEBUG
		std::cout << "Stack::Stack(const Stack&)" << std::endl;
		#endif
	}

	/**
		@brief Distruttore

		Distruttore che dealloca tutte le risorse allocate dall'oggetto

		@post top_pos == -1
		@post maximum_size == 0
		@post Items == nullptr
	*/
	~Stack()
	{
		delete[] Items;
		maximum_size = 0;
		top_pos = -1;

		#ifndef NDEBUG
		std::cout << "Stack::~Stack()" << std::endl;
		#endif
	}

	/**
		@brief Push

		Metodo che carica il valore passato sullo stack, se c'é
		ancora spazio disponibile

		@param value il valore da caricare sullo stack

		@post top_pos == top_pos + 1
		@post Items != nullptr

		@throw Maximum_size_reached se lo stack é pieno
	*/
	void push(const stack_value& value)
	{
		if (maximum_size == top_pos + 1) {
			throw Maximum_size_reached();
		} else {
			top_pos++;
			Items[top_pos] = value;
		}
	}

	/**
		@brief Pop

		Metodo che rimuove il valore in cima allo stack e lo restituisce,
		a meno che lo stack sia vuoto

		@return il valore in cima allo stack

		@post top_pos == top_pos - 1
		@post Items != nullptr

		@throw Minimum_size_reached se lo stack é vuoto
	*/
	stack_value pop()
	{
		if (top_pos == -1) {
			throw Minimum_size_reached();
		} else {
			stack_value old_top = Items[top_pos];
			top_pos--;
			return old_top;
		}
	}

	/**
		@brief Peek

		Metodo che restituisce il valore in cima allo stack, a meno che lo
		stack sia vuoto

		@return il valore in cima allo stack

		@post top_pos == top_pos - 1
		@post Items != nullptr

		@throw Minimum_size_reached se lo stack é vuoto
	*/
	stack_value peek() const
	{
		if (top_pos == -1) {
			throw Minimum_size_reached();
		} else {
			return Items[top_pos];
		}
	}

	/**
		@brief Stack empty

		Metodo che restituisce se lo stack sia vuoto o meno

		@return true se é vuoto, false se non lo é
	*/
	bool stack_empty() const
	{
		if (top_pos == -1) {
			return true;
		} else {
			return false;
		}
	}

	/**
		@brief Size

		Metodo che restituisce la dimensione massima dello stack

		Nota: sebbene la dimensione massima di uno stack venga
		definita nei costruttori, questo metodo potrebbe comunque
		rivelarsi necessario, ad esempio se uno stack viene creato
		mediante =

		@return la dimensione massima dello stack
	*/
	unsigned int size() const
	{
		return maximum_size;
	}

	/**
		@brief Head

		Metodo che restituisce la posizione della cima dello stack.
		Restituisce -1 se lo stack é vuoto

		Nota: le posizioni dello stack, in accordo con la convenzione
		usata per gli array, partono da 0. Pertanto, il numero di
		elementi nello stack é head + 1

		@return la posizione della cima dello stack
	*/
	int head() const
	{
		return top_pos;
	}

	/**
		@brief Fill

		Metodo che riempie tutte le celle dello stack con il valore dato

		@param value il valore con cui riempire lo stack
	*/
	void fill(const stack_value& value)
	{
		for (unsigned int i = 0; i < maximum_size; ++i) {
			Items[i] = value;
		}
	}

	/**
		@brief Swap

		Ridefinizione del metodo std::swap per la classe Stack.
		Scambia lo stato dello stack chiamante con quello dello
		stack dato

		@param other lo stack con cui eseguire lo scambio

		@post this->Items == other.Items
		@post this->top_pos == other.top_pos
		@post this->maximum_size == other.maximum_size
	*/
	void swap(Stack& other) {
		std::swap(this->Items, other.Items);
		std::swap(this->top_pos, other.top_pos);
		std::swap(this->maximum_size, other.maximum_size);
	}

	/**
		@brief Operatore di assegnamento

		Ridefinizione dell'operatore di assegnamento per la classe Stack.
		Copia il contenuto dello stack dato nello stack chiamante. Basato
		sulla ridefinizione di std::swap

		@param other lo stack da copiare

		@return una reference al chiamante (this)

		@post this->Items == other.Items
		@post this->top_pos == other.top_pos
		@post this->maximum_size == other.maximum_size

		@throw std::bad_alloc se l'allocazione della memoria fallisce
	*/
	Stack& operator=(const Stack& other) {
		if (this != &other) {
			Stack tmp(other);
			this->swap(tmp);
		}

		#ifndef NDEBUG
		std::cout << "Stack::operator=(const Stack&)" << std::endl;
		#endif

		return *this;
	}
};

/**
	@brief Stampa

	Ridefinizione dell'operatore di stampa per la classe Stack.
	Stampa il contenuto dello stack sullo standard output

	@param os l'oggetto ostream
	@param stack lo stack da stampare

	@return l'oggetto ostream (modificato)

	@post os == os << stack.Items
*/
std::ostream& operator<<(std::ostream& os, const Stack& stack)
{
	os << "[ ";
	if (!stack.stack_empty()) {
		for (unsigned int i = 0; i <= stack.top_pos; ++i) {
			os << stack.Items[i] << " ";
		}
	}
	os << "]" << std::endl;
	return os;
}

#endif
