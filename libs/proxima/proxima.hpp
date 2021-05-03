#ifndef __PROXIMA_HPP__
#define __PROXIMA_HPP__

#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <ctype.h>

#include "../libs.hpp"

struct L::Proxima
{

  enum Token
  {
    TokNone,
    TokKeyword,    // lRun(const char *file)et, if, while, return, func, float ...
    TokIdentifier, // x, name, color ...
    TokSeparator,  // {, [, (, ;
    TokOperator,   // :=, ::, +, -, /, *, %
    TokLiteral,    // true, 1, 0.1, "String", 'a'
    TokComment     // /* */,  //
  };

  void rm_from_str(char *source, char target);
  const char *read_file_content(const char *path);
  void parse_variable(char *buf);
  char *line_by_line(char *key, const char *path);
  const char *tok_to_str(Token tok);
  void parse(char c);

public:
  void run(const char *file);
};

void L::Proxima::rm_from_str(char *source, char target)
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

const char *L::Proxima::read_file_content(const char *path)
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
  {
    exit(-1);
  }

  fread(buffer, sizeof(char), numbytes, infile);
  fclose(infile);
  return buffer;
}

char *L::Proxima::line_by_line(char *key, const char *path)
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

const char *L::Proxima::tok_to_str(L::Proxima::Token tok)
{
  switch (tok)
  {
  case L::Proxima::TokNone:
    return "NONE";
    break;
  case L::Proxima::TokKeyword:
    return "KEYWORD";
    break;
  case L::Proxima::TokOperator:
    return "OPERATOR";
    break;
  case L::Proxima::TokComment:
    return "COMMENT";
    break;
  };
  return "NONE";
}

void L::Proxima::parse(char c)
{
  printf("Found operator LET [%c]", c);
}

void L::Proxima::parse_variable(char *buf)
{
  const char *spliter = ":=";
  const char *key = strtok(buf, spliter);
}

void L::Proxima::run(const char *file)
{
  printf("\nProxima Runtime: <%s>\n", file);
  const char *buf = L::Proxima::read_file_content(file);

  int length = strlen(buf);
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
}

#endif // __PROXIMA_HPP__