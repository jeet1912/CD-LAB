#include<stdio.h>
#include<ctype.h>
#include "token.h"
#include<string.h>

Token lookahead;
int i=0;
FILE *f;
Table *tb;
void proc_t();
void proc_e()
{
	lookahead=getNextToken(f,tb);
	printf("%s+\n",lookahead->token_name);
	if(strcmp(lookahead->token_name,"NUMBER")==0)
	{
		// printf("%d\n",lookahead->type);
		// lookahead=getNextToken(f,tb);
		proc_t();
	}
	else
	{
		printf("\nError1");
	}
}

void proc_t()
{
	lookahead=getNextToken(f,tb);
	// if(strcmp(lookahead->token_name,"$")==0)
	// 	return;
	if(strcmp(lookahead->token_name,"*")==0)
	{
		printf("%s\n",lookahead->token_name);
		lookahead=getNextToken(f,tb);
		if(strcmp(lookahead->token_name,"NUMBER")==0)
		{
			printf("%s\n",lookahead->token_name);
			// lookahead=getNextToken(f,tb);
			proc_t();
		}
		else
		{
			printf("Error2\n");
		}
	}
}

int main()
{
	lookahead=malloc(sizeof(struct TOKEN));
	tb=(Table*)malloc(sizeof(struct TABLE));
	
	f=fopen("input.txt","r");
	// lookahead=getNextToken(f,tb);
	proc_e();
	if(strcmp(lookahead->token_name,"$")==0)// if(strcmp(lookahead->token_name,"EOL")==0)
		printf("\nSuccessful");
	else
		printf("\nError3");
	return 0;
}