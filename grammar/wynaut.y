%{
#include <vector>
#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>
#include "../compiler/Script.hpp"
#include "../util/Expression.hpp"
#include "../util/Arguments.hpp"

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

enum operator_type {
	OP_PLUS,
	OP_MINUS,
	OP_DIVIDE,
	OP_MULTIPLY
};

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

	util::Arguments *args;
	util::Argument *arg;

	operator_type op;

	grammar::Expression *expression;

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

%type <args> arguments
%type <arg> argument
%type <op> binary_operator unary_operator
%type <expression> expression

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
	: IDENTIFIER assign_operator expression { cout << "wh " << *$3 << endl; }
	| function_call
	;

function_call
	: IDENTIFIER '(' arguments ')' {
		script.handleFunction($1, $3);
		delete $3;
		free($1);
	}
	| FUNCNAME '(' arguments ')' {
		script.handleFunction($1->module, $1->function, $3);
		free($1->module);
		delete $3;
	}
	;

arguments
	: {
		// No arguments
		$$ = new util::Arguments();
	}
	| argument {
		// Create a new arguments object and add the value
		$$ = new util::Arguments();
		$$->add($1);
	}
	| arguments ',' argument {
		$$->add($3);
	}
	;

argument
	: expression {
		if ($1->isConstant()) {
			$$ = util::Argument::create(*$1);
			delete $1;
		}
		else {
			// TODO: Resolve to a 'Type' argument rather than making a 'String' argument
			$$ = util::Argument::create($1->toString());
			delete $1;
		}
	}
	| STRING_LITERAL {
		$$ = util::Argument::create($1);
		free($1);
	}
	;

expression
	: CONSTANT { $$ = new grammar::Expression($1); }
	| IDENTIFIER {
		try {
			$$ = new grammar::Expression(script.resolveConstant($1));
		} catch (const char *e) {
			$$ = new grammar::Expression($1);
		}
	}
	| unary_operator expression {
		$$ = new grammar::Expression(solve($1, *$2));
	}
	| expression binary_operator expression {
		$$ = new grammar::Expression(solve($2, *$1, *$3));
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
	: if_statement END
	| if_statement else_statement END
	| if_statement else_if_statement END
	| if_statement else_statement else_if_statement END
	;

if_statement
	: IF condition NEWLINE statements {
		cout << "IF" << endl;
	}
	;

else_if_statement
	: ELSE_IF condition NEWLINE statements {
		cout << "ELSEIF" << endl;
	}
	| else_if_statement ELSE_IF condition NEWLINE statements {
		cout << "ELSEIF" << endl;
	}
	;

else_statement
	: ELSE NEWLINE statements {
		cout << "ELSE" << endl;
	}
	;

while_block
	: WHILE condition NEWLINE statements END {
		cout << "WHILE" << endl;
	}
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