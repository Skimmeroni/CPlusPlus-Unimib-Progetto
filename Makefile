CXX = g++
BASE_CXXFLAGS = -Wall -g
BASE_LDFLAGS = -Wl

EXTRA_FLAGS = -ggdb -pedantic -std=c++11 -fsanitize=address,leak,undefined -fno-omit-frame-pointer
CXXFLAGS = $(BASE_CXXFLAGS) #$(EXTRA_FLAGS)
LDFLAGS = $(BASE_LDFLAGS) #$(EXTRA_FLAGS)

main.exe: Main.o Test.o
	$(CXX) $(CXXFLAGS) Main.o Test.o -o main.exe

Main.o: Main.cpp Stack.hpp
	$(CXX) $(CXXFLAGS) -c Main.cpp -o Main.o

Test.o: Test.cpp
	$(CXX) $(CXXFLAGS) -c Test.cpp -o Test.o

doc:
	doxygen

clean:
	rm -f *.o *.exe
	rm -rf html

all: main.exe doc

.PHONY: clean doc all
