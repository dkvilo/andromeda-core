#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <ctype.h>

void rm_from_str(char *source, char target)
{
  char *i = source;
  char *j = source;
  while (*j != 0)
  {
    *i = *j++;
    if (*i != target)
    {
      i++;
    }
  }
  *i = 0;
}

const char *read_file_content(const char *path)
{
  FILE *infile;
  char *buffer;
  long numbytes;

  infile = fopen(path, "r");
  if (infile == NULL)
  {
    perror("fopen\t");
    exit(-1);
  }

  fseek(infile, 0L, SEEK_END);
  numbytes = ftell(infile);

  fseek(infile, 0L, SEEK_SET);
  buffer = (char *)calloc(numbytes, sizeof(char));
  if (buffer == NULL)
    exit(-1);

  fread(buffer, sizeof(char), numbytes, infile);
  fclose(infile);
  return buffer;
}

char *line_by_line(char *key, const char *path)
{
  char *line[1024];
  const char *search = "=";
  char *token;
  char *value;

  FILE *fp = fopen(path, "r");

  while (fgets((char *)line, sizeof((char *)line), fp) != NULL)
  {
    token = strtok((char *)line, search);
    if (strcmp(key, token) == 0)
    {
      value = strtok(NULL, search);
    }
  }

  delete token;
  delete line;
  delete search;

  fclose(fp);
  return value;
}

enum Token
{
  TokNone,
  TokKeyword,    // let, if, while, return, func, float ...
  TokIdentifier, // x, name, color ...
  TokSeparator,  // {, [, (, ;
  TokOperator,   // :=, ::, +, -, /, *, %
  TokLiteral,    // true, 1, 0.1, "String", 'a'
  TokComment     // /* */,  //
};

const char *tok_to_str(Token tok)
{
  switch (tok)
  {
  case TokNone:
    return "NONE";
    break;
  case TokKeyword:
    return "KEYWORD";
    break;
  case TokOperator:
    return "OPERATOR";
    break;
  case TokComment:
    return "COMMENT";
    break;
  };
  return "NONE";
}

// let x := 1;
void parse(char c)
{
  printf("Found operator LET [%c]", c);
}

void parse_variable(char *buf)
{
  const char *spliter = ":=";
  const char *key = strtok(buf, spliter);
  printf("\nfound:[%s]\n", buf);
}

int main()
{
  const char *buf = read_file_content("lang.prx");

  int length = strlen(buf); // / sizeof(file_content[0]);
  for (unsigned long long ind = 0; ind < length; ind++)
  {
    if (buf[ind + 0] == '/' && buf[ind + 1] == '/')
    {
      continue;
    }
    else if (buf[ind + 0] == 'l' && buf[ind + 1] == 'e' && buf[ind + 2] == 't')
    {
      parse_variable((char *)buf);
    }
  }

  return 0;
}
