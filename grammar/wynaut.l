IDENT [_a-zA-z][_\-a-zA-Z0-9]*

%{
#include <cstdio>
#include <iostream>
using namespace std;
#define YY_DECL extern "C" int yylex()

#include "wynaut_parser.hpp"  // to get the token types that we return

struct funcname {
	char *module;
	char *function;
};

%}

%option warn
%option nodefault
%option yylineno
%option noyywrap

%%

"using" { return USING; }

"if" { return IF; }
"else" { return ELSE; }
"elif" { return ELSE_IF; }
"while" { return WHILE; }
"break" { return BREAK; }
"continue" { return CONTINUE; }
"end" { return END; }

"dialect" { return DIALECT; }

"as" { return AS; }
"sub" { return SUBROUTINE; }

"exit" { return END_SCRIPT; }
"return" { return RETURN; }

{IDENT} { yylval.string = strdup(yytext); return IDENTIFIER; }
{IDENT}\.{IDENT} { yylval.func->module = strtok(strdup(yytext), "."); yylval.func->function = strtok(NULL, "."); return FUNCNAME; }

\"(\\.|[^\\"])*\"	{ return(STRING_LITERAL); }
\'(\\.|[^\\'])*\'	{ return(STRING_LITERAL); }

\( { return '('; }
\) { return ')'; }
\, { return ','; }

0[oO][0-7]+ {  yylval.value = strtol(yytext + 2, NULL, 8); return CONSTANT; }
0[xX][0-9a-fA-F]+ {  yylval.value = strtol(yytext, NULL, 16); return CONSTANT; }
0[bB][01]+ {  yylval.value = strtol(yytext + 2, NULL, 2); return CONSTANT; }
[0-9]+ { yylval.value = strtol(yytext, NULL, 10); return CONSTANT; }

\+ { return '+'; }
\- { return '-'; }
\* { return '*'; }
\/ { return '/'; }

\= { return OP_ASSIGN; }
"+=" { return OP_ASSIGN_ADD; }
"-=" { return OP_ASSIGN_SUB; }
"*=" { return OP_ASSIGN_MUL; }
"/=" { return OP_ASSIGN_DIV; }


\n             { return ENDL; }
[ \v\t] ;
.	printf("bad input character '%s' at line %d\n", yytext, yylineno);
%%