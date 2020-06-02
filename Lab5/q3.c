#include<stdio.h>
#include<ctype.h>
#include "token.h"
#include<string.h>

Token lookahead;
int i=0;
FILE *f;
Table *tb;

void proc_ad()
{
	lookahead=getNextToken(f,tb);
	printf("%s     2\n",lookahead->token_name);
	if(strcmp(lookahead->token_name,"b")==0)
	{
		proc_ad();
	}
	else
		fseek(f,-strlen(lookahead->token_name)-1,SEEK_CUR);
}

void proc_a()
{
	lookahead=getNextToken(f,tb);
	printf("%s     3\n",lookahead->token_name);	
	if(strcmp(lookahead->token_name,"b")==0)
	{
		proc_ad();
	}
	else
		printf("Error6\n");
}

void proc_b()
{
	lookahead=getNextToken(f,tb);
	printf("%s     4\n",lookahead->token_name);
	if(strcmp(lookahead->token_name,"d")==0)
		return;
	else
		printf("Error5\n");
}


void proc_s()
{
	lookahead=getNextToken(f,tb);
	printf("%s     1\n",lookahead->token_name);
	if(strcmp(lookahead->token_name,"a")==0)
	{
		proc_a();
		lookahead=getNextToken(f,tb);
		if(strcmp(lookahead->token_name,"c")==0)
		{
			proc_b();
			printf("%s     5\n",lookahead->token_name);
			lookahead=getNextToken(f,tb);
			if(strcmp(lookahead->token_name,"e")==0)
			{
				
			printf("%s     5\n",lookahead->token_name);
				return;

			}
			else
				printf("Error1\n");
		}
		else
			printf("Error2\n");
	}
	else
		printf("Error4\n");

}


int main()
{
	lookahead=malloc(sizeof(struct TOKEN));
	tb=(Table*)malloc(sizeof(struct TABLE));
	
	f=fopen("input.txt","r");
	// lookahead=getNextToken(f,tb);
	proc_s();
	lookahead=getNextToken(f,tb);
	if(strcmp(lookahead->token_name,"$")==0)// if(strcmp(lookahead->token_name,"EOL")==0)
		printf("\nSuccessful");
	else
		printf("\nError3");
	return 0;
}