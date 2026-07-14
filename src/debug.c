#include "debug.h"
#include "ast.h"
#include <stdio.h>

char *printable_token_type(TokenType type) {
  switch (type) {
  case TOKEN_LEFT_PAREN:
    return "LEFT_PAREN";
  case TOKEN_RIGHT_PAREN:
    return "RIGHT_PAREN";
  case TOKEN_LEFT_BRACE:
    return "LEFT_BRACE";
  case TOKEN_RIGHT_BRACE:
    return "RIGHT_BRACE";
  case TOKEN_LEFT_BRACKET:
    return "LEFT_BRACKET";
  case TOKEN_RIGHT_BRACKET:
    return "RIGHT_BRACKET";
  case TOKEN_PLUS:
    return "PLUS";
  case TOKEN_MINUS:
    return "MINUS";
  case TOKEN_STAR:
    return "STAR";
  case TOKEN_SLASH:
    return "SLASH";
  case TOKEN_LESS:
    return "LESS";
  case TOKEN_GREATER:
    return "GREATER";
  case TOKEN_BANG:
    return "BANG";
  case TOKEN_EQUAL:
    return "EQUAL";
  case TOKEN_COMMA:
    return "COMMA";
  case TOKEN_DOT:
    return "DOT";
  case TOKEN_COLON:
    return "COLON";
  case TOKEN_BANG_EQUAL:
    return "BANG_EQUAL";
  case TOKEN_EQUAL_EQUAL:
    return "EQUAL_EQUAL";
  case TOKEN_ARROW:
    return "ARROW";
  case TOKEN_LESS_EQUAL:
    return "LESS_EQUAL";
  case TOKEN_GREATER_EQUAL:
    return "GREATER_EQUAL";
  case TOKEN_PIPE:
    return "PIPE";
  case TOKEN_IDENTIFIER:
    return "IDENTIFIER";
  case TOKEN_STRING:
    return "STRING";
  case TOKEN_NUMBER:
    return "NUMBER";
  case TOKEN_NIL:
    return "NIL";
  case TOKEN_FUNCTION:
    return "FUNCTION";
  case TOKEN_IF:
    return "IF";
  case TOKEN_ELSE:
    return "ELSE";
  case TOKEN_TRUE:
    return "TRUE";
  case TOKEN_FALSE:
    return "FALSE";
  case TOKEN_EOF:
    return "EOF";
  case TOKEN_ERROR:
    return "ERROR";
  case TOKEN_OR:
    return "OR";
  case TOKEN_AND:
    return "AND";
  }
}

void print_token(Token *token) {
  printf("Token = { ");
  printf("type = %12s, ", printable_token_type(token->type));
  printf("lexeme = '%.*s', ", token->length, token->start);
  printf("line = %04d }\n", token->line);
}

void print_expr(Expr *expr, int indent) {
  printf("Expr { line = %04d, ", expr->line);
  switch (expr->type) {
  case EXPR_UNARY: {
    Unary unary = AS_UNARY(*expr);
    printf("type = UNARY, op = %s,\n%*sexpr = ",
           printable_token_type(unary.op), indent + 2, "");
    print_expr(unary.expr, indent + 2);
    printf("%*s}\n", indent, "");
    return;
  }
  case EXPR_BINARY: {
    Binary binary = AS_BINARY(*expr);
    printf("type = BINARY, op = %s,\n%*sleft = ",
           printable_token_type(binary.op), indent + 2, "");
    print_expr(binary.left, indent + 2);
    printf("%*sright = ", indent + 2, "");
    print_expr(binary.right, indent + 2);
    printf("%*s}\n", indent, "");
    return;
  }
  case EXPR_CALL:
    printf("type = CALL }\n");
    return;
  case EXPR_VAR: {
    Var var = AS_VAR(*expr);
    printf("type = VAR, name = %s }\n", var.name);
    return;
  }
  case EXPR_STRING: {
    printf("type = STRING, value = %s }\n", AS_STRING(*expr));
    return;
  }
  case EXPR_NUMBER:
    printf("type = NUMBER, value = %f }\n", AS_NUMBER(*expr));
    return;
  case EXPR_BOOLEAN:
    printf("type = BOOLEAN, value = %s }\n",
           AS_BOOLEAN(*expr) ? "true" : "false");
    return;
  case EXPR_NIL:
    printf("type = NIL }\n");
    return;
  case EXPR_GROUPING: {
    Grouping grouping = AS_GROUPING(*expr);
    printf("type = GROUPING,\n%*sexpr = ", indent + 2, "");
    print_expr(grouping.expr, indent + 2);
    printf("%*s}\n", indent, "");
    return;
  }
  }
}
