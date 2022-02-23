#include <stdio.h>
#include <stdlib.h>
#include "tokenize.h"
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

// no Ctrl+D functionality
// there are bugs with using arguments, but simple commands like ls work

int main(int argc, char **argv, char **envp)
{
  printf("Welcome to mini-shell.\n");
  while (1)
  {
    char input[MAX_NUM_CHARS];
    printf("shell $ ");
    scanf("%s", input);
    if (strcmp(input, "exit") == 0)
      break;
    char **tokens = tokenize(input);
    int status;
    if (fork() == 0)
    {
      execvp(tokens[0], tokens);
      exit(0);
    }
    wait(&status);
  }
  printf("Bye bye.");
  return 0;
}
