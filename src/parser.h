#ifndef _PEACH_PARSER_H
#define _PEACH_PARSER_H

#include "ast.h"
#include "token.h"

void parse(TokenArray *tokens, Arena *arena);

#endif
