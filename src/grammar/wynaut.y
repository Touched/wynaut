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

#include "wynaut.h"

using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

int current_line_indent = 0;
int indent_level = 0;

void yyerror(const char *s);

int solve(operator_type op, int lhs, int rhs);
int solve(operator_type op, int lhs);

// TODO: In init function
// TODO: Fix memory leaks when not lazy (they're all in the Bison/Flex source)
compiler::Script script;

%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":

%union {
	int ival;
	float fval;
	char *sval;

	char *string;

	struct funcname *func;

	lang::Arguments *args;
	lang::Argument *arg;
	lang::Condition *condition;
	std::vector<std::string> *parameters;

	operator_type op;

	condition_type cond;

	lang::Expression *expression;

	int value;
}

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING

%token USING
%token IF ELSE ELSE_IF WHILE BREAK CONTINUE END
%token RETURN END_SCRIPT
%token SUBROUTINE
%token AS
%token <string> IDENTIFIER
%token <func> FUNCNAME
%token <value> CONSTANT
%token <string> STRING_LITERAL
%token ENDL
%token DIALECT

%token OP_ASSIGN OP_ASSIGN_ADD OP_ASSIGN_SUB OP_ASSIGN_MUL OP_ASSIGN_DIV
%token OPERATOR_EQ OPERATOR_LT OPERATOR_GT OPERATOR_GEQ OPERATOR_LEQ OPERATOR_NEQ

%type <args> arguments
%type <arg> argument
%type <op> binary_operator unary_operator
%type <cond> conditional_operator
%type <expression> expression
%type <condition> condition
%type <parameters> parameter_list parameters

%%
script
	: OPTIONAL_NEWLINE dialect NEWLINE imports NEWLINE declarations NEWLINE subroutines OPTIONAL_NEWLINE
	| OPTIONAL_NEWLINE dialect NEWLINE imports NEWLINE subroutines OPTIONAL_NEWLINE
	| OPTIONAL_NEWLINE dialect NEWLINE declarations NEWLINE subroutines OPTIONAL_NEWLINE
	| OPTIONAL_NEWLINE dialect NEWLINE subroutines OPTIONAL_NEWLINE
	;

dialect
	: DIALECT IDENTIFIER { cout << "Dialect chosen: " << $2 << endl; /* dialect = new lang::Dialect(); */ }
	;

imports
	: import_statement
	| imports NEWLINE import_statement
	;

declarations
	: identifier_declaration
	| declarations NEWLINE identifier_declaration
	;

identifier_declaration
	: IDENTIFIER CONSTANT AS IDENTIFIER { script.declare($4, $1, $2); }
	;

import_statement
	: USING IDENTIFIER { script.import($2); }
	;

subroutines
	: subroutine
	| subroutines NEWLINE subroutine
	;

subroutine
	: subroutine_declaration NEWLINE statements END {
	}
	;

subroutine_declaration
	: SUBROUTINE IDENTIFIER parameters  {
		script.handleSubroutine($2, $3);
		delete $3;
	}
	;

parameters
	: '(' parameter_list ')' {
		$$ = $2;
	}
	;

parameter_list
	: {
		$$ = new std::vector<std::string>();
	}
	| IDENTIFIER {
		$$ = new std::vector<std::string>();
		$$->push_back($1);
	}
	| parameter_list ',' IDENTIFIER {
		$$->push_back($3);
	}
	;

statements
	: statement NEWLINE
	| statements statement NEWLINE
	;

statement
	: compound_statement
	| simple_statement
	;

simple_statement
	: IDENTIFIER assign_operator expression {
		// TODO: Allow script to handle this
		cout << "wh " << *$3 << endl;
		delete $3;
	}
	| function_call
	| BREAK
	| CONTINUE
	;

function_call
	: IDENTIFIER '(' arguments ')' {
		script.handleFunction($1, *$3);
		delete $3;
		free($1);
	}
	| FUNCNAME '(' arguments ')' {
		script.handleFunction($1->module, $1->function, *$3);
		free($1->module);
		delete $3;
	}
	;

arguments
	: {
		// No arguments
		$$ = new lang::Arguments();
	}
	| argument {
		// Create a new arguments object and add the value
		$$ = new lang::Arguments();
		$$->add($1);
	}
	| arguments ',' argument {
		$$->add($3);
	}
	;

argument
	: expression {
		if ($1->isConstant()) {
			$$ = lang::Argument::create(*$1);
			delete $1;
		}
		else {
			// TODO: Resolve to a 'Type' argument rather than making a 'String' argument
			$$ = lang::Argument::create($1->toString());
			delete $1;
		}
	}
	| STRING_LITERAL {
		$$ = lang::Argument::create($1);
		free($1);
	}
	;

expression
	: CONSTANT { $$ = new lang::Expression($1); }
	| IDENTIFIER {
		try {
			$$ = new lang::Expression(script.resolveConstant($1));
		} catch (const char *e) {
			$$ = new lang::Expression($1);
		}
	}
	| unary_operator expression {
		$$ = new lang::Expression(solve($1, *$2));
	}
	| expression binary_operator expression {
		$$ = new lang::Expression(solve($2, *$1, *$3));
	}
	| '(' expression ')' {
		$$ = $2;
	}
	;

unary_operator
	: '+' { $$ = OP_PLUS; }
	| '-' { $$ = OP_MINUS; }
	;

binary_operator
	: '+' { $$ = OP_PLUS; }
	| '-' { $$ = OP_MINUS; }
	| '*' { $$ = OP_MULTIPLY; }
	| '/' { $$ = OP_DIVIDE; }
	;

assign_operator
	: OP_ASSIGN
	| OP_ASSIGN_ADD
	| OP_ASSIGN_MUL
	| OP_ASSIGN_DIV
	| OP_ASSIGN_SUB
	;

compound_statement
	: while_block
	| if_block
	;

if_block
	: if_statement END { script.handleEndIf(); }
	| if_statement else_statement END { script.handleEndIf(); }
	| if_statement else_if_statement END { script.handleEndIf(); }
	| if_statement else_if_statement else_statement END { script.handleEndIf(); }
	;

if_statement
	: IF condition NEWLINE statements {
		script.handleIf(*$2);
		delete $2;
	}
	;

else_if_statement
	: ELSE_IF condition NEWLINE statements {
		script.handleElseIf(*$2);
        delete $2;
	}
	| else_if_statement ELSE_IF condition NEWLINE statements {
		script.handleElseIf(*$3);
        delete $3;
	}
	;

else_statement
	: ELSE NEWLINE statements {
		script.handleElse();
	}
	;

while_block
	: WHILE condition NEWLINE statements END {
		script.handleWhile(*$2);
        delete $2;
	}
	;

condition
	: expression conditional_operator expression { $$ = new lang::Condition((lang::Condition::Operator) $2, $3, $1); }
	| conditional_operator expression { $$ = new lang::Condition((lang::Condition::Operator) $1, $2); }
	| expression { $$ = new lang::Condition($1); }
	;

conditional_operator
	: OPERATOR_EQ { $$ = OP_EQ; }
	| OPERATOR_NEQ { $$ = OP_NEQ; }
	| OPERATOR_GT { $$ = OP_GT; }
	| OPERATOR_GEQ { $$ = OP_GEQ; }
	| OPERATOR_LT { $$ = OP_LT; }
	| OPERATOR_LEQ { $$ = OP_LEQ; }
	;

NEWLINE
	: ENDL
	| NEWLINE ENDL
	;

OPTIONAL_NEWLINE
	: NEWLINE
	|
	;
%%

main() {
	// open a file handle to a particular file:
	FILE *myfile = fopen("/home/james/tests/a.snazzle.file", "r");
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
}

extern int yylineno;

void yyerror(const char *s) {
	cout << yylineno << " EEK, parse error!  Message: " << s << endl;

	// might as well halt now:
	exit(-1);
}

int solve(operator_type op, int lhs) {
	switch (op) {
	case OP_PLUS:
		return +lhs;
	case OP_MINUS:
		return -lhs;
	}
}

int solve(operator_type op, int lhs, int rhs) {
	switch (op) {
	case OP_PLUS:
		return lhs + rhs;
	case OP_MINUS:
		return lhs - rhs;
	case OP_MULTIPLY:
		return lhs * rhs;
	case OP_DIVIDE:
		return lhs / rhs;
	}
}