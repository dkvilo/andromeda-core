#ifndef __ANDROMEDA_CORE_API__
#define __ANDROMEDA_CORE_API__

#include <iostream>

#define ASSERT(check, msg)                                   \
  {                                                          \
    if (!(check))                                            \
    {                                                        \
      std::cout << "Assertion failed: " << msg << std::endl; \
      exit(1);                                               \
    }                                                        \
  }

namespace Andromeda
{
  struct Entity;
  struct UI;

  class Editor;
  class Window;
  class Log;
}

namespace Andromeda::Types
{
  struct WindowConfog;
}

#endif // __ANDROMEDA_CORE_API__