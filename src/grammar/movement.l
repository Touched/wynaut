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

%%

\#.* /* comment */
\n { return T_NEWLINE; }
[A-Za-z_][A-Za-z0-9_]* { yylval.id = yytext; return T_IDENTIFIER; }
0[oO][0-7]+ {  yylval.value = strtol(yytext + 2, NULL, 8); return T_CONSTANT; }
0[xX][0-9a-fA-F]+ {  yylval.value = strtol(yytext, NULL, 16); return T_CONSTANT; }
0[bB][01]+ {  yylval.value = strtol(yytext + 2, NULL, 2); return T_CONSTANT; }
[0-9]+ { yylval.value = strtol(yytext, NULL, 10); return T_CONSTANT; }

%%