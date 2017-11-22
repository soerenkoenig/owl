
#pragma once
#if __has_include(<variant>)
#include <variant>
#else
#include "thirdparty/variant/variant.hpp"
namespace std
{
  using namespace mpark;
}
#endif

