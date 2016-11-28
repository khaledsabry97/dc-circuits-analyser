main: main.cpp
	g++ -std=c++11 -g main.cpp Node.cpp Element.cpp Circuit.cpp -o main

test: test.cpp
	g++ -std=c++11 -g test.cpp Node.cpp Element.cpp Circuit.cpp -o test

clean:
	rm -f *.o main
