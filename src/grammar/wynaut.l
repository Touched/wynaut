/*
This file is part of Wynaut.

Wynaut is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Wynaut is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Wynaut.  If not, see <http://www.gnu.org/licenses/>.
*/

IDENT [_a-zA-z][_a-zA-Z0-9]*

%{
#include <cstdio>
#include <iostream>
#include <vector>
#include "wynaut.h"
using namespace std;
#define YY_DECL extern "C" int yylex()

#include "wynautParser.hpp"

%}

%option warn
%option nodefault
%option yylineno
%option noyywrap

%x COMMENT_STATE

%%

<INITIAL>"/*" BEGIN(COMMENT_STATE);
<COMMENT_STATE>{
"*/"      BEGIN(INITIAL);
[^*\n]+   // eat comment in chunks
"*"       // eat the lone star
\n        yylineno++;
}

\#.* /* comment */

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

\"(\\.|[^\\"])*\"	{ yylval.string = strdup(yytext); return(STRING_LITERAL); }
\'(\\.|[^\\'])*\'	{ yylval.string = strdup(yytext); return(STRING_LITERAL); }

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

"==" { return OPERATOR_EQ; }
"!=" { return OPERATOR_NEQ; }
">=" { return OPERATOR_GEQ; }
">" { return OPERATOR_GT; }
"<" { return OPERATOR_LT; }
"<=" { return OPERATOR_LEQ; }


\n             { return ENDL; }
[ \v\t] ;
.	printf("bad input character '%s' at line %d\n", yytext, yylineno);
%%