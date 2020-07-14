#include<stdio.h>
#include<stdlib.h>
#include"lexl.c"
#include<ctype.h>
#define error printf("invalid input\n");
#define success printf("valid\n");

void S();
void A();
void A1();
void B();

FILE *fp;
nodeptr lookahead;

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
            strcpy(t1.lex,"EOF");
            strcpy(t1.type,"EOF");
            t1.col=-1;
            t1.row=-1;

            head=newnode(head,t1);
            display(head);

            lookahead=head;

            
            S();

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
        /*else if(ca=='/')
        {
            ca=getc(fp);
            if(ca=='/')
            {
                ca=getc(fp);
                while(ca!='\n')
                {
                    ca=getc(fp);
                }
                linec++;
                colc=1;
                //ca=getc(fp);
            }
            
            else
            {
                ungetc(ca,fp);//ca=getc(fp);
                
            }
        }*/
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

void S(){
    match("a");
    A();
    match("c");
    B();
    match("e");
}

void A1(){
    if(!strcmp(lookahead->tok.lex,"b")){
        match("b");
        A1();
    }
    else 
        return ;
}

void A(){
    match("b");
    A1();
}

void B(){
    match("d");
}