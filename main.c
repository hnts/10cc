#include "10cc.h"

LVar *locals;

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Invalid arguments\n");
    return 1;
  }

  char *user_input = argv[1];
  Token *token = tokenize(user_input);

  program(token);

  int offset = 0;
  for (LVar *var = locals; var; var = var->next) {
    offset += 8;
    var->offset = offset;
  }

  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  printf("    push rbp\n");
  printf("    mov rbp, rsp\n");
  printf("    sub rsp, 208\n");

  for (int i = 0; code[i]; i++) {
    gen(code[i]);

    printf("    pop rax\n");
  }

  printf("    mov rsp, rbp\n");
  printf("    pop rbp\n");
  printf("    ret\n");
  return 0;
}