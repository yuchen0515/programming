all: hw0501.c hw0502.c hw0503.c hw0504.c hw0505.c hw0505_header.c hw0506.c
	gcc hw0501.c -o hw0501
	gcc hw0502.c -o hw0502
	gcc hw0503.c -o hw0503
	gcc hw0504.c -o hw0504
	gcc -c hw0505.c hw0505_header.c
	gcc hw0505.o hw0505_header.o -o hw0505
	#gcc hw0506.c -o hw0506
	
clean:
	rm -rf *.o
