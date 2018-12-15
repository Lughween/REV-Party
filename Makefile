CFLAGS=-Wall -g -lm -L -lcircuit

all: test

test: test.o graphePython.o condorcet.o liste.o elementliste.o lecture_csv.o utils_sd.o 
	gcc -o test test.o lecture_csv.o utils_sd.o condorcet.o liste.o elementliste.o graphePython.o $(CFLAGS)
test.o: test.c 
	gcc -o test.o -c test.c $(CFLAGS)
lecture_csv.o: lecture_csv.c
	gcc -o lecture_csv.o -c lecture_csv.c $(CFLAGS)
condorcet.o: condorcet.c
	gcc -o condorcet.o -c condorcet.c $(CFLAGS)
liste.o: liste.c 
	gcc -o liste.o -c liste.c $(CFLAGS)
elementliste.o: elementliste.c
	gcc -o elementliste.o -c elementliste.c $(CFLAGS)
graphePython.o: graphePython.c
	gcc -o graphePython.o -c graphePython.c $(CFLAGS)
utils_sd.o: utils_sd.c 
	gcc -o utils_sd.o -c utils_sd.c $(CFLAGS)

clean:
	rm -rf *.o
