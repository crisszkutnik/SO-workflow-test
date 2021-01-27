_HEADERS = func.h
HEAD_DIR = ./headers
HEADERS = $(patsubst %,$(HEAD_DIR)/%,$(_HEADERS))

_OBJ = func.o 
ODIR = ./compile
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TEST_OBJ = test1.out
_TEST_OBJ_DIR = ./test/compile
TEST_OBJ = $(patsubst %,$(_TEST_OBJ_DIR)/%,$(_TEST_OBJ))

LDIR = ./lib

CC = gcc
FLAGS = -c -o

build: $(OBJ) $(HEADERS) makeFolder
	$(CC) main.c $(OBJ) $(HEADERS)

# -------------------
# Test definitions
# -------------------

test: $(TEST_OBJ)

./test/compile/%.out: ./test/%.c $(HEADERS) $(OBJ)
	$(CC) -o $@ $< $(OBJ) $(HEADERS)

# -------------------
# End test definitions
# -------------------

makeFolder:
		@echo "\n\n- CREANDO CARPETA compile"
		@if [ ! -d compile ]; then \
			mkdir compile; \
			echo -  CARPETA CREADA""; \
		else \
			echo "-  CARPETA COMPILE EXISTENTE"; \
		fi

./compile/%.o: $(LDIR)/%.c $(HEADERS)
	$(CC) $(FLAGS) $@ $< 

.PHONY: clean cleanTest

clean:
	rm -rf ./compile/*
	rm -rf ./headers/*.h.gch

cleanTest:
	rm -rf ./test/compile/*
