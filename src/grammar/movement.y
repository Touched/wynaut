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
#include <vector>
#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>
#include "../compiler/Script.hpp"

extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

void moveerror(const char *s);

using namespace std;

%}

%union {
	int value;
	char *string;
}

%define api.prefix {move};

%token <value> T_CONSTANT
%token <string> T_IDENTIFIER
%token T_NEWLINE

%%
program
	: optional_linebreaks statements optional_linebreaks
	;

optional_linebreaks
	:
	| linebreaks
	;

statements
	: statement
	| statements end statement
	;
end
	: linebreaks
	| ','
	| ';'
	;

linebreaks
	: '\n'
	| linebreaks '\n'
	;

statement
	: direction qualifier quantifier
	| direction qualifier
	| direction quantifier
	| qualifier quantifier
	| qualifier
	| direction
	;

direction
	: T_IDENTIFIER
	;

qualifier
	: T_IDENTIFIER
	;

quantifier
	: T_CONSTANT
	;

%%

int parse_movements(const char *filename) {
	// Open the file and check for errors
	FILE *file = fopen(filename, "r");
	if (!file) {
		cout << "Can't open it" << endl;
		return -1;
	}

	// Lex from file handle instead of stdin
	yyin = file;

	// Parse
	do {
		moveparse();
	} while (!feof(yyin));
}

extern int yylineno;

void moveerror(const char *s) {
	cout << yylineno << " EEK, parse error!  Message: " << s << endl;

	// might as well halt now:
	exit(-1);
}
