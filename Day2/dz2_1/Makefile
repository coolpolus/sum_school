all: dz2

dz2: dz2_1.o
	gcc dz2_1.o -lpthread -o dz2

dz2_1.o: dz2_1.c
	gcc -c dz2_1.c

clean:
	rm -rf *.o dz2
