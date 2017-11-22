#pragma once

#if __has_include(<optional>)
#include <optional>
#elif __has_include(<experimental/optional>)
#include <experimental/optional>
namespace std
{
  using namespace experimental;
}
#else
static_assert(false, "no std::optional available");
#endif

