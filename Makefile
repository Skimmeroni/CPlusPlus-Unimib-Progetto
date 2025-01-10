CXX = g++
BASE_CXXFLAGS = -Wall -g
BASE_LDFLAGS = -Wl

EXTRA_FLAGS = -ggdb -pedantic -std=c++11 -fsanitize=address,leak,undefined -fno-omit-frame-pointer
CXXFLAGS = $(BASE_CXXFLAGS) $(EXTRA_FLAGS)
LDFLAGS = $(BASE_LDFLAGS) $(EXTRA_FLAGS)

main.exe: Stack.o
	$(CXX) $(CXXFLAGS) Stack.o -o main.exe

Stack.o: Stack.cxx Stack.hpp
	$(CXX) $(CXXFLAGS) -c Stack.cxx -o Stack.o

doc:
	doxygen

clean:
	rm -f Stack.o main.exe
	rm -rf html

all: main.exe doc

.PHONY: clean doc all
