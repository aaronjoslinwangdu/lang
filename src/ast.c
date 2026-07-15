#include "ast.h"
#include "memory.h"

#include <string.h>

void init_expr_array(ExprArray *exprs) {
  exprs->count = 0;
  exprs->capacity = 0;
  exprs->entries = NULL;
}

Expr *make_expr(Arena *arena, ExprType type, int line) {
  Expr *expr = arena_allocate(arena, sizeof(*expr));
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
  char *str = arena_allocate(arena, length + 1);
  memcpy(str, start, length);
  str[length] = '\0';
  expr->as.string = str;
  return expr;
}

Expr *make_var(Arena *arena, int line, char *start, int length) {
  Expr *expr = make_expr(arena, EXPR_VAR, line);
  char *name = arena_allocate(arena, length + 1);
  memcpy(name, start, length);
  name[length] = '\0';
  expr->as.var.name = name;
  return expr;
}

Expr *make_unary(Arena *arena, int line, TokenType op, Expr *left) {
  Expr *expr = make_expr(arena, EXPR_UNARY, line);
  expr->as.unary.op = op;
  expr->as.unary.left = left;
  return expr;
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

Expr *make_block(Arena *arena, int line, ExprArray *exprs) {
  Expr *block = make_expr(arena, EXPR_BLOCK, line);
  block->as.block.exprs = exprs;
  return block;
}
