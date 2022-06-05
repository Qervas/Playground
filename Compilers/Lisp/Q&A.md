# Chap7

## Parsing


* [ ] › Write a regular expression matching strings of all `a` or `b` such as `aababa` or `bbaa`.
* [ ] › Write a regular expression matching strings of consecutive `a` and `b` such as `ababab` or `aba`.
* [ ] › Write a regular expression matching `pit`, `pot` and `respite` but *not* `peat`, `spit`, or `part`.
* [ ] › Change the grammar to add a new operator such as `%`.
* [ ] › Change the grammar to recognise operators written in textual format `add`, `sub`, `mul`, `div`.
* [ ] › Change the grammar to recognize decimal numbers such as `0.01`, `5.21`, or `10.2`.
* [ ] › Change the grammar to make the operators written conventionally, between two expressions.
* [ ] › Use the grammar from the previous chapter to parse `Doge`. You must add *start* and *end* of input.

## Evaluation

`mpc_add_content.h mpc_add_content.c`

* [X] How would you use `strstr` to see if a node was tagged as an `expr`?

> if(strstr(t->tag, "expr") ){`/*tagged expr*/ `}

* [X] Write a recursive function to compute the number of leaves of a tree.
* [X] Write a recursive function to compute the number of branches of a tree.
* [ ] › Write a recursive function to compute the most number of children spanning from one branch of a tree.
* [X] › How would you use `strcmp` to see if a node had the contents `'('` or `')'`?

  > ```c
  > if(strcmp(t->content, "or") == 0){
  > 	//"or" operator
  > }
  > ```
  >
* [X] › Add the operator `%`, which returns the remainder of division. For example `% 10 6` is `4`.
* [X] › Add the operator `^`, which raises one number to another. For example `^ 4 2` is `16`.
* [ ] › Add the function `min`, which returns the smallest number. For example `min 1 5 3` is `1`.
* [ ] › Add the function `max`, which returns the biggest number. For example `max 1 5 3` is `5`.
* [ ] › Change the minus operator `-` so that when it receives one argument it negates it.
