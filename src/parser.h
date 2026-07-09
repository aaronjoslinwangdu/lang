#ifndef _lang_parser_c
#define _lang_parser_c

#include "scanner.h"

typedef enum {
  EXPR_BLOCK,
  EXPR_GROUP,
  EXPR_CALL,
  EXPR_UNARY,
  EXPR_BINARY,
  EXPR_STRING,
  EXPR_NUMBER,
  EXPR_BOOLEAN,
  EXPR_NIL,
} ExprType;

typedef enum {
  UNARY_NEGATE,
  UNARY_NOT,
} UnaryType;

typedef enum {
  BINARY_GREATER,
  BINARY_GREATER_EQ,
  BINARY_LESS,
  BINARY_LESS_EQ,
  BINARY_MATCH,
  BINARY_EQ_EQ,
  BINARY_ADD,
  BINARY_SUB,
  BINARY_MULT,
  BINARY_DIV,
} BinaryType;

typedef struct Expr Expr;

typedef struct {
  Expr *expr;
} Group;

typedef struct {
  const char *start;
  int length;
} Var;

typedef struct {
  Var *name;
  Expr **args;
} Call;

typedef struct {
  UnaryType type;
  const char *start;
  int length;
} Unary;

typedef struct {
  const char *left_start;
  int left_length;
  BinaryType type;
  const char *right_start;
  int right_length;
} Binary;

typedef struct Expr {
  ExprType type;
  union {
    Group *block;
    Call *call;
    Unary *unary;
    Binary *binary;
    Var *var;
    bool boolean;
    double number;
    char *string;
  } as;
} Expr;

#endif
