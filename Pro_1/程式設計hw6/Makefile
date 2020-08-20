all: hw0601.c hw0601_header.c hw0602.c hw0603.c hw0604.c hw0605.c hw0606.c
	gcc -c hw0601.c hw0601_header.c
	gcc hw0601.o hw0601_header.o -o hw0601
	gcc hw0602.c -o hw0602
	gcc hw0603.c -lm -o hw0603
	gcc hw0604.c -o hw0604
	gcc hw0605.c -o hw0605
	gcc hw0606.c -o hw0606

clean:
	rm -rf *.o
