#include<stdio.h>
#include<ctype.h>
#include "token.h"
#include<string.h>

Token lookahead;
int i=0;
FILE *f;
Table *tb;

void proc_lexp_seq();
void proc_lexp_seqd()
{
	lookahead=getNextToken(f,tb);
	if(strcmp(lookahead->token_name,"num")==0 || strcmp(lookahead->token_name,"id")==0)
	{
		proc_lexp_seqd();
	}
	else if(strcmp(lookahead->token_name,"(")==0)
	{
		proc_lexp_seq();
		lookahead=getNextToken(f,tb);
		if(strcmp(lookahead->token_name,")")==0)
			proc_lexp_seqd();
		else
			printf("Error2");
	}
	else
		fseek(f,-strlen(lookahead->token_name),SEEK_CUR);
}	



void proc_lexp()
{
	lookahead=getNextToken(f,tb);
	if(strcmp(lookahead->token_name,"num")==0 || strcmp(lookahead->token_name,"id")==0)
		return;
	else if(strcmp(lookahead->token_name,"(")==0)
	{
		proc_lexp_seq();
		lookahead=getNextToken(f,tb);
		if(strcmp(lookahead->token_name,")")==0)
			return;
		else
			printf("Error1");
	}
	else
		printf("Error4\n");
}

void proc_lexp_seq()
{
	proc_lexp();
	proc_lexp_seqd();
}

int main()
{
	lookahead=malloc(sizeof(struct TOKEN));
	tb=(Table*)malloc(sizeof(struct TABLE));
	
	f=fopen("input.txt","r");
	// lookahead=getNextToken(f,tb);
	proc_lexp();
	lookahead=getNextToken(f,tb);
	if(strcmp(lookahead->token_name,"$")==0)// if(strcmp(lookahead->token_name,"EOL")==0)
		printf("\nSuccessful");
	else
		printf("\nError3");
	return 0;
}