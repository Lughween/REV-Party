CFLAGS=-Wall -g -lm

all: test

test: test.o lecture_csv.o utils_sd.o 
	gcc -o test test.o lecture_csv.o utils_sd.o $(CFLAGS)
test.o: test.c 
	gcc -o test.o -c test.c $(CFLAGS)
lecture_csv.o: lecture_csv.c
	gcc -o lecture_csv.o -c lecture_csv.c $(CFLAGS)
utils_sd.o: utils_sd.c 
	gcc -o utils_sd.o -c utils_sd.c $(CFLAGS)

clean:
<<<<<<< HEAD
	rm -rf *.o test
=======
	rm -rf *.o
>>>>>>> d88e82c092f32630e1d3bd995f9734430a9c2eba
