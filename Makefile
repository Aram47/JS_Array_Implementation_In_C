GCC = gcc
FILES = main.c ./src/array.c
EXE = array
DEL = rm

all:
	$(GCC) $(FILES) -o $(EXE)

del:
	$(DEL) $(EXE)