CXXFLAGS=-pedantic -std=c++11 -fsanitize=address

main.exe: Stack.o
	g++ ${CXXFLAGS} Stack.o -o main.exe

Stack.o: Stack.cxx
	g++ ${CXXFLAGS} -c Stack.cxx

clean: 
	rm -f Stack.o main.exe
