#include<stdio.h>
#include<ctype.h>
#include "token.h"
#include<string.h>

Token lookahead;
int i=0;
FILE *f;
Table *tb;
void proc_s();
void proc_t();
void proc_td();

void proc_td()
{
	lookahead=getNextToken(f,tb);printf("%sh\n",lookahead->token_name);
	if(strcmp(lookahead->token_name,",")==0)
	{
		proc_s();
		proc_td();
	}
	else
		fseek(f,-strlen(lookahead->token_name),SEEK_CUR);//printf("Error3\n");
}

void proc_t()
{
	proc_s();
	proc_td();
}

void proc_s()
{
	lookahead=getNextToken(f,tb);
	// if(strcmp(lookahead->token_name,"$")==0)
	// 	return;
	printf("%s+\n",lookahead->token_name);
	if(strcmp(lookahead->token_name,"a")==0)
	{
		return;
	}
	else if(strcmp(lookahead->token_name,">")==0)
	{
		return;
	}
	else if(strcmp(lookahead->token_name,"(")==0)
	{
		proc_t();
		lookahead=getNextToken(f,tb);
		printf("%ss\n",lookahead->token_name);
		if(strcmp(lookahead->token_name,")")==0)
			return;
		else
			printf("Error2\n");
	}
	else
		printf("Error1\n");
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