main: main.cpp
	g++ -std=c++11 -g main.cpp Node.cpp Element.cpp Circuit.cpp -o main

clean:
	rm -f *.o main
