#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

void cpstr(char *str, char *sor){
	int32_t count = 0;
	while (1){
		if (*(sor+count) == '\0'){
			str = realloc(str, count);
			*(str+count) = '\0'; return;
		}else{
			*(str+count) = *(sor+count);
		}
		count +=1;
	}
}

struct option long_options[] = 
{  
     { "all",  0, NULL, 'a' },  
     { "break", 0, NULL, 'b' },  
     { "cancel", 1, NULL, 'c' },  
     {  0, 0, 0, 0},  
};  

int main( int argc, char *argv[] )
{
    printf( "argc: %d\n", argc );
    
    for( int32_t i = 0 ; i < argc ; i++ )
    {
        printf( "argv[%d]: %s\n", i, argv[i] );
    }
    
    puts( "---" );
    
    // getopt_long
    
    int32_t c = 0;
    int32_t index = 0;
	int32_t record_b = 0;
	int32_t getop_count = 0;
	char *str = calloc(1000, sizeof(char));

	if (argc < 3){
		printf("Your input error!\n");
		return 0;
	}
    
    while ( ( c = getopt_long( argc, argv, "web:", long_options, &index ) ) != -1 )
    {
        //printf( "index: %d\n", index );
        switch( c )
        {
            case 'b':
                printf( "option: -b, %s\n", optarg );
				record_b = 1;
				cpstr(str, optarg);
                break;
			case 'w':
                printf( "option: -w\n");
				break;
			case 'e':
                printf( "option: -e\n");
				break;


            //case '?':
            //    printf( "option: ?\n" );
            //    break;
            default:
                printf( "option: unknown\n"); 
				return 0;
        }
    }
	argc+= getop_count;
	if (record_F ==1 && argc != 7){
		printf("Input error!\n");
		return 0;
	}else if (record_F == 0 && argc != 5){
		printf("Input error!\n");
		return 0;
	}
	//printf("%d\n", getop_count);
	//printf( "option: -F, %s\n", str );
    
    return 0;
}
