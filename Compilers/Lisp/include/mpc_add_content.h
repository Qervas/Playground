/*
 * @Author: FrankTudor
 * @Date: 2022-06-04 20:08:11
 * @LastEditors: FrankTudor
 * @Description: This file is created, edited, contributed by FrankTudor
 * @LastEditTime: 2022-06-04 21:56:06
 */
#ifndef MPC_ADD_CONTENT_H
#define MPC_ADD_CONTENT_H
#include "mpc.h"
int max(int n,  ...);
int min(int n,  ...);
long umax(long n,  ...);
long umin(long n,  ...);
long height(mpc_ast_t* t);
long mpc_ast_node_count(mpc_ast_t* t);
#endif //MPC_ADD_CONTENT_H