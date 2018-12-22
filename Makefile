CFLAGS=-Wall -g -lm -L -lcircuit

all: test

test: test.o graphePython.o condorcet.o lecture_csv.o utils_sd.o liste.o elementliste.o
	gcc -o test test.o liste.o graphePython.o condorcet.o lecture_csv.o utils_sd.o  elementliste.o $(CFLAGS)

test.o: test.c
	gcc -o test.o -c test.c $(CFLAGS)

graphePython.o: graphePython.c
	gcc -o graphePython.o -c graphePython.c $(CFLAGS)

condorcet.o: condorcet.c
	gcc -o condorcet.o -c condorcet.c $(CFLAGS)

lecture_csv.o: lecture_csv.c
	gcc -o lecture_csv.o -c lecture_csv.c $(CFLAGS)

utils_sd.o: utils_sd.c
	gcc -o utils_sd.o -c utils_sd.c $(CFLAGS)

elementliste.o: elementliste.c
	gcc -o elementliste.o -c elementliste.c $(CFLAGS)

liste.o: liste.c
	gcc -o liste.o -c liste.c $(CFLAGS)



clean:
	rm -rf *.o
