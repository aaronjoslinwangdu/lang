#include "token.h"
#include "memory.h"

void init_token_array(TokenArray *tokens) {
  tokens->count = 0;
  tokens->capacity = 0;
  tokens->entries = NULL;
}

void free_token_array(TokenArray *tokens) {
  DYN_ARR_FREE(TokenArray, tokens, tokens->count);
  init_token_array(tokens);
}
