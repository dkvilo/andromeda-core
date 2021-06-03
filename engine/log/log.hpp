#ifndef __ENGINE_LOG__
#define __ENGINE_LOG__

#include <stdio.h>

#include "andromeda.hpp"
#include "spdlog/spdlog.h"

class Andromeda::Log
{

public:
  static inline void SetPrefix(const char *prefix)
  {
    Get().set_prefix_impl(prefix);
  }

  static inline void Print(const char *message)
  {
    Get().print_impl(message);
  }

  static inline void Warn(const char *message)
  {
    Get().warning_impl(message);
  }

  Log() = default;

private:
  const char *m_Prefix;

private:
  static Log &Get()
  {
    static Log s_Instance;
    return s_Instance;
  }

  void set_prefix_impl(const char *prefix)
  {
    m_Prefix = prefix;
  }

  void print_impl(const char *message)
  {
    spdlog::info("({0}): {1}", m_Prefix, message);
  }

  void warning_impl(const char *message)
  {
    spdlog::warn("({0}): {1}", m_Prefix, message);
  }
};

#endif // __ENGINE_LOG__
