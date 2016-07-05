all: dz1

dz1: dz1.o sort.o
	g++ dz1.o sort.o -o dz1

dz1.o: dz1.cpp sort.h
	g++ -c dz1.cpp

sort.o: sort.cpp
	g++ -c sort.cpp

clean:
	rm -rf *.o dz1
