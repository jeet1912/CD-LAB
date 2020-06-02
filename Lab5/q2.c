#include<stdio.h>
#include<ctype.h>
#include "token.h"
#include<string.h>

Token lookahead;
int i=0;
FILE *f;
Table *tb;
void proc_e();
void proc_ed();
void proc_t();
void proc_td();
void proc_f();


void proc_ed()
{
	lookahead=getNextToken(f,tb);
	printf("%s3\n",lookahead->token_name);
	if(strcmp(lookahead->token_name,"+")==0)
	{
		proc_t();
		proc_ed();
	}
	else
		fseek(f,-strlen(lookahead->token_name),SEEK_CUR);
}

void proc_f()
{
	lookahead=getNextToken(f,tb);
	printf("%s2 bvc\n",lookahead->token_name);
	if(strcmp(lookahead->token_name,"(")==0)
	{
		proc_e();
		lookahead=getNextToken(f,tb);
		if(strcmp(lookahead->token_name,")")==0)
			return;
		else
			printf("Error2\n");
	}
	else if(strcmp(lookahead->token_name,"id")==0)
		return;
	else
		printf("Error33\n");
}

void proc_td()
{
	lookahead=getNextToken(f,tb);
	printf("%s1%d\n",lookahead->token_name,strlen(lookahead->token_name));
	if(strcmp(lookahead->token_name,"*")==0)
	{
		proc_f();
		proc_td();
	}
	else
		fseek(f,-1,SEEK_CUR);
}
void proc_t()
{
	proc_f();
	proc_td();
}

void proc_e()
{
	proc_t();
	proc_ed();
}



int main()
{
	lookahead=malloc(sizeof(struct TOKEN));
	tb=(Table*)malloc(sizeof(struct TABLE));
	
	f=fopen("input.txt","r");
	// lookahead=getNextToken(f,tb);
	proc_e();
	lookahead=getNextToken(f,tb);
	if(strcmp(lookahead->token_name,"$")==0)// if(strcmp(lookahead->token_name,"EOL")==0)
		printf("\nSuccessful");
	else
		printf("\nError3");
	return 0;
}