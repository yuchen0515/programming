CFLAGS = -O3
INCLUDE = -I curl-7.70.0/include
LIB = -L curl-7.70.0/lib/.libs/

all:
	gcc hw0501.c -o hw0501
	gcc hw0502.c -o hw0502
	gcc -D DEBUG_LEVEL_VVERBOSE hw0503.c -o hw0503
	#gcc -D DEBUG_LEVEL_VERBOSE hw0503.c -o hw0503
	#gcc -D DEBUG_LEVEL_INFO hw0503.c -o hw0503
	#gcc -D DEBUG_LEVEL_ERROR hw0503.c -o hw0503
	#gcc -D DEBUG_LEVEL_NONE hw0503.c -o hw0503
	#gcc hw0503.c -o hw0503
	gcc hw0504.c -o hw0504
	gcc ${CFLAGS} ${INCLUDE} ${LIB} hw0504_2.c -o hw0504_2 -lcurl
	gcc hw0505.c -o hw0505

