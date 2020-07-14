%{ 
#include<stdio.h> 
#include<string.h> 
int v = 0;
int c = 0; 
%} 
  

%% 
([aeiou])    {v++;}
([qwrtypsdfghjklzxcvbnm])  {c++;} 
%% 
  
int yywrap(void){} 
  
int main() 
{    
    // The function that starts the analysis 
    yylex(); 
    printf("Vovels : %d\n",v);
    printf("Consonants : %d\n",c);
    return 0; 
}    