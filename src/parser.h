#ifndef _LANG_PARSER_H
#define _LANG_PARSER_H

#include "ast.h"
#include "token.h"

void parse(TokenArray *tokens, Arena *arena);

#endif
