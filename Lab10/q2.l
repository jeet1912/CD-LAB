%{ 
#include<stdio.h> 
#include<string.h> 
int w = 0;
int c = 0;
int b = 0;
int l = 0; 
%} 
  
/* Rules Section*/
%% 
[a-zA-Z]* {w++;c+=strlen(yytext);}
[ ] {b++;}
\t {b+=4;}
\n {l++;} 
%% 
  
int yywrap(void){} 
  
int main() 
{    
    // The function that starts the analysis 
    yylex(); 
    printf("Words : %d\n",w);
    printf("Charaters : %d\n",c);
    printf("Blanks : %d\n",b);
    printf("Lines : %d\n",l);
    return 0; 