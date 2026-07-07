#ifndef _lang_parser_c
#define _lang_parser_c

#include "common.h"
#include "scanner.h"

typedef enum {
  OP_FUNCTION,
  OP_MATCH,
  OP_BLOCK,
  OP_LAMBDA,
  OP_NUMBER,
  OP_STRING,
  OP_IDENTIFIER,
} Op;

typedef struct {
  Op op;
  char *start;
  int length;
  int line;
} Node;

typedef struct {
  int count;
  int capacity;
  Node *entries;
} NodeArray;

void parse(TokenArray *tokens, NodeArray *nodes);

void init_node_array(NodeArray *nodes);
void free_node_array(NodeArray *nodes);

#endif
