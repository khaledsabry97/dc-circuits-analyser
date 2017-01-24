# directories
SRC_DIR = Sources

HDR_DIR = Headers

BLD_DIR = Build

# executable
EXEC = $(BLD_DIR)/main

# compiler
COMPILER = g++

CPP_VER = 11

COMPILER_FLAGS = -std=c++$(CPP_VER)
COMPILER_FLAGS += -I $(HDR_DIR) 
COMPILER_FLAGS += -g 
COMPILER_FLAGS += $(SRC_DIR)/*.cpp -o $(EXEC)


run:
	if [ ! -x $(EXEC) ]; then make main; fi
	$(EXEC)

main: 
	$(COMPILER) $(COMPILER_FLAGS) 

test:
	cat ./test/input | $(EXEC) &> ./test/result
	less ./test/result

archieve:
	mkdir ./test/archieve
	cp -i ./test/input ./test/archieve
	cp -i ./test/result ./test/archieve

duty:
	egrep -H -n '(BUG|TODO):'  Sources/*.* Headers/*.* -A 1 -B 1

clean:
	rm $(EXEC) 2> /dev/null
	rm -r *.dSYM $(BLD_DIR)/*.dSYM 2> /dev/null