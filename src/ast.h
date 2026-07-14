#ifndef _PEACH_AST_H
#define _PEACH_AST_H

#include "common.h"
#include "memory.h"
#include "token.h"

typedef enum {
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
  Expr *expr;
} Grouping;

typedef struct {
  Expr **expr;
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
  Expr *expr;
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
Expr *make_unary(Arena *arena, int line, TokenType op, Expr *expr);
Expr *make_binary(Arena *arena, int line, TokenType op, Expr *left,
                  Expr *right);
Expr *make_grouping(Arena *arena, int line, Expr *expr);

#define AS_BOOLEAN(expression) (bool)(expression).as.boolean
#define AS_NUMBER(expression) (double)(expression).as.number
#define AS_STRING(expression) (char *)(expression).as.string
#define AS_VAR(expression) (Var)(expression).as.var
#define AS_UNARY(expression) (Unary)(expression).as.unary
#define AS_BINARY(expression) (Binary)(expression).as.binary
#define AS_GROUPING(expression) (Grouping)(expression).as.grouping

#endif
