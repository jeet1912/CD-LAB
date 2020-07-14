#include<stdio.h>
#include<stdlib.h>
#include"lexl.c"
#include<ctype.h>
#define error printf("invalid input\n");
#define success printf("valid\n");

void lexp();
void aterm();
void list();
void lexp_seq();
void lexp_seq1();

nodeptr lookahead;
FILE *fp;

void match(char str[]){
	if(strcmp(lookahead->tok.lex,str) == 0)
		lookahead=lookahead->next;
	else 
		printf("Error at %s\n",lookahead->tok.lex);
}

int main()
{
	fp=fopen("input.txt","r");
	FILE *fp1=fopen("out.txt","w");
	token t1;
	nodeptr head=NULL;
	ca=getc(fp);
	while(1)
	{
		if(ca==EOF)
		{
			//display(head);
			strcpy(t1.lex,"EOF");
			strcpy(t1.type,"EOF");
			t1.col=-1;
			t1.row=-1;

			head=newnode(head,t1);
			display(head);

			lookahead=head;

			
			lexp();

			if(!strcmp(lookahead->tok.lex,"$"))
			{
				success;
			}
			else 
				error;
			
			return 0;
		}
		else if(ca=='\n')
		{
			linec++;
			colc=1;
		}
		else if(ca==' ')
		{
			colc++;
		}
		else if(ca=='#')
		{
			while(ca!='\n')
			{
				ca=getc(fp);
			}

			linec++;
			colc=1;
		}
		
		else if(ca=='\t')
		{
			colc=colc+4;
		}
		else
		{
			t1=getNextToken(fp);
			fprintf(fp1,"%s\n",t1.type);
			head=newnode(head,t1);
		}
		
		ca=getc(fp);
		
		
	}
	
}


void lexp(){
	if((!strcmp(lookahead->tok.type,"Number")) || (!strcmp(lookahead->tok.type,"Identifier")))
		aterm();
	else 
		list();
}

void aterm(){
	if((!strcmp(lookahead->tok.type,"Number")) || (!strcmp(lookahead->tok.type,"Identifier")))
		lookahead=lookahead->next;
	
	else 
		printf("Error at %s\n",lookahead->tok.lex);
}

void list(){
	match("(");
	lexp_seq();
	match(")");
}

void lexp_seq(){
	lexp();
	lexp_seq1();
}

void lexp_seq1() {
	if((!strcmp(lookahead->tok.type,"Number")) || (!strcmp(lookahead->tok.type,"Identifier"))){
		lexp();
		lexp_seq1();
	}
	else 
		return ;
}