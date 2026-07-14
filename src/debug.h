#ifndef _PEACH_DEBUG_H
#define _PEACH_DEBUG_H

#include "ast.h"
#include "token.h"

void print_token(Token *token);
void print_expr(Expr *expr, int indent);

#endif
