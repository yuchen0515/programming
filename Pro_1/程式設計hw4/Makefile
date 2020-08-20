all: hw0401-1.c hw0401-2.c hw0401_header.c hw0402.c hw0403.c hw0404.c hw0405.c hw0405_header.c hw0406.c
	gcc -c hw0401-1.c hw0401-2.c hw0401_header.c
	gcc hw0401-1.o hw0401_header.o -o hw0401-1
	gcc hw0401-2.o hw0401_header.o -o hw0401-2
	gcc hw0402.c -o hw0402
	gcc hw0403.c -o hw0403
	gcc hw0404.c -lm -o hw0404
	gcc -c hw0405.c hw0405_header.c
	gcc hw0405.o hw0405_header.o -o hw0405
	gcc hw0406.c -o hw0406
clean:
	rm -f *.o

