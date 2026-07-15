#ifndef _PEACH_AST_H
#define _PEACH_AST_H

#include "common.h"
#include "memory.h"
#include "token.h"

typedef enum {
  EXPR_BLOCK,
  EXPR_GROUPING,
  EXPR_UNARY,
  EXPR_BINARY,
  EXPR_CALL,
  EXPR_VAR,
  EXPR_STRING,
  EXPR_NUMBER,
  EXPR_BOOLEAN,
  EXPR_NIL,
} ExprType;

typedef struct Expr Expr;

typedef struct {
  int count;
  int capacity;
  Expr **entries;
} ExprArray;

typedef struct {
  Expr *expr;
} Grouping;

typedef struct {
  ExprArray *exprs;
} Block;

typedef struct {
  const char *name;
} Var;

typedef struct {
  Var *name;
  Expr **args;
} Call;

typedef struct {
  TokenType op;
  Expr *left;
} Unary;

typedef struct {
  TokenType op;
  Expr *left, *right;
} Binary;

typedef struct Expr {
  ExprType type;
  int line;
  union {
    Grouping grouping;
    Block block;
    Call call;
    Unary unary;
    Binary binary;
    Var var;
    bool boolean;
    double number;
    char *string;
  } as;
} Expr;

Expr *make_nil(Arena *arena, int line);
Expr *make_boolean(Arena *arena, int line, bool value);
Expr *make_number(Arena *arena, int line, double value);
Expr *make_var(Arena *arena, int line, char *start, int length);
Expr *make_string(Arena *arena, int line, char *start, int length);
Expr *make_unary(Arena *arena, int line, TokenType op, Expr *left);
Expr *make_binary(Arena *arena, int line, TokenType op, Expr *left,
                  Expr *right);
Expr *make_grouping(Arena *arena, int line, Expr *expr);
Expr *make_block(Arena *arena, int line, ExprArray *exprs);

void init_expr_array(ExprArray *exprs);

#endif
