#include <stdio.h>
#include <unistd.h>

const int MAX_NUM_CHARS = 255;

// Is whitespace or \t
int is_special(char ch)
{
  return ch == ' ' || ch == '\t';
}

int is_token(char ch)
{
  char *tokens = {
      '(',
      ')',
      '<',
      '>',
      ';',
      '|',
  };
  for (int i = 0; i < 6; i++)
  {
    if (tokens[i] == ch)
      return 1;
  }
  return 0;
}

/**
 * Read the next integer as a string from the input into the output.
 */
int read_string(const char *input, char *output)
{
  int i = 0;
  while (input[i] != '\0' && !(is_special(input[i] || is_token(input[i]))))
  {
    output[i] = input[i];
    ++i;
  }
  output[i] = '\0';
  return i;
}

/**
 * Reads a string in quotes (ignores quotes).
 */
int read_quotes(const char *input, char *output)
{
  int i = 0;
  while (input[i] != '\0' && !(is_special(input[i] || is_token(input[i]))))
  {
    if (input[i] != "\"")
    {
      output[i] = input[i];
      ++i;
    }
  }
  output[i] = '\0';
  return i + 2;
}

/**
 * Parses a string (max 255 chars) and returns an array of tokens.
 */
char **tokenize(char *str)
{
  char *result[MAX_NUM_CHARS];
  int result_i = 0; // tracks index of result arr
  int str_i = 0;    // tracks index of str arr
  char *buf[MAX_NUM_CHARS];
  while (str[str_i] != '\0')
  {
    if (is_special(str[str_i]))
    {
      ++str_i;
      continue;
    }
    else if (is_token(str[str_i]))
    {
      result[result_i] = str[str_i];
      ++str_i;
    }
    else
    {
      if (str[str_i] == "\"")
        str_i += read_quotes(&str[str_i], buf);
      else
        str_i += read_string(&str[str_i], buf);
      /*
       * Bug
       * buf goes out of scope when this function ends, so result[result_i] will end up
       * being null, need to find a way to copy buf to result[result_i]
       */
      result[result_i] = buf;
    }
    ++result_i;
  }
}

int main()
{
  char *buf[MAX_NUM_CHARS];
  read(0, buf, MAX_NUM_CHARS);
  char **result = tokenize(buf);
  int i = 0;
  while (result[i] != NULL) // I think this works...but not sure
  {
    printf(result[i]);
    ++i;
  }
  return 0;
}