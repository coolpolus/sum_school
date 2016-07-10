all: win1 win2
win1: win1.o 
	
win1.o: File2.c bin_sem.c 
	gcc File1.c bin_sem.c -o win1
win2: win2.o
	 
win2.o: File1.c bin_sem.c
	gcc File2.c bin_sem.c -o win2
clean:
	rm -f *.o win1 win2
