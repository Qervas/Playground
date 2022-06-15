/*
 * @Author: FrankTudor
 * @Date: 2022-06-04 18:36:32
 * @LastEditors: FrankTudor
 * @Description: This file is created, edited, contributed by FrankTudor
 * @LastEditTime: 2022-06-05 17:04:37
 */
#include "mpc.h"
#include "mpc_add_content.h"
#ifdef _WIN32

static char buffer[2048];

char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

void add_history(char* unused) {}

#else
#include <editline/readline.h>
#endif


long eval_op(long x, char* op, long y){//perform the corresponding calculation
	if(strcmp(op, "+") == 0){return x + y;}
	if(strcmp(op, "-") == 0){return x - y;}
	if(strcmp(op, "*") == 0){return x * y;}
	if(strcmp(op, "/") == 0){return x / y;}
	if(strcmp(op, "%") == 0){return x % y;}
	if(strcmp(op, "^") == 0){return pow(x,y);}
	if(strcmp(op, "or") == 0){return x | y;}
	if(strcmp(op, "and") == 0){return x & y;}
	if(strcmp(op, "xor") == 0){return x ^ y;}
	return 0;
}

long eval(mpc_ast_t* t){
	if(strstr(t->tag, "number")){// t tagged as a number
		return atoi(t->contents);
	}
	char* op = t->children[1]->contents;//get the operator
	long ans = eval(t->children[2]);//recursively store the third child
	int i = 3;
	while(strstr(t->children[i]->tag, "expr")){
		ans = eval_op(ans, op, eval(t->children[i]));
		i++;
	}
	return ans;

}

int main(int argc, char** argv){
	mpc_parser_t* Number = mpc_new("number");
	mpc_parser_t* Operator = mpc_new("operator");
	mpc_parser_t* Expr = mpc_new("expr");
	mpc_parser_t* Lispy = mpc_new("lispy");

	mpca_lang(MPCA_LANG_DEFAULT, \
		" \
		number: /-?[0-9]+/ ; \
		operator : '+' | '-' | '*' | '/' | '%' | '^' | /or/ | /and/ | /xor/; \
		expr : <number> | '(' <operator> <expr>+ ')' ; \
		lispy : /^/ <operator> <expr>+ /$/ ; \
		",
		Number, Operator, Expr, Lispy);

	puts("Lispy Version 0.0.0.0.3");
	puts("Press Ctrl+C to exit\n");
	while(1){
		char* input = readline("lispy> ");
		add_history(input);

		mpc_result_t r;
		if(mpc_parse("<stdin>", input, Lispy, &r)){
			long result = eval(r.output);
			long leaves_count = mpc_ast_leaves_count(r.output);
			printf("%li, leaves: %li\n", result,leaves_count);
			mpc_ast_delete(r.output);
		}else{
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}
		free(input);

	}
	mpc_cleanup(4, Number, Operator, Expr, Lispy);
	return EXIT_SUCCESS;
}