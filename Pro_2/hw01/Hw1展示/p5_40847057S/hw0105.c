#include<string.h>
#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<ctype.h>
#include<stdlib.h>

char arrange1(char *str)
{
	for(uint16_t i=0; i<200; i++)
	{
		if(str[i]==' ')
		{
			for(uint16_t j=i; j<200; j++)
			{
				str[j]=str[j+1];
			}
		}

		if(str[i]==' ') i--;
	}
	return 0;
}

bool availability(char *str)
{
	if(*str=='\0' || *str=='\n') return true;

	if(isdigit(*str)) return availability(str+1);

	if(*str=='+' || *str=='-' || *str=='*' || *str=='/' || *str=='(' || *str==')' || *str==',') return availability(str+1);

	return false;
}

char arrange2(char *str)
{
	for(uint16_t i=0; i<200; i++)
	{
		str[i]=str[i+1];

		if(str[i]=='(' || str[i]==')' || str[i]==',')
		{
			str[i]=' ';
		}

		if(str[i]=='\0') break;
	}
}

void simplify(int32_t *numerator, int32_t *denominator)
{
	int32_t x, y ,t;
	x=*numerator;
	y=*denominator;

	while(y!=0)//calculate gcd
	{
		t=y;
		y=x%y;
		x=t;
	}
		*numerator=*numerator/x;
		*denominator=*denominator/x;
}

void lcm(int32_t *denominator1, int32_t *denominator2, int32_t *numerator1, int32_t *numerator2)//lowest common multiply
{
	int32_t x, y ,t;
	x=*denominator1;
	y=*denominator2;

	while(y!=0)//calculate gcd
	{
		t=y;
		y=x%y;
		x=t;
	}
	*numerator1=*numerator1 * *denominator2 / x;
	*numerator2=*numerator2 * *denominator1 / x;
	*denominator1=(*denominator1) / x * (*denominator2);
	*denominator2=*denominator1;
}

int main()
{
	char str[200]={0};
	int32_t numerator[15]={0};
	int32_t denominator[15]={0};
	char sign[15]={0};
	int32_t nume=0, deno=0;

	printf("Please enter an equation:");
	fgets(str, 200, stdin);

	arrange1(str);

	if(!availability(str))
	{
		printf("INVALID INPUT! INCALCULABLE!\n");
		return 0;
	}

	arrange2(str);

	char *token=strtok(str, " ");
	uint16_t i=1;
	while(token!=NULL)
	{
		if(i%3==1) numerator[i/3]=atoi(token);

		else if(i%3==2)
		{
			denominator[i/3]=atoi(token);
			if(denominator[i/3]==0)
			{
				printf("INVALID INPUT! INCALCULABLE!\n");
				return 0;
			}
		}

		else sign[i/3]=*token;

		i++;
		token=strtok(NULL, " ");
	}

	for(i=1; sign[i]!='\n'; i++)
	{
		if(sign[i]=='*')
		{
			simplify(&numerator[i-1], &denominator[i-1]);
			simplify(&numerator[i], &denominator[i]);
			simplify(&numerator[i-1], &denominator[i]);
			simplify(&numerator[i], &denominator[i-1]);

			numerator[i-1]=numerator[i-1]*numerator[i];
			denominator[i-1]=denominator[i-1]*denominator[i];
			nume=numerator[i-1];
			deno=denominator[i-1];

			for(uint16_t j=i; sign[j-1]!='\n'; j++)
			{
				numerator[j]=numerator[j+1];
				denominator[j]=denominator[j+1];
				sign[j]=sign[j+1];
			}
			i--;
		}

		else if(sign[i]=='/')
		{
			simplify(&numerator[i-1], &denominator[i-1]);
			simplify(&numerator[i], &denominator[i]);
			simplify(&numerator[i-1], &numerator[i]);
			simplify(&denominator[i-1], &denominator[i]);

			numerator[i-1]=numerator[i-1]*denominator[i];
			denominator[i-1]=denominator[i-1]*numerator[i];
			nume=numerator[i-1];
			deno=denominator[i-1];

			if(deno==0)
			{
				printf("INVALID INPUT! INCALCULABLE!\n");
				return 0;
			}

			for(uint16_t j=i; sign[j-1]!='\n'; j++)
			{
				numerator[j]=numerator[j+1];
				denominator[j]=denominator[j+1];
				sign[j]=sign[j+1];
			}
			i--;
		}
	}

	for(i=1; sign[i]!='\n'; i++)
	{
		if(sign[i]=='+')
		{
			lcm(&denominator[i-1], &denominator[i], &numerator[i-1], &numerator[i]);
			numerator[i]=numerator[i-1]+numerator[i];
			nume=numerator[i];
			deno=denominator[i];
		}

		else if(sign[i]=='-')
		{
			lcm(&denominator[i-1], &denominator[i], &numerator[i-1], &numerator[i]);
			numerator[i]=numerator[i-1]-numerator[i];
			nume=numerator[i];
			deno=denominator[i];
		}
	}

	int32_t x, y ,t;
	x=nume;
	y=deno;

	while(y!=0)//calculate gcd
	{
		t=y;
		y=x%y;
		x=t;
	}
	nume=nume/x;
	deno=deno/x;

	printf("(%d,%d)\n", nume, deno);

	return 0;
}
