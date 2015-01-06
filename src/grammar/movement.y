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

extern "C" int movelex();
extern "C" int moveparse();
extern "C" FILE *movein;

void moveerror(const char *s);

using namespace std;

const char *last;

%}

%union {
	int value;
	char *string;
}

%define api.prefix {move};

%token <value> T_CONSTANT
%token <string> T_IDENTIFIER
%token T_NEWLINE

%type <value> quantity

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
	;

linebreaks
	: T_NEWLINE
	| linebreaks T_NEWLINE
	;

statement
	: quantity T_IDENTIFIER T_IDENTIFIER {
		cout << $1 << " " << $2 << " " << $3 << endl;
	}
	| quantity T_IDENTIFIER {
		cout << $1 << " " << $2 << endl;
	}
	;

quantity
	: { $$ = 1; /* Default to 1 */ }
	| T_CONSTANT { $$ = $1; }
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
	movein = file;

	// Parse
	do {
		moveparse();
	} while (!feof(movein));
}

extern int yylineno;

void moveerror(const char *s) {
	cout << yylineno << " EEK, parse error!  Message: " << s << endl;

	// might as well halt now:
	exit(-1);
}
