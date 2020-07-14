%{
	#include<stdio.h>
	#include<string.h>
	int flag = 0;
%}

%%
(and|or|if) flag = 1;
%%

int yywrap(void){}

int main()
{
	yylex();
	if(flag)
		printf("Compound !!:)!!\n");
	else
		printf("Simp  !!:(!\n");
	return 0;
}