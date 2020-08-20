#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
bool IsTextEqualPatternOrQuestionMark(char character, char pattern);
int check(char * text,char *pattern);
int main()
{
	char text[512];
    char pattern[512];
    printf("Please enter the pattern:：");
    fgets(pattern, 512, stdin);
    printf("Please enter the  string:：");
    fgets(text, 512, stdin);
    
    pattern[strlen(pattern) - 1] = '\0';
    text[strlen(text) - 1] = '\0';
    char *token = strtok(text , " ");
    char *tmp[512];
    int i = 0;
    int counter = 0;
    while( token != NULL ) 
	{	
		tmp[i] = token;
		token = strtok(NULL," ");
		i++;
		counter ++;
	}
	printf("Result:\n");
	for (int i = 0; i < counter; ++i)
	{
		if (check(tmp[i],pattern))
		{
			printf("%s ",tmp[i]);
		}
	}
	printf("\n");
	return 0;
}
bool IsTextEqualPatternOrQuestionMark(char c, char pattern)
{
    if (c == pattern || pattern == '?')
        return true;
    return false;
}
int check(char *text,char *pattern)
{
	int textIndex = 0;
	int patternIndex = 0;
	int asteriskIndex = -1;
	while (textIndex < strlen(text))
	{
	    bool isEndOfPattern = patternIndex == strlen(pattern);
	    if (!isEndOfPattern && IsTextEqualPatternOrQuestionMark(text[textIndex], pattern[patternIndex]))
	    {
	        textIndex++;
	        patternIndex++;
	    } 
	    else if (!isEndOfPattern && pattern[patternIndex] == '*')
        {
            asteriskIndex = patternIndex;
            patternIndex += 1;
        }
        else if (asteriskIndex != -1)
        {
            patternIndex = asteriskIndex + 1;
            textIndex += 1;
            continue;
        }
	    else 
	    {
	            return false;
	    }
	}
	while (patternIndex < strlen(pattern) && pattern[patternIndex] == '*')
        patternIndex++;
	return patternIndex == strlen(pattern);
}