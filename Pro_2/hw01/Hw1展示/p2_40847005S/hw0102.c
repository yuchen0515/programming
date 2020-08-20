#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main()
{
	char mac[20]={0};
	printf("Please enter the string:");
	fgets(mac,20,stdin);
	mac[strlen(mac)-1]='\0';
	if(strlen(mac)!=17)
	{
		printf("invalid len\n");
		return 0;
	}
	for(size_t c=0;c<17;c++)
	{
		if((c+1)%3==0)
		{
			if(mac[c]!=':')
			{
				printf("invalid ':'\n");
				return 0;
			}
		}
	}

	char *token=":",*number=NULL;
	int nset[6]={0},norder=0;
	number=strtok(mac,token);
	while(number!=NULL)
	{
		nset[norder]=strtol(number,NULL,16);
		if(nset[norder]==0 && strcmp(number,"00")!=0)
		{
			printf("invalid number\n");
			return 0;
		}
		number=strtok(NULL,token);
		norder++;
	}
	for(int p=0;p<6;p++)
	{
		printf("%02x",nset[p]);
		if(p<5)
		{
			printf("-");
		}
	}
	printf("\n");
}