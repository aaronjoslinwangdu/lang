#include "ast.h"
#include "memory.h"
#include <string.h>

Expr *make_expr(Arena *arena, ExprType type, int line) {
  // TODO: real alignment arg
  Expr *expr = arena_allocate(arena, sizeof(*expr), (2 * sizeof(void *)));
  expr->type = type;
  expr->line = line;
  return expr;
}

Expr *make_nil(Arena *arena, int line) {
  return make_expr(arena, EXPR_NIL, line);
}

Expr *make_boolean(Arena *arena, int line, bool value) {
  Expr *expr = make_expr(arena, EXPR_BOOLEAN, line);
  expr->as.boolean = value;
  return expr;
}

Expr *make_number(Arena *arena, int line, double value) {
  Expr *expr = make_expr(arena, EXPR_NUMBER, line);
  expr->as.number = value;
  return expr;
}

Expr *make_string(Arena *arena, int line, char *start, int length) {
  Expr *expr = make_expr(arena, EXPR_STRING, line);
  // TODO: real alignment arg
  char *str = arena_allocate(arena, length + 1, (2 * sizeof(void *)));
  memcpy(str, start, length);
  str[length] = '\0';
  expr->as.string = str;
  return expr;
}

Expr *make_var(Arena *arena, int line, char *start, int length) {
  Expr *expr = make_expr(arena, EXPR_VAR, line);
  // TODO: real alignment arg
  char *name = arena_allocate(arena, length + 1, (2 * sizeof(void *)));
  memcpy(name, start, length);
  name[length] = '\0';
  expr->as.var.name = name;
  return expr;
}

Expr *make_unary(Arena *arena, int line, TokenType op, Expr *expr) {
  Expr *unary = make_expr(arena, EXPR_UNARY, line);
  unary->as.unary.op = op;
  unary->as.unary.expr = expr;
  return unary;
}

Expr *make_binary(Arena *arena, int line, TokenType op, Expr *left,
                  Expr *right) {
  Expr *expr = make_expr(arena, EXPR_BINARY, line);
  expr->as.binary.op = op;
  expr->as.binary.left = left;
  expr->as.binary.right = right;
  return expr;
}

Expr *make_grouping(Arena *arena, int line, Expr *expr) {
  Expr *grouping = make_expr(arena, EXPR_GROUPING, line);
  grouping->as.grouping.expr = expr;
  return grouping;
}
