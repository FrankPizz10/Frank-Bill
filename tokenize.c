#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

const int MAX_NUM_CHARS = 255;

/**
 * COPYRIGHT 2022 these balls
 * Not to be used by Thomas Colao or Frank Pizzella under any circumstances.
 */

// Is whitespace or \t (or possibly newline)
int is_special(char ch)
{
  // should newline be here? its necessary to avoid an extra newline at the end
  // could maybe fix using getline but im too lazy to do that rn and it works
  return ch == ' ' || ch == '\t' || ch == '\n';
}

int is_token(char ch)
{
  return ch == '(' || ch == ')' || ch == '<' || ch == '>' || ch == ';' || ch == '|';
}

/**
 * Reads a string to output, returns the length of the string
 */
int read_string(const char *input, char *output)
{
  int i = 0;
  while (input[i] != '\0' && !(is_special(input[i]) || is_token(input[i])))
  {
    output[i] = input[i];
    ++i;
  }
  output[i] = '\0';
  return i;
}

/**
 * Reads a string in quotes to output (not including quotes), returns the length including quotes
 */
int read_quotes(const char *input, char *output)
{
  int i = 0;
  while (input[i + 1] != '\0' && input[i + 1] != '\"')
  {
    output[i] = input[i + 1];
    ++i;
  }
  output[i] = '\0';
  return i + 2;
}

/**
 * Parses a string (max 255 chars) and returns an array of tokens.
 */
char **tokenize(char *str)
{
  char result[MAX_NUM_CHARS][MAX_NUM_CHARS]; // waste of space but idk a better solution
  int result_i = 0;                          // tracks index of result arr
  int str_i = 0;                             // tracks index of str arr
  while (str[str_i] != '\0')
  {
    char buf[MAX_NUM_CHARS];
    int len;
    if (is_special(str[str_i]))
    {
      ++str_i;
      continue;
    }
    else if (is_token(str[str_i]))
    {
      buf[0] = str[str_i];
      buf[1] = '\0';
      len = 2;
    }
    else
    {
      if (str[str_i] == '\"')
        len = read_quotes(&str[str_i], buf);
      else
        len = read_string(&str[str_i], buf);
    }
    strcpy(&result[result_i][0], buf);
    str_i += len;
    ++result_i;
  }
  char **outer = calloc(MAX_NUM_CHARS, sizeof(char *));
  for (int i = 0; i < result_i; i++)
  {
    char *inner = malloc(MAX_NUM_CHARS * sizeof(char));
    strcpy(inner, &result[i][0]);
    outer[i] = inner;
  }
  return outer;
}

int main()
{
  char buf[MAX_NUM_CHARS];
  read(0, buf, MAX_NUM_CHARS);
  char **result = tokenize(buf);
  int i = 0;
  while (result[i] != NULL)
  {
    if (i > 0)
      printf("\n");
    printf("%s", result[i]);
    ++i;
  }
  return 0;
}