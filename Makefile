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
COMPILER_FLAGS += -ferror-limit=50


main: 
	$(COMPILER) $(COMPILER_FLAGS) 
	
run:
	if [ ! -x $(EXEC) ]; then make main; fi
	$(EXEC)

test:
	cat ./test/input | $(EXEC) &> ./test/result
	cat ./test/result

archieve:
	cp ./test/input ./Test/archieve/input`date +%d-%H:%M`
	cp ./test/result ./Test/archieve/result`date +%d-%H:%M`

newtest:
	printf '# \n\nxx\n\n# ' > ./test/input

duty:
	egrep -H -n '(BUG|TODO):'  Sources/*.* Headers/*.* -A 1 -B 1

update:
	git add .; git commit ; git push

clean:
	rm $(EXEC) 2> /dev/null
	rm -r *.dSYM $(BLD_DIR)/*.dSYM 2> /dev/null