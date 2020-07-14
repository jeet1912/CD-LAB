%{ 
#include<stdio.h> 
#include<string.h> 
int pi = 0;
int ni = 0;
int pf = 0;
int nf = 0; 
%} 
  
/* Rules Section*/
%% 
[+]?[0-9]* {pi++;}
-[0-9]* {ni++;}
[+]?[0-9]*\.[0-9]* {pf++;}
-[0-9]*\.[0-9]* {nf++;}
[ ] {}
\n {}
. {} 
%% 
  
int yywrap(void){} 
  
int main() 
{    
    // The function that starts the analysis 
    yylex(); 
    printf("Positive integers : %d\n",pi);
    printf("Negative integers : %d\n",ni);
    printf("Positive floats : %d\n",pf);
    printf("Negative floats : %d\n",nf);
    return 0; 
}    