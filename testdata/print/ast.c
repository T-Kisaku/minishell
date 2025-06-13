#include "ast.h"
#include "libft.h"
#include <stdio.h>

void print_ast(t_ast *ast, int indent);

void print_indent(int indent) {
  for (int i = 0; i < indent; i++)
    printf("  ");
}

void print_redir_target(t_redir_target t) {
  if (t.is_direct_to_fd)
    printf("(fd)%d", t.fd);
  else {
    printf("(filename)%s", t.filename);
  }
}

void print_redirection(t_list *redir_list, int indent) {
  while (redir_list) {
    t_redir *redir = lstget_redir(redir_list);
    print_indent(indent);
    printf("redir: ");

    switch (redir->type) {
    case REDIR_INPUT:
    case REDIR_OUTPUT:
      print_redir_target(redir->from);
      break;
    case REDIR_HERE_DOC:
    case REDIR_APPEND:
      print_redir_target(redir->to);
      break;
    }
    switch (redir->type) {
    case REDIR_INPUT:
      printf("< ");
      break;
    case REDIR_OUTPUT:
      printf("> ");
      break;
    case REDIR_HERE_DOC:
      printf("<< ");
      break;
    case REDIR_APPEND:
      printf(">> ");
      break;
    }
    switch (redir->type) {
    case REDIR_INPUT:
    case REDIR_OUTPUT:
      print_redir_target(redir->to);
      break;
    case REDIR_HERE_DOC:
    case REDIR_APPEND:
      print_redir_target(redir->from);
      break;
    }
    printf("\n");
    redir_list = redir_list->next;
  }
}

void print_command(t_command *cmd, int indent) {
  print_indent(indent);
  printf("command: ");
  if (cmd->type == CMD_SIMPLE) {
    printf("simple\n");
    print_indent(indent + 1);
    printf("argc: %d\n", cmd->u.simple.argc);
    for (int i = 0; i < cmd->u.simple.argc; i++) {
      print_indent(indent + 1);
      printf("argv[%d]: \"%s\"\n", i, cmd->u.simple.argv[i]);
    }
  } else if (cmd->type == CMD_SUBSHELL) {
    printf("subshell\n");
    print_ast(cmd->u.subshell.and_or_list, indent + 1);
  }
  if (cmd->redir_list)
    print_redirection(cmd->redir_list, indent + 1);
}

void print_pipeline(t_pipeline *pipeline, int indent) {
  t_list *node = pipeline->command_list;
  print_indent(indent);
  printf("pipeline:\n");
  while (node) {
    t_command *cmd = lstget_command(node);
    print_command(cmd, indent + 1);
    node = node->next;
  }
}

void print_and_or(t_and_or *and_or, int indent) {
  print_pipeline(and_or->pipeline, indent);
  if (and_or->op_next != OP_NONE) {
    print_indent(indent);
    printf("op_next: %s\n", and_or->op_next == OP_AND ? "&&" : "||");
  }
}

void print_ast(t_ast *ast, int indent) {
  t_list *node = ast;
  while (node) {
    t_and_or *and_or = lstget_and_or(node);
    print_and_or(and_or, indent);
    node = node->next;
  }
}
