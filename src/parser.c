#include "parser.h"
#include "memory.h"
#include "scanner.h"

typedef struct {
  int current;
  TokenArray *tokens;
  NodeArray *nodes;
} Parser;

Parser parser;

void init_node_array(NodeArray *nodes) {
  nodes->count = 0;
  nodes->capacity = 0;
  nodes->entries = NULL;
}

void free_node_array(NodeArray *nodes) {
  DYN_ARR_FREE(nodes);
  init_node_array(nodes);
}


static bool is_end() {
  return parser.tokens->entries[parser.current].type == TOKEN_EOF;
}

static Token *peek() {
  // TODO: error handling
  if (is_end())
    return NULL;
  return &parser.tokens->entries[parser.current + 1];
}

static Token *current() { return &parser.tokens->entries[parser.current]; }

static Token *consume(TokenType type) {
  // TODO: error handling
  if (is_end())
    return NULL;
  // TODO: error handling
  if (current()->type != type)
    return NULL;
  return &parser.tokens->entries[parser.current++];
}

static Node match(Token *token) {}

static Node function(Token *token) {
  if (token->type != TOKEN_FUNCTION) {
    return match(token);
  }
  consume(TOKEN_FUNCTION);
  Token *ident = consume(TOKEN_IDENTIFIER);
}

void parse(TokenArray *tokens, NodeArray *nodes) {
  parser.current = 0;
  parser.tokens = tokens;
  parser.nodes = nodes;

  while (!is_end()) {
    Node node = function(current());
    DYN_ARR_PUSH(Node, nodes, node);
  }
}
