%{
int yylex();
void yyerror();
%}
%{
#include <stdio.h>
#include <stdlib.h>
int id=0, key=0, op=0;
%}
%token ID KEY OP
%%
input: ID input { id++; }
| KEY input { key++; }
| OP input {op++;}
| ID { id++; }
| KEY
| OP
;
%%
extern FILE *yyin;
void main(int argc ,char** argv)
{
yyin = fopen(argv[1],"r");
yyparse();
printf("Keywords = %d\nIdentifiers = %d\noperators = %d\n", key,id, op);
}
void yyerror()
{
printf("Not valid");
}
