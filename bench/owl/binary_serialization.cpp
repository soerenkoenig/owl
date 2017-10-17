#include "benchpress/benchpress.hpp"
#include "owl/utils/binary_serialization.hpp"
#include <array>

namespace benchpress
{

  BENCHMARK("write_binary vector", [](benchpress::context* ctx)
  {
    std::stringstream ss;
    std::vector<int> data(1000);
  
    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i)
    {
      owl::utils::write_binary(ss, data);
    }
  })
  
  BENCHMARK("write_binary array", ([](benchpress::context* ctx)
  {
    std::stringstream ss;
    std::array<int, 1000> data;
  
    ctx->reset_timer();
    for (size_t i = 0; i < ctx->num_iterations(); ++i)
    {
      owl::utils::write_binary(ss, data);
    }
  }))

}
