%{ 
#include<stdio.h> 
#include<string.h>  
#include<stdlib.h>
int a,b=0;
%} 
  
/* Rules Section*/
%% 
"scanf" {a++;fprintf(yyout,"%s","READ");}
"printf" {b++;fprintf(yyout,"%s","WRITE");}
\n {fprintf(yyout,"%s","\n");}
. {fprintf(yyout,"%s",yytext);}
%% 
  
int yywrap(void){} 
  
int main() 
{    
    // The function that starts the analysis
    yyin=fopen("Input.txt","r");
    yyout = fopen("Output.txt", "w"); 
    yylex(); 
    printf("No of scanf : %d\n",a);
    printf("No of printf : %d\n",b);
    return 0; 
}    