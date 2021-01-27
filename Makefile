_HEADERS = func.h
HEAD_DIR = ./headers
HEADERS = $(patsubst %,$(HEAD_DIR)/%,$(_HEADERS))

_OBJ = func.o 
ODIR = ./compile
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TEST_OBJ = test1.out roto-2-haha.out roto.out todo-bien.out no-anda.out
_TEST_OBJ_DIR = ./test/compile
TEST_OBJ = $(patsubst %,$(_TEST_OBJ_DIR)/%,$(_TEST_OBJ))

LDIR = ./lib

CC = gcc
FLAGS = -c -o

all: makeFolder build

build: $(OBJ) $(HEADERS)
	$(CC) main.c $(OBJ) $(HEADERS)

# -------------------
# Test definitions
# -------------------

test: makeFolder makeTestFolder $(TEST_OBJ)

./test/compile/%.out: ./test/%.c $(HEADERS) $(OBJ)
	$(CC) -o $@ $< $(OBJ) $(HEADERS)

makeTestFolder:
	@if [ ! -d ./test/compile ]; then \
		mkdir ./test/compile; \
	fi

# -------------------
# End test definitions
# -------------------

makeFolder:
		@if [ ! -d compile ]; then \
			mkdir compile; \
		fi

./compile/%.o: $(LDIR)/%.c $(HEADERS)
	$(CC) $(FLAGS) $@ $< 

.PHONY: clean cleanTest

clean:
	rm -rf compile
	rm -rf ./headers/*.h.gch

cleanTest:
	rm -rf ./test/compile
