PROJ = Lisp Compiler
CC = gcc
STD = -std=c99
MKDIR = mkdir -p
DIST = bin
CFLAGS = -Wall -Wextra -pedantic -O3 -g 

.PHONY: all clean

# all include parser and evaluator
all: parser evaluator


parser:
	$(CC) src/mpc.c src/mpc_add_content.c src/parsing/parser.c -Iinclude -ledit -lm $(CFLAGS) -o $(DIST)/parser

evaluator:
	$(CC) src/mpc.c src/mpc_add_content.c src/evaluation/evaluator.c -Iinclude -ledit -lm $(CFLAGS) -o $(DIST)/evaluator


	

clean:
	rm -f $(DIST)/parser
	rm -f $(DIST)/evaluator
