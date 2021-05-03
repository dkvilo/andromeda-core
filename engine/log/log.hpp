#ifndef __ENGINE_LOG__
#define __ENGINE_LOG__

#include <stdio.h>

#include "andromeda.hpp"

class Andromeda::Log
{
private:
  char *m_prefix;

public:
  inline void set_prefix(const char *prefix)
  {
    this->m_prefix = const_cast<char *>(prefix);
  }

  inline void Print(const char *message)
  {
    printf("@[%s]: %s\n", this->m_prefix, message);
  }
};

#endif // __ENGINE_LOG__
