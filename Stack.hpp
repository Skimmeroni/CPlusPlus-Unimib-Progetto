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
	template <typename F>
	friend void transform(const Stack& stack, F functor);

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
			throw;
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
			throw;
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
			throw;
		}

		for (unsigned int i = 0; i < other.top_pos + 1; ++i) {
			Items[i] = other.Items[i];
		}

		top_pos = other.top_pos;
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
		Items = nullptr;
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

		@post Items[i] == value
	*/
	void fill(const stack_value& value)
	{
		stack_value* tmp = nullptr;

		try {
			tmp = new stack_value[maximum_size];
		}
		catch (std::bad_alloc) {
			std::cerr << "Allocazione di memoria fallita :(" << std::endl;
			throw;
		}

		for (unsigned int i = 0; i < maximum_size; ++i) {
			tmp[i] = value;
		}

		std::swap(Items, tmp);
		delete[] tmp;
		tmp = nullptr;

		top_pos = maximum_size - 1;

		#ifndef NDEBUG
		std::cout << "Stack::fill(const stack_value&)" << std::endl;
		#endif
	}

	/**
		@brief Load

		Metodo che prende in input una coppia di iteratori, uno che
		punta all'inizio di una sequenza e uno che punta alla fine
		di una sequenza, e che riempie uno stack con i valori nel
		mezzo. Se lo stack contiene giá dei valori, viene svuotato

		@param it_s un iteratore che punta all'inizio della sequenza
		@param it_e un iteratore che punta alla fine della sequenza

		@post maximum_size = it_e - it_s
		@post top_pos = maximum_size - 1
		@post Items != nullptr

		@throw std::bad_alloc se l'allocazione della memoria fallisce
	*/

	template <typename I>
	void load(I it_s, I it_e)
	{
		if (Items != nullptr) {
			delete[] Items;
			Items = nullptr;
		}

		maximum_size = it_e - it_s;
		top_pos = maximum_size - 1;

		try {
			Items = new stack_value[maximum_size];
		}
		catch (std::bad_alloc) {
			std::cerr << "Allocazione di memoria fallita :(" << std::endl;
			throw;
		}

		for (unsigned int i = 0; it_s != it_e; ++i, it_s++) {
			Items[i] = *it_s;
		}
	}

	/**
		@brief Clear

		Metodo che svuota tutte le celle dello stack

		Nota: non é necessario modificare nessun valore
		dello stack, é sufficiente porre la posizione 
		a -1. I valori nelle celle sono perduti comunque

		@post top_pos == -1
	*/
	void clear()
	{
		top_pos = -1;
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

	/**
		@brief Filter out

		Metodo che prende in input un predicato di tipo generico e ritorna
		uno stack costituito solamente dagli elementi dello stack chiamante
		che rispettano il predicato

		@param predicate il predicato con cui testare lo stack

		@return uno stack opportunamente costruito
	*/
	template <typename P>
	Stack filter_out(P predicate) {
		Stack S(this->maximum_size);

		for (unsigned int i = 0; i <= this->top_pos; ++i) {
			if (predicate(this->Items[i]) == true) {
				S.push(Items[i]);
			}
		}

		return S;
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
	os << "{ ";
	if (!stack.stack_empty()) {
		for (unsigned int i = 0; i <= stack.top_pos; ++i) {
			os << "[" << stack.Items[i] << "] ";
		}
	}
	for (unsigned int i = stack.top_pos + 1; i < stack.maximum_size; ++i) {
		os << "[] ";
	}
	os << "}" << std::endl;
	return os;
}

/**
	@brief Transform

	Funzione che prende in input uno stack ed un funtore di tipo generico
	e modifica tutti gli elementi dello stack applicandovi tale funtore

	@param stack lo stack da modificare
	@param functor il funtore da applicare agli elementi dello stack

	@post stack.Items[i] = functor(stack.Items[i])
*/
template <typename F>
void transform(const Stack& stack, F functor)
{
	for (unsigned int i = 0; i <= stack.top_pos; ++i) {
		stack.Items[i] = functor(stack.Items[i]);
	}
}

#endif
