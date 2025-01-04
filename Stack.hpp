/**
	@file Stack.hpp

	@brief File header della classe Stack

	File di dichiarazioni della classe Stack
*/

#ifndef _STACK_HPP
#define _STACK_HPP

#include <iostream>
#include <algorithm>
#include <iterator>
#include <cassert>

struct Maximum_size_reached {};
struct Minimum_size_reached {};

/**
	@brief Classe Stack

	Classe che implementa la struttura dati stack, utilizzando un array
	statico di dimensione fissata
*/

template<typename T>
class Stack {
public:
	typedef int item_type;
	class iterator;
	class const_iterator;
private:
	item_type top_pos;       // posizione della cima dello stack
	item_type maximum_size;  // dimensione (massima) dello stack
	T* Items;                // array di elementi
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

		Nota: viene dichiarato explicit per evitare che il compilatore
		lo intenda come un cast implicito

		@param size la dimensione massima dello stack

		@post top_pos == -1
		@post maximum_size == size
		@post Items != nullptr

		@throw std::bad_alloc se l'allocazione della memoria fallisce
	*/

	explicit Stack(const item_type& size)
	: top_pos(-1), maximum_size(0), Items(nullptr)
	{
		try {
			Items = new T[size];
		}
		catch (std::bad_alloc const&) {
			std::cerr << "Allocazione di memoria fallita :(" << std::endl;
			throw;
		}

		maximum_size = size;

		for (item_type i = 0; i < maximum_size; ++i) {
			Items[i] = T();
		}

		#ifndef NDEBUG
		std::cout << "Stack::Stack(item_type)" << std::endl;
		#endif
	}

	/**
		@brief Costruttore secondario

		Costruttore secondario, che prende in input una coppia di iteratori,
		uno che punta all'inizio di una sequenza e uno che punta alla fine
		di una sequenza, e che riempie uno stack con i valori nel mezzo

		@param it_s un iteratore che punta all'inizio della sequenza
		@param it_e un iteratore che punta alla fine della sequenza

		@post maximum_size = it_e - it_s
		@post top_pos = maximum_size - 1

		@throw std::bad_alloc se l'allocazione della memoria fallisce
	*/

	template <typename I>
	Stack(I it_s, I it_e)
	: top_pos(-1), maximum_size(0), Items(nullptr)
	{
		load<I>(it_s, it_e);
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
		wipe();

		try {
			Items = new T[other.maximum_size];
		}
		catch (std::bad_alloc const&) {
			std::cerr << "Allocazione di memoria fallita :(" << std::endl;
			throw;
		}

		for (item_type i = 0; i < other.top_pos + 1; ++i) {
			this->Items[i] = other.Items[i];
		}

		this->top_pos = other.top_pos;
		this->maximum_size = other.maximum_size;

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
		wipe();

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

	void push(const T& value)
	{
		assert(top_pos < maximum_size);

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

	T pop()
	{
		assert(top_pos < maximum_size);

		if (top_pos == -1) {
			throw Minimum_size_reached();
		} else {
			T old_top = Items[top_pos];
			Items[top_pos] = T();
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

	T peek() const
	{
		assert(top_pos < maximum_size);

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
		assert(top_pos < maximum_size);

		return (top_pos == -1);
	}

	/**
		@brief Size

		Metodo che restituisce la dimensione massima dello stack.
		Utile per la stampa

		Nota: sebbene la dimensione massima di uno stack venga
		definita nei costruttori, questo metodo potrebbe comunque
		rivelarsi necessario, ad esempio se uno stack viene creato
		mediante =

		@return la dimensione massima dello stack
	*/

	item_type size() const
	{
		assert(top_pos < maximum_size);

		return maximum_size;
	}

	/**
		@brief Head

		Metodo che restituisce la posizione della cima dello stack.
		Restituisce -1 se lo stack é vuoto. Utile per la stampa

		Nota: le posizioni dello stack, in accordo con la convenzione
		usata per gli array, partono da 0. Pertanto, il numero di
		elementi nello stack é head + 1

		@return la posizione della cima dello stack
	*/

	item_type head() const
	{
		assert(top_pos < maximum_size);

		return top_pos;
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
		assert(top_pos < maximum_size);

		wipe();

		item_type d = 0;
		I temp = it_s;
		while (temp != it_e) {
			d++;
			temp++;
		}

		maximum_size = d;
		top_pos = maximum_size - 1;

		try {
			Items = new T[maximum_size];
		}
		catch (std::bad_alloc const&) {
			std::cerr << "Allocazione di memoria fallita :(" << std::endl;
			throw;
		}

		for (item_type i = 0; it_s != it_e; ++i, it_s++) {
			Items[i] = static_cast<T>(*it_s);
		}
	}

	/**
		@brief Wipe

		Metodo che svuota tutte le celle dello stack,
		azzerandone la dimensione

		@post top_pos == -1
		@post maximum_size == 0
		@post Items == nullptr
	*/

	void wipe()
	{
		assert(top_pos < maximum_size);

		if (Items != nullptr) {
			delete[] Items;
			Items = nullptr;
		}

		maximum_size = 0;
		top_pos = -1;
	}

	/**
		@brief Clear

		Metodo che svuota tutte le celle dello stack,
		lasciando peró intatta la dimensione

		@post top_pos == -1
	*/

	void clear()
	{
		assert(top_pos < maximum_size);

		if (Items != nullptr) {
			for (item_type i = 0; i <= top_pos; ++i) {
				Items[i] = T();
			}
		}

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

	void swap(Stack& other)
	{
		assert(top_pos < maximum_size);

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

	Stack& operator=(const Stack& other)
	{
		assert(top_pos < maximum_size);

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
	Stack filter_out(P predicate)
	{
		assert(top_pos < maximum_size);

		Stack S(this->maximum_size);

		for (item_type i = 0; i <= this->top_pos; ++i) {
			if (predicate(this->Items[i]) == true) {
				S.push(Items[i]);
			}
		}

		return S;
	}

	class iterator {
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef T*                        pointer;
		typedef T&                        reference;
	private:
		T* ptr;
		friend class Stack;
		friend class const_iterator;

		// Costruttore privato di inizializzazione usato dalla
		// classe Stack per i metodi begin() e end()
		iterator(T* n) : ptr(n) {}
	public:
		// Costruttore di default
		iterator() : ptr(nullptr) {}

		// Copy constructor
		iterator(const iterator &other) : ptr(nullptr)
		{
			this->ptr = other.ptr;
		}

		// Operatore di assegnamento
		iterator& operator=(const iterator &other)
		{
			this->ptr = other.ptr;
			return *this;
		}

		// Distruttore
		~iterator() {}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const
		{
			return *ptr;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const
		{
			return ptr;
		}

		// Operatore di iterazione pre-incremento
		iterator& operator++()
		{
			ptr++;
			return *this;
		}

		// Operatore di iterazione post-incremento
		iterator operator++(int dummy)
		{
			iterator tmp(*this);
			++(*this);
			return tmp;
		}

		// Uguaglianza fra due iterator
		bool operator==(const iterator &other) const
		{
			return ptr == other.ptr;
		}

		// Uguaglianza fra un iterator ed un const_iterator
		bool operator==(const const_iterator &other) const
		{
			return ptr == other.ptr;
		}

		// Diversitá fra due iterator
		bool operator!=(const iterator &other) const
		{
			return ptr != other.ptr;
		}

		// Diversitá fra un iterator ed un const_iterator
		bool operator!=(const const_iterator &other) const
		{
			return ptr != other.ptr;
		}
	};

	class const_iterator {
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;
	private:
		const T* ptr;
		friend class Stack;
		friend class iterator;

		// Costruttore privato di inizializzazione usato dalla 
		// classe Stack per i metodi begin() e end()
		const_iterator(const T* n) : ptr(n) {}
	public:
		// Costruttore di default
		const_iterator() : ptr(nullptr) {}

		// Copy constructor
		const_iterator(const const_iterator &other) : ptr(nullptr)
		{
			this->ptr = other.ptr;
		}

		// Operatore di assegnamento
		const_iterator& operator=(const const_iterator &other)
		{
			this->ptr = other.ptr;
			return *this;
		}

		// Distruttore
		~const_iterator() {}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const
		{
			return *ptr;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const
		{
			return ptr;
		}

		// Operatore di iterazione pre-incremento
		const_iterator& operator++()
		{
			ptr++;
			return *this;
		}

		// Operatore di iterazione post-incremento
		const_iterator operator++(int dummy)
		{
			const_iterator tmp(*this);
			++(*this);
			return tmp;
		}

		// Uguaglianza fra due const_iterator
		bool operator==(const const_iterator &other) const
		{
			return ptr == other.ptr;
		}

		// Uguaglianza fra un const_iterator ed un iterator
		bool operator==(const iterator &other) const {
			return ptr == other.ptr;
		}

		// Diversitá fra due const_iterator
		bool operator!=(const const_iterator &other) const
		{
			return ptr != other.ptr;
		}

		// Diversitá fra un const_iterator ed un iterator
		bool operator!=(const iterator &other) const {
			return ptr != other.ptr;
		}

		// Conversione da iterator a const_iterator
		const_iterator(const iterator &other) : ptr(nullptr)
		{
			this->ptr = other.ptr;
		}

		// Assegnamento di un iterator ad un const_iterator
		const_iterator& operator=(const iterator &other)
		{
			this->ptr = other.ptr;
			return *this;
		}
	};

	// Ritorna l'iteratore all'inizio della sequenza
	iterator begin()
	{
		if (!stack_empty()) {
			return iterator(&Items[0]);
		} else {
			return iterator(nullptr);
		}
	}

	const_iterator begin() const
	{
		if (!stack_empty()) {
		return const_iterator(&Items[0]);
		} else {
			return const_iterator(nullptr);
		}
	}

	// Ritorna l'iteratore alla fine della sequenza
	// Nota: sommare 1 NON é safe
	iterator end()
	{
		if (!stack_empty()) {
		return iterator(&Items[top_pos] + 1);
		} else {
			return iterator(nullptr);
		}
	}

	const_iterator end() const
	{
		if (!stack_empty()) {
		return const_iterator(&Items[top_pos] + 1);
		} else {
			return const_iterator(nullptr);
		}
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

template<typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& stack)
{
	typename Stack<T>::const_iterator start = stack.begin();
	typename Stack<T>::const_iterator end = stack.end();

	os << "{ ";
	while (start != end) {
		os << "[" << *start << "] ";
		start++;
	}

	for (typename Stack<T>::item_type i = stack.head() + 1; i < stack.size(); ++i) {
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

template <typename T, typename F>
void transform(Stack<T>& stack, F functor)
{
	typename Stack<T>::iterator start = stack.begin();
	typename Stack<T>::iterator end = stack.end();

	while (start != end) {
		*start = functor(*start);
		start++;
	}
}

#endif
