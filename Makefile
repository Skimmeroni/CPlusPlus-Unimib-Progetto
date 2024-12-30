CXXFLAGS=-pedantic -std=c++11 -fsanitize=address

main.exe: Stack.o
	g++ ${CXXFLAGS} Stack.o -o main.exe

Stack.o: Stack.cxx Stack.hpp
	g++ ${CXXFLAGS} -c Stack.cxx -o Stack.o

all: main.exe html

run: main.exe
	./main.exe

html:
	doxygen

clean:
	rm -f Stack.o main.exe
	rm -rf html 
