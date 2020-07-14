#include<stdio.h>
#include<stdlib.h>
#include"lexl.c"
#include<ctype.h>
#define error printf("invalid input\n");
#define success printf("valid\n");

void S();
void T();
void T_();

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
            //display(head);
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
          else if(ca=='\t')
        {
            colc=colc+4;
        }
        else
        {
            //printf("\n%c\n",ca);
            t1=getNextToken(fp);
            //printf("<%s,%d,%d,%s>\n",t1.lex,t1.row,t1.col,t1.type);
            fprintf(fp1,"%s\n",t1.type);
            head=newnode(head,t1);

        }
        
        ca=getc(fp);
        
        
    }
    
}

void S(){
    // S -> a
    if(!strcmp(lookahead->tok.lex,"a")){
        match("a");
    } else if(!strcmp(lookahead->tok.lex,">")){
        match(">");
    }else if(!strcmp(lookahead->tok.lex,"(")){
        match("(");
        T();
        match(")");
    }
}

void T_(){
    if(!strcmp(lookahead->tok.lex,",")){
        match(",");
        S();
        T_();
    }
    else 
        return ;
}

void T(){
    S();
    T_();
}
