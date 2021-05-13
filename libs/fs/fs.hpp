#ifndef __ANDROMEDA_LIBS_UTILS__
#define __ANDROMEDA_LIBS_UTILS__

#include <stdio.h>
#include <stdlib.h>

#include "../libs.hpp"
#include "../../engine/andromeda.hpp"

static inline const char *L::Fs::ReadFileContent(const char *path)
{

  FILE *infile;
  char *buffer;
  long numbytes;

  infile = fopen(path, "r");
  ASSERT(infile, "Fopen: Unable to open file", path);

  fseek(infile, 0L, SEEK_END);
  numbytes = ftell(infile);

  fseek(infile, 0L, SEEK_SET);

  buffer = (char *)calloc(numbytes, sizeof(char));
  ASSERT(buffer, "unable to allocate data", NULL);

  fread(buffer, sizeof(char), numbytes, infile);
  fclose(infile);

  return buffer;
}

#endif // __ANDROMEDA_LIBS_UTILS__
