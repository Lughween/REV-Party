CFLAGS=-Wall -g -lm

all: test

test: test.o condorcet.o lecture_csv.o utils_sd.o 
	gcc -o test test.o lecture_csv.o utils_sd.o condorcet.o $(CFLAGS)
test.o: test.c 
	gcc -o test.o -c test.c $(CFLAGS)
lecture_csv.o: lecture_csv.c
	gcc -o lecture_csv.o -c lecture_csv.c $(CFLAGS)
condorcet.o: condorcet.c
	gcc -o condorcet.o -c condorcet.c $(CFLAGS)
utils_sd.o: utils_sd.c 
	gcc -o utils_sd.o -c utils_sd.c $(CFLAGS)

clean:
	rm -rf *.o
