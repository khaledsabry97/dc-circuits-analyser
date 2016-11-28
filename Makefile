main: main.cpp
	g++ -std=c++11 -g main.cpp -o main

test: test.cpp
	g++ -std=c++11 -g test.cpp -o test

clean:
	rm -f *.o main
