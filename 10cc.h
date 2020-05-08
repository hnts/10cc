#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// parse.c
typedef enum {
  ND_ADD, // +
  ND_SUB, // -
  ND_MUL, // *
  ND_DIV, // /
  ND_NUM, // integer
  ND_EQ,
  ND_NE,
  ND_LT,
  ND_LE,
  ND_ASSIGN, // =
  ND_LVAR, // local variable
} NodeKind;

typedef struct Node Node;

struct Node {
  NodeKind kind;
  Node *lhs;
  Node *rhs;
  int val;
  int offset;
};

Node *expr();
void program();
extern Node *code[100];

// token.c
typedef enum {
  TK_RESERVED, // 記号
  TK_IDENT,    // 識別子
  TK_NUM,      // 整数トークン
  TK_EOF,      // 入力の終わりを表すトークン
} TokenType;

typedef struct Token Token;

struct Token {
  int type; // トークンの型
  Token *next;    // 次の入力トークン
  int val;        // kindがTK_NUMの場合、その数値
  char *str;      // トークン文字列
  int len;        // トークンの長さ
};

Token *tokenize(char *p);
void error_at(char *loc, char *fmt, ...);

// codegen.c
void gen(Node *node);

// util.c
void error(char *fmt, ...);