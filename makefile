all: nim.o nimhelp.o alphanim.o
	clang -std=c99 -Wall -pedantic nim.o nimhelp.o alphanim.o -o a
nim.o: nim.c nim.h
	clang -std=c99 -Wall -pedantic -c nim.c
nimhelp.o: nimhelp.c nim.h
	clang -std=c99 -Wall -pedantic -c nimhelp.c
alphanim.o: alphanim.c nim.h
	clang -std=c99 -Wall -pedantic -c alphanim.c
clean:
	rm *.o *.exe