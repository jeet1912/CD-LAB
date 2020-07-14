#include<stdio.h>
#include<stdlib.h>
#include"lexl.c"
#include<ctype.h>
#define error printf("invalid input\n");
#define success printf("valid\n");

void E();
void E_();
void F();
void T();
void T1();

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

            
            E();

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
            //printf("\n%c\n",ca);
            t1=getNextToken(fp);
            //printf("<%s,%d,%d,%s>\n",t1.lex,t1.row,t1.col,t1.type);
            fprintf(fp1,"%s\n",t1.type);
            head=newnode(head,t1);

        }
        
        ca=getc(fp);
        
        
    }
    
}

void E(){
    T();
    E_();
}

void E_(){
    if(strcmp(lookahead->tok.lex,"+") == 0){
        match("+");
        T();
        E_();
    }
    else 
        return ;
}

void T_(){
    if(strcmp(lookahead->tok.lex,"*") == 0){
        match("*");
        F();
        T_();
    }
    else 
        return ;
}

void T(){
    F();
    T_();
}

void F() {
    if(strcmp(lookahead->tok.lex,"(") == 0){
        match("(");
        E();
        match(")");
    } 
    else if(!strcmp(lookahead->tok.type,"Identifier")){
        lookahead=lookahead->next;
    
    }
    else 
        printf("error at %s\n",lookahead->tok.lex);
}