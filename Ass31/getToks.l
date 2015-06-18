%{
#include<stdio.h>
#include<string.h> 
#define YYSTYPE char*
#include "y.tab.h"
%}
ud [_]
letter [a-zA-Z]
number [0-9]
%%
int {return TOKINT;}
float {return TOKFLOAT;}
char {return TOKCHAR;}  
void {return TOKVOID;}
while {return TOKWHILE;}            
for {return TOKFOR;}
if {return TOKIF;}
else {return TOKELSE;}
return {return TOKRETURN;}
{ud}*{letter}({letter}|{number})*   {yylval=strdup(yytext);return TOKNAME;}
{number}+ return NUMBER;
;       return SEMICOLON;
,       return COMMA;
"="    return EQUAL;
"+"    return PLUS;
"-"    return MINUS;
"*"    return MULT;
"/"    return DIV;
"%"    return MOD;
"++"   return INC;
"--"   return DEC; 
"&&"   return AND;
"||"   return OR;
"!"    return NOT;
">"	return GREATERTHAN;
"<" 	return LESSTHAN;
"<="    return LESSTHANEQUAL;
">="	return GREATERTHANEQUAL;
"!="   return NOTEQUAL;
"=="   return COMPEQUAL;
"("    return OPENPAREN;
")"    return CLOSEPAREN;
"{"    return OPENBRACE;
"}"    return CLOSEBRACE;
. ;
%%


