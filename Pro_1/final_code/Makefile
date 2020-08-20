all: final.o test.c
	gcc test.c final.o -o test
	
final.o: final.c final.h
	gcc -c final.c

clean:
	rm -f *.o test
