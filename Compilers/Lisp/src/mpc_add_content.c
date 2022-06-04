/*
 * @Author: FrankTudor
 * @Date: 2022-06-04 20:30:04
 * @LastEditors: FrankTudor
 * @Description: This file is created, edited, contributed by FrankTudor
 * @LastEditTime: 2022-06-04 21:55:40
 */
#include "mpc_add_content.h"

int max(int n,  ...){
	va_list va;
	va_start(va,n);
	int tmp, max = 0;
	for(int i = 0; i < n; i++){
		tmp = va_arg(va, int) ;
		max = max < tmp ? tmp : max;
	}
	va_end(va);
	return max;
}
int min(int n,  ...){
	va_list va;
	va_start(va,n);
	int tmp, min = __INT_MAX__;
	for(int i = 0; i < n; i++){
		tmp = va_arg(va, int) ;
		min = min > tmp ? tmp : min;
	}
	va_end(va);
	return min;
}
long umax(long n,  ...){
	va_list va;
	va_start(va,n);
	long tmp, max = 0;
	for(long i = 0; i < n; i++){
		tmp = va_arg(va, long) ;
		max = max < tmp ? tmp : max;
	}
	va_end(va);
	return max;
}
long umin(long n,  ...){
	va_list va;
	va_start(va,n);
	long tmp, min = __LONG_MAX__;
	for(long i = 0; i < n; i++){
		tmp = va_arg(va, long) ;
		min = min > tmp ? tmp : min;
	}
	va_end(va);
	return min;
}
long height(mpc_ast_t* t){
	if(strstr(t->tag, "number")){
		return 0;
	}
	int lheight = height(t->children[2]);
	int i = 3;
	int tmp, rheight=0;
	while(strstr(t->children[i]->tag, "expr")){
		tmp = height(t->children[i]);
		rheight = umax(2, rheight, tmp);
		i++;
	}
	if(lheight > rheight){
		return (lheight + 1);
	}else{
		return (rheight + 1);
	}
}

long mpc_ast_node_count(mpc_ast_t* t){
	if(strstr(t->tag, "number")){
		return 1;
	}
	int count;
	if(strstr(t->children[2]->tag, "expr")){
		count = 1 + mpc_ast_node_count(t->children[2]);
	}else{
		count = 1;
	}
	int i =3;
	while(strstr(t->children[i]->tag, "expr")){
		count += mpc_ast_node_count(t->children[i]);
		i++;
	}
	return count ;//plus current level operator
}

