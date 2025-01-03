CXX = g++
CXXFLAGS = -ggdb -pedantic -std=c++11 -fsanitize=address,leak,undefined -fno-omit-frame-pointer -Wall -g
LDFLAGS = -ggdb -pedantic -std=c++11 -fsanitize=address,leak,undefined -fno-omit-frame-pointer -Wl

main.exe: Stack.o
	$(CXX) $(CXXFLAGS) Stack.o -o main.exe

Stack.o: Stack.cxx Stack.hpp
	$(CXX) $(CXXFLAGS) -c Stack.cxx -o Stack.o

all: main.exe html

run: main.exe
	./main.exe

html:
	doxygen

.PHONY: clean
clean:
	rm -f Stack.o main.exe
	rm -rf html
