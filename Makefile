main: 
	g++ -std=c++11 -g *.cpp  -o main

test:
	cat ./test/input | ./main &> ./test/result ; less ./test/result

archieve:
	mkdir ./test/archieve ; cp -n ./test/input ./test/archieve; cp -n ./test/result ./test/archieve/result 

clean:
	rm -f *.o main
