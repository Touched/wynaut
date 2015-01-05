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

using namespace std;

%union {
	int value;
	char *string;
}

%token <value> T_CONSTANT
%token <string> T_IDENTIFIER
%token NEWLINE

%%

program
	: optional_linebreaks statements optional_linebreaks
	;

optional_linebreaks:
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

main() {
	try {
		// open a file handle to a particular file:
		FILE *myfile = fopen("../../tests/test.mov", "r");
		// make sure it is valid:
		if (!myfile) {
			cout << "I can't open a.snazzle.file!" << endl;
			return -1;
		}
		// set flex to read from it instead of defaulting to STDIN:
		yyin = myfile;

		// parse through the input until there is no more:
		do {
			yyparse();
		} while (!feof(yyin));
	} catch (const char *e) {
		cerr << "Error: " << e << endl;
	}
}