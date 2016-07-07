all: main

main: main.o
	gcc main.o -lpthread -o main

main.o: main.c
	gcc main.c -c

clean:
	rm -rf *.o main 
