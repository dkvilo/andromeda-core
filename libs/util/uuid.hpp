#ifndef __ANDROMEDA_LIBS_UTIL_UUID__
#define __ANDROMEDA_LIBS_UTIL_UUID__

#include <random>
#include <string>

#include "../libs.hpp"

class L::Util::UUID
{

public:
  UUID() = default;

  std::string V1() const
  {

    const unsigned int SET_LENGTH = 0x10;
    const char *SET = "0123456789abcdef-";

    const bool DASH_PATTERN[SET_LENGTH] = {
        0, 0, 0, 0, 1, 0, 1, 0,
        1, 0, 1, 0, 0, 0, 0, 0};

    const char DASH = SET[SET_LENGTH];

    static std::random_device device;
    static std::mt19937 range(device());
    std::uniform_int_distribution<int> distribution(0, SET_LENGTH - 1);

    std::string result;
    for (int i = 0; i < SET_LENGTH; i++)
    {
      if (DASH_PATTERN[i])
      {
        result += DASH;
      }

      result += SET[distribution(range)];
      result += SET[distribution(range)];
    }

    return result;
  }
};

#endif // __ANDROMEDA_LIBS_UTIL_UUID__