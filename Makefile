GCC = gcc
FILES = main.c array.c
EXE = array
DEL = rm

all:
	$(GCC) $(FILES) -o $(EXE)

del:
	$(DEL) $(EXE)