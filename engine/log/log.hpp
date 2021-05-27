#ifndef __ENGINE_LOG__
#define __ENGINE_LOG__

#include <stdio.h>

#include "andromeda.hpp"

class Andromeda::Log
{
private:
  char *m_Prefix;

public:
  inline void set_prefix(const char *prefix)
  {
    m_Prefix = const_cast<char *>(prefix);
  }

  inline void Print(const char *message)
  {
    printf("@[%s]: %s\n", m_Prefix, message);
  }
};

#endif // __ENGINE_LOG__
