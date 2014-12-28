%{
#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>
#include "../compiler/Script.hpp"

#include "../language/Dialect.hpp"

using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

int current_line_indent = 0;
int indent_level = 0;

void yyerror(const char *s);

struct node {
	void *data;
	struct node *next;
};

struct funcname {
	char *module;
	char *function;
};

std::unordered_map<std::string, lang::Type> symbols;
lang::Dialect *dialect;

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
%token STRING_LITERAL
%token ENDL
%token DIALECT

%token OP_ASSIGN OP_ASSIGN_ADD OP_ASSIGN_SUB OP_ASSIGN_MUL OP_ASSIGN_DIV

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
	: IDENTIFIER CONSTANT AS IDENTIFIER { cout << $1 << " " << $2 << " " << $4 << endl; /* symbols[$4] = dialect->createType($1, $2); */ }
	;

import_statement
	: USING IDENTIFIER { printf("Importing '%s'\n", $2); }
	;

subroutines
	: subroutine
	| subroutines NEWLINE subroutine
	;

subroutine
	: SUBROUTINE IDENTIFIER parameters NEWLINE statements END { cout << $2 << endl; }
	;

parameters
	: '(' parameter_list ')' { cout << endl; }
	| '(' ')' { cout << "No parameters" << endl; }
	;

parameter_list
	: IDENTIFIER { cout << $1 << " "; }
	| parameter_list ',' IDENTIFIER { cout << $3 << " ";  }
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
	: IDENTIFIER assign_operator expression
	| function_call
	;

function_call
	: IDENTIFIER '(' arguments ')'
	| FUNCNAME '(' arguments ')' { cout << "Calling " << $1->module << "::" << $1->function << endl; }
	;

arguments
	:
	| argument
	| arguments ',' argument
	;

argument
	: IDENTIFIER
	| CONSTANT
	| STRING_LITERAL
	;

expression
	: CONSTANT
	| IDENTIFIER
	| unary_operator expression
	| expression binary_operator expression
	| '(' expression ')'
	;

unary_operator
	: '+'
	| '-'
	;

binary_operator
	: '+'
	| '-'
	| '*'
	| '/'
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
	: if_statement END
	| if_statement else_statement END
	| if_statement else_if_statement END
	| if_statement else_statement else_if_statement END
	;

if_statement
	: IF condition NEWLINE statements
	;

else_if_statement
	: ELSE_IF condition NEWLINE statements
	| else_if_statement ELSE_IF condition NEWLINE statements
	;

else_statement
	: ELSE NEWLINE statements
	;

while_block
	: WHILE condition NEWLINE statements END
	;

condition
	: expression
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